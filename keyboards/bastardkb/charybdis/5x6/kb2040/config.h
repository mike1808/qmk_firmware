/*
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "pins.h"

/* Key matrix configuration. */
#define MATRIX_COL_PINS \
    { PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7 }

#define MATRIX_ROW_PINS \
    { PIN_D8, PIN_D9, PIN_D10, PIN_A1, PIN_A2, PIN_A3 }

#define MATRIX_COL_PINS_RIGHT \
    { PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7 }

#define MATRIX_ROW_PINS_RIGHT \
    { PIN_D8, PIN_D9, NO_PIN, PIN_A1, PIN_A2, PIN_A3 }

#ifdef DIODE_DIRECTION
#    undef DIODE_DIRECTION
#endif // DIODE_DIRECTION
#define DIODE_DIRECTION ROW2COL

/* Handedness. */
// #define EE_HANDS
// #define MASTER_LEFT
// #define MASTER_RIGHT

/* serial.c configuration (for split keyboard). */
#define SERIAL_PIO_USE_PIO1
// #define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN PIN_TX
#define SERIAL_USART_RX_PIN PIN_RX
#define SERIAL_USART_TIMEOUT 100
#define SERIAL_USART_SPEED (2 * 1024 * 1024)

/* RGB settings. */
#define RGB_DI_PIN PIN_A0

/* SPI & PMW3360 settings. */
// #define SPI_DRIVER SPID1
// #define SPI_SCK_PIN GP19
// #define SPI_MOSI_PIN GP19
// #define SPI_MISO_PIN GP20
// #define PMW33XX_CS_PIN GP10

// #undef POINTING_DEVICE_INVERT_X
// #undef POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_INVERT_Y

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

// settings for the oled keyboard demo with Adafruit 0.91" OLED display on the Stemma QT port
#define OLED_DISPLAY_128X32
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP12
#define I2C1_SCL_PIN GP13

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_USB_DETECT

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0
#define BOOTMAGIC_LITE_EEPROM_ROW 0
#define BOOTMAGIC_LITE_EEPROM_COLUMN 1

#define BOOTMAGIC_LITE_ROW_RIGHT 6
#define BOOTMAGIC_LITE_COLUMN_RIGHT 5
#define BOOTMAGIC_LITE_EEPROM_ROW_RIGHT 6
#define BOOTMAGIC_LITE_EEPROM_COLUMN_RIGHT 4
