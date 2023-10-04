#include "devices.h"

devices::devices()
{

}

size_t devices::deviceCount()
{
    libusb_context *ctx = NULL;
    libusb_device **list = NULL;
    int rc = 0;
    size_t count = 0;

    rc = libusb_init(&ctx);
    count = libusb_get_device_list(ctx, &list);

    libusb_free_device_list(list,count);
    libusb_exit(ctx);

    return count;
}
