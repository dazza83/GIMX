/*
 Copyright (c) 2016 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#include <ghid.h>
#include <guhid.h>
#include <ginput.h>
#include <gpoll.h>
#include <gtimer.h>
#include "common.h"

#define PERIOD 10000//microseconds

#ifdef WIN32
#define REGISTER_FUNCTION gpoll_register_handle
#else
#define REGISTER_FUNCTION gpoll_register_fd
#endif

static int uhid = -1;
static int hid = -1;

static void terminate(int sig) {
  done = 1;
}

static void dump(const unsigned char * packet, unsigned char length) {
  int i;
  for (i = 0; i < length; ++i) {
    if (i && !(i % 8)) {
      printf("\n");
    }
    printf("0x%02x ", packet[i]);
  }
  printf("\n");
}

int hid_read(int user, const void * buf, int status) {

  if (status < 0) {
    done = 1;
    return 1;
  }

  int ret = ghid_poll(hid);
  if (ret < 0) {
    done = 1;
    return 1;
  }

  if (status > 0) {
    struct timeval t;
    gettimeofday(&t, NULL);
    printf("%ld.%06ld ", t.tv_sec, t.tv_usec);
    printf("%s\n", __func__);
    dump((unsigned char *) buf, status);
    fflush(stdout);
    guhid_write(uhid, buf, status);
  }

  return 0;
}

int hid_close(int user) {
  printf("close user: %d\n", user);
  done = 1;
  return 0;
}

int main(int argc, char* argv[]) {

  (void) signal(SIGINT, terminate);
  (void) signal(SIGTERM, terminate);

  char * path = hid_select();

  if (path == NULL) {
    fprintf(stderr, "No HID device selected!\n");
    ginput_quit();
    exit(-1);
  }

  hid = ghid_open_path(path);

  if (hid >= 0) {

    const s_hid_info * hid_info = ghid_get_hid_info(hid);

    printf("Opened device: VID 0x%04x PID 0x%04x PATH %s\n", hid_info->vendor_id, hid_info->product_id, path);

    const s_hid_info * hidInfo = ghid_get_hid_info(hid);
    dump(hidInfo->reportDescriptor, hidInfo->reportDescriptorLength);

    //Create a virtual hid device
    uhid = guhid_create(hidInfo);

    if (uhid >= 0) {

      if (ginput_init(GE_MKB_SOURCE_PHYSICAL, process_event)) {

        display_devices();

        if (ghid_register(hid, 42, hid_read, NULL, hid_close, REGISTER_FUNCTION) != -1) {

          int timer = gtimer_start(42, PERIOD, timer_read, timer_close, REGISTER_FUNCTION);
          if (timer < 0) {
            done = 1;
          }

          int ret = ghid_poll(hid);
          if (ret < 0) {
            done = 1;
          }

          while (!done) {

            gpoll();

            //do something periodically

          }

          if (timer >= 0) {
            gtimer_close(timer);
          }

        }
      } else {
        fprintf(stderr, "GE_initialize failed\n");
      }

      ghid_close(hid);
    }

    guhid_close(uhid);
  }

  free(path);

  ginput_quit();

  printf("Exiting\n");

  return 0;
}