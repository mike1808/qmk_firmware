import sys
import hid

vendor_id = 0x320F
product_id = 0x5044

usage_page = 0xFF60
usage = 0x61


device_interfaces = hid.enumerate(vendor_id, product_id)
raw_hid_interfaces = [
    i
    for i in device_interfaces
    if i["usage_page"] == usage_page and i["usage"] == usage
]

if len(raw_hid_interfaces) == 0:
    print("cannot find interface")
    sys.exit(0)

with hid.Device(path=raw_hid_interfaces[0]["path"]) as d:
    print("Manufacturer: %s" % d.manufacturer)
    print("Product: %s" % d.product)

    data = [0x41]

    request_packet = [0x00] * 32  # First byte is Report ID
    request_packet[0 : len(data) + 1] = data

    print("Request:")
    print(request_packet)

    d.write(request_packet)

    response_packet = d.read(32, timeout=1000)

    print("Response:")
    print(response_packet)
