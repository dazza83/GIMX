/*
 Copyright (c) 2016 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#ifndef GUSBHID_H_
#define GUSBHID_H_

#include "ghid.h"

int gusbhid_open_ids(unsigned short vendor, unsigned short product);
s_hid_dev * gusbhid_enumerate(unsigned short vendor, unsigned short product);
void gusbhid_free_enumeration(s_hid_dev * hid_devs);
int gusbhid_open_path(const char * path);
const s_hid_info * gusbhid_get_hid_info(int device);
int gusbhid_close(int device);
int gusbhid_poll(int device);
int gusbhid_read_timeout(int device, void * buf, unsigned int count, unsigned int timeout);
int gusbhid_register(int device, int user, ASYNC_READ_CALLBACK fp_read, ASYNC_WRITE_CALLBACK fp_write, ASYNC_CLOSE_CALLBACK fp_close, ASYNC_REGISTER_SOURCE fp_register);
int gusbhid_write(int device, const void * buf, unsigned int count);
int gusbhid_write_timeout(int device, const void * buf, unsigned int count, unsigned int timeout);

#endif /* GUSBHID_H_ */