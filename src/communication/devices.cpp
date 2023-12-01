#include "devices.h"

auto devices::deviceCount() -> size_t
{
    libusb_context *ctx = nullptr;
    libusb_device **list = nullptr;
    size_t count = 0;

    libusb_init(&ctx);
    count = libusb_get_device_list(ctx, &list);

    libusb_free_device_list(list, (int) count);
    libusb_exit(ctx);

    return count;
}
