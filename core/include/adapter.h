/*
 Copyright (c) 2014 Mathieu Laurendeau
 License: GPLv3
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <connectors/protocol.h>
#include <controller2.h>
#include <config.h>
#include <serialasync.h>

#ifndef WIN32
#include <netinet/in.h>
#else
#include <connectors/windows/sockets.h>
#endif

#define MAX_CONTROLLERS 7
#define MAX_CONFIGURATIONS 8
#define MAX_DEVICES 256
#define MAX_CONTROLS 256

typedef enum
{
  E_ADAPTER_TYPE_NONE,
  E_ADAPTER_TYPE_BLUETOOTH,
  E_ADAPTER_TYPE_DIY_USB,
  E_ADAPTER_TYPE_REMOTE_GIMX,
  E_ADAPTER_TYPE_GPP,
} e_adapter_type;

typedef struct
{
  char* bdaddr_dst;
  int dongle_index;
  //TODO MLA: refactoring (struct, union...)
  char* portname;
  int serialdevice;
  s_packet packet;
  unsigned int bread;
  in_addr_t dst_ip;
  unsigned short dst_port;
  int dst_fd;
  in_addr_t src_ip;
  unsigned short src_port;
  int src_fd;
  e_adapter_type atype;
  e_controller_type ctype;
  int event;
  int axis[AXIS_MAX];
  int change;
  int send_command;
  int ts_axis[AXIS_MAX][2]; //issue 15
  s_report_packet report[2]; //the xbox one guide button needs a dedicated report
  int status;
  int hid_id;
  int hid_busy;
#ifndef WIN32
  int uhid_id;
#else
  struct
  {
	unsigned short vendor;
	unsigned short product;
  } usb_ids;
#endif
} s_adapter;

int adapter_detect();
int adapter_start();
int adapter_send();
void adapter_clean();

s_adapter* adapter_get(unsigned char index);
int adapter_set_port(unsigned char index, char* portname);

void adapter_set_device(int controller, e_device_type device_type, int device_id);
int adapter_get_device(e_device_type device_type, int controller);
int adapter_get_controller(e_device_type device_type, int device_id);

#ifndef WIN32
void adapter_set_uhid_id(int controller, int uhid_id);
#else
void adapter_set_usb_ids(int controller, unsigned short vendor, unsigned short product);
#endif

void adapter_set_axis(unsigned char c, int axis, int value);

int adapter_forward_control_in(int id, unsigned char* data, unsigned char length);
int adapter_forward_interrupt_in(int id, unsigned char* data, unsigned char length);

#endif /* ADAPTER_H_ */
