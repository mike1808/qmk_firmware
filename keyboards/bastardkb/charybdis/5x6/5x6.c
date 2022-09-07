/*
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Publicw License as published by
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

#include "5x6.h"

// clang-format off
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    /* Key Matrix to LED index. */
    // Left split.
    {      0,      1,      2,      3,      4,     5 }, // Num row
    {     11,     10,      9,      8,      7,     6 }, // Top row
    {     12,     13,     14,     15,     16,    17 }, // Middle row
    {     23,     22,     21,     20,     19,    18 }, // Bottom row
    {     24,     25,     26,     27,     28,    29 }, // Thumb row
    { NO_LED, NO_LED, NO_LED, NO_LED,     31,    30 }, // Thumb cluster
    // Right split.
    {     37,     36,     35,     34,     33,     32 }, // Num row
    {     38,     39,     40,     41,     42,     43 }, // Top row
    {     49,     48,     47,     46,     45,     44 }, // Middle row
    {     50,     51,     52,     53,     54,     55 }, // Bottom row
    {     61,     60,     59,     58,     57,     56 }, // Thumb row
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }, // Thumb cluster
}, {
    /* LED index to physical position. */
    // Left split.
    {   0,   0 }, {   0,  12 }, {   0,  24 }, {   0,  36 }, {  0,   48 }, {  0,   60 }, 
    {  16,  60 }, {  16,  48 }, {  16,  36 }, {  16,  24 }, {  16,  12 }, {  16,   0 },
    {  32,   0 }, {  32,  12 }, {  32,  24 }, {  32,  36 }, {  32,  48 }, {  32,  60 },
    {  48,  60 }, {  48,  48 }, {  48,  36 }, {  48,  24 }, {  48,  12 }, {  48,   0 },
    {  64,   0 }, {  64,  12 }, {  64,  24 }, {  64,  36 }, {  64,  48 }, {  64,  60 },
    {  80,  60 }, {  80,  48 }, 
    // Right split.
    { 224,  60 }, { 224,  48 }, { 224,  36 }, { 224,  24 }, { 224, 12 }, { 224, 0 },
    { 208,   0 }, { 208,  12 }, { 208,  24 }, { 208,  36 }, { 208, 48 }, { 208, 60 },
    { 192,  60 }, { 192,  48 }, { 192,  36 }, { 192,  24 }, { 192, 12 }, { 192, 0 },
    { 176,   0 }, { 176,  12 }, { 176,  24 }, { 176,  36 }, { 176, 48 }, { 176, 60 },
    { 160,  60 }, { 160,  48 }, { 160,  36 }, { 160,  24 }, { 160, 12 }, { 160, 0 }
}, {
    /* LED index to flag. */
    // Left split.
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, 
    // Right split.
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
} };
#endif
// clang-format on

#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    /* Left hand, matrix positions */
    {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
    {{5, 7}, {4, 7}, {3, 7}, {2, 7}, {1, 7}, {0, 7}},
    {{5, 8}, {4, 8}, {3, 8}, {2, 8}, {1, 8}, {0, 8}},
    {{5, 9}, {4, 9}, {3, 9}, {2, 9}, {1, 9}, {0, 9}},
    {{5, 10}, {4, 10}, {3, 10}, {2, 10}, {1, 10}, {0, 10}},
    {{5, 11}, {4, 11}, {3, 11}, {2, 11}, {1, 11}, {0, 11}},
    /* Right hand, matrix positions */
    {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
    {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
    {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
    {{5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}, {0, 3}},
    {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
    {{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}}};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif
#endif
