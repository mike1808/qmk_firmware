package main

import (
	"log"

	"github.com/karalabe/hid"
)

const (
	VENDOR_ID  = 0x320F
	PRODUCT_ID = 0x5044
	USAGE_PAGE = 0xFF60
	USAGE      = 0x61
)

func main() {
	if !hid.Supported() {
		log.Fatal("USB HID is not supported")
	}

	devices := hid.Enumerate(VENDOR_ID, PRODUCT_ID)
	var deviceInfo hid.DeviceInfo
	for _, d := range devices {
		if d.UsagePage == USAGE_PAGE && d.Usage == USAGE {
			deviceInfo = d
			break
		}
	}

	if deviceInfo.Path == "" {
		log.Fatalf("Cannot find device with VID = %X, PID = %X, Usage Page = %X, Usage = %X\n", VENDOR_ID, PRODUCT_ID, USAGE_PAGE, USAGE)
	}

	device, err := deviceInfo.Open()
	if err != nil {
		log.Fatalf("Cannot open device: %v\n", err)
	}

	defer device.Close()

	data := []byte{
		0x01, 0x53, 0x43, 0x12,
	}

	packet := make([]byte, 33)
	for i, b := range data {
		packet[1+i] = b
	}

	n, err := device.Write(packet)
	if err != nil {
		log.Fatalf("Cannot send data to the device: %v\n", err)
	}
	if n == 0 {
		log.Fatalf("No data was sent to the device\n")
	}

	log.Printf("Wrote %d bytes\n", n)
}
