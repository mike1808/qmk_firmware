/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#define EE_HANDS

#define TAPPING_TERM 175
#define FAST_TAPPING_TERM 150
#define TAPPING_TERM_PER_KEY
// tap-preferred flavor from ZMK
#define IGNORE_MOD_TAP_INTERRUPT
// #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY


#undef ONESHOT_TIMEOUT
#define ONESHOT_TIMEOUT 1000


#undef POINTING_DEVICE_INVERT_X
#undef POINTING_DEVICE_INVERT_Y
// #define POINTING_DEVICE_DEBUG

#if defined(POINTING_DEVICE_DRIVER_pmw3360)
#    define PMW33XX_CS_PIN GP10
#    define POINTING_DEVICE_INVERT_Y
#    define PMW33XX_LIFTOFF_DISTANCE 0x03
#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
#    define POINTING_DEVICE_INVERT_X
#    define POINTING_DEVICE_INVERT_Y

#    define CIRQUE_PINNACLE_DIAMETER_MM 40
#    define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X
#    define CIRQUE_PINNACLE_CURVED_OVERLAY
#    define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#    define CIRQUE_PINNACLE_TAP_ENABLE
#    define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#endif

#define CHARYBDIS_CONFIG_SYNC
#define CHARYBDIS_DRAGSCROLL_REVERSE_X
#define CHARYBDIS_DRAGSCROLL_REVERSE_Y
#define CHARYBDIS_DRAGSCROLL_DPI 200
#define CHARYBDIS_DRAGSCROLL_BUFFER_SIZE 6

#define TRACKBALL_MEDIA_BUFFER 6
#define TRACKBALL_MEDIA_INVERT_Y

#define AUTO_SHIFT_REPEAT
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
