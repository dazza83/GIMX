/*
 Copyright (c) 2015 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#include <hidasync.h>
#include <usbhidasync.h>

/*
 * \brief Open a hid device.
 *
 * \param device_path  the path of the hid device to open.
 *
 * \return the identifier of the opened device (to be used in further operations), \
 * or -1 in case of failure (e.g. bad path, device already opened).
 */
int hidasync_open_path(const char * device_path) {

    return usbhidasync_open_path(device_path);
}

/*
 * \brief Open a hid device.
 *
 * \param vendor   the vendor id of the hid device to open.
 * \param product  the product id of the hid device to open.
 *
 * \return the identifier of the opened device (to be used in further operations), \
 * or -1 in case of failure (e.g. no device found).
 */
int hidasync_open_ids(unsigned short vendor, unsigned short product) {

  return usbhidasync_open_ids(vendor, product);
}

/*
 * \brief Enumerate hid devices.
 *
 * \param vendor  the vendor id to look for
 * \param product the product id to look for (ignored if vendor is 0)
 *
 * \return the hid devices
 */
s_hid_dev * hidasync_enumerate(unsigned short vendor, unsigned short product) {

    return usbhidasync_enumerate(vendor, product);
}

/*
 * \brief Free the memory allocated by hidasync_enumerate.
 *
 * \param hid_devs  the hid devices returned by hidasync_enumerate
 */
void hidasync_free_enumeration(s_hid_dev * hid_devs) {

    usbhidasync_free_enumeration(hid_devs);
}

/*
 * \brief Get info for a hid device.
 *
 * \param device  the identifier of the hid device
 *
 * \return the hid info
 */
const s_hid_info * hidasync_get_hid_info(int device) {

    return usbhidasync_get_hid_info(device);
}

/*
 * \brief Read from a hid device, with a timeout. Use this function in a synchronous context.
 *
 * \param device  the identifier of the hid device
 * \param buf     the buffer where to store the data
 * \param count   the maximum number of bytes to read
 * \param timeout the maximum time to wait, in seconds
 *
 * \return the number of bytes actually read
 */
int hidasync_read_timeout(int device, void * buf, unsigned int count, unsigned int timeout) {

  return usbhidasync_read_timeout(device, buf, count, timeout);
}

/*
 * \brief Register the device as an event source, and set the external callbacks. \
 * This function triggers an asynchronous context. \
 * The fp_read callback is responsible for setting the next read size.
 *
 * \param device      the hid device
 * \param user        the user to pass to the external callback
 * \param fp_read     the external callback to call on data reception
 * \param fp_write    unused
 * \param fp_close    the external callback to call on failure
 * \param fp_register the function to register the device as an event source
 *
 * \return 0 in case of success, or -1 in case of error
 */
int hidasync_register(int device, int user, ASYNC_READ_CALLBACK fp_read, ASYNC_WRITE_CALLBACK fp_write, ASYNC_CLOSE_CALLBACK fp_close, ASYNC_REGISTER_SOURCE fp_register) {
    
    return usbhidasync_register(device, user, fp_read, fp_write, fp_close, fp_register);
}

/*
 * \brief Write to a serial device, with a timeout. Use this function in a synchronous context.
 *
 * \param device  the identifier of the serial device
 * \param buf     the buffer containing the data to write
 * \param count   the number of bytes in buf
 * \param timeout the maximum time to wait for the completion, in seconds
 *
 * \return the number of bytes actually written (0 in case of timeout)
 */
int hidasync_write_timeout(int device, const void * buf, unsigned int count, unsigned int timeout) {

    return usbhidasync_write_timeout(device, buf, count, timeout);
}

/*
 * \brief Send data to a serial device. Use this function in an asynchronous context.
 *
 * \param device  the identifier of the serial device
 * \param buf     the buffer containing the data to send
 * \param count   the maximum number of bytes to send
 *
 * \return -1 in case of error, 0 in case of pending write, or the number of bytes written
 */
int hidasync_write(int device, const void * buf, unsigned int count) {

    return usbhidasync_write(device, buf, count);
}

/*
 * \brief Close a hid device.
 *
 * \param device  the identifier of the hid device to close.
 *
 * \return 0 in case of success, or -1 in case of failure (i.e. bad device identifier).
 */
int hidasync_close(int device) {

    return usbhidasync_close(device);
}

