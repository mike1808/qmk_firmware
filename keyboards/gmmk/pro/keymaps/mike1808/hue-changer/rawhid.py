#!/usr/bin/env python3

# NOTE: There are two HID libraries in Python: pyhidapi (https://pypi.org/project/hid/) and cython-hidapi (https://pypi.org/project/hidapi/).
#       Both have similar, but not quite compatible, APIs. This example code uses pyhidapi.

import sys
import hid

vendor_id = 0x320F
product_id = 0x5044

usage_page = 0xFF60
usage = 0x61


def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [
        i
        for i in device_interfaces
        if i["usage_page"] == usage_page and i["usage"] == usage
    ]

    if len(raw_hid_interfaces) == 0:
        return None

    interface = hid.Device(path=raw_hid_interfaces[0]["path"])

    print("Manufacturer: %s" % interface.manufacturer)
    print("Product: %s" % interface.product)

    return interface


def send_raw_packet(data):
    interface = get_raw_hid_interface()

    if interface is None:
        print("No device found")
        sys.exit(1)

    request_data = [0x00] * 33  # First byte is Report ID
    request_data[1 : len(data) + 1] = data
    request_packet = bytes(request_data)

    print("Request:")
    print(request_packet)

    try:
        interface.write(request_packet)

        response_packet = interface.read(32, timeout=1000)

        print("Response:")
        print(response_packet)
    finally:
        interface.close()


if __name__ == "__main__":
    send_raw_packet([0x41, 0x42, 0x43, 0xFF, 0x12])
