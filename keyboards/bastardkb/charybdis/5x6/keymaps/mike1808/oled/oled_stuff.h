/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "quantum.h"
#include "oled_driver.h"

bool            process_record_user_oled(uint16_t keycode, keyrecord_t *record);
oled_rotation_t oled_init_keymap(oled_rotation_t rotation);
void            oled_timer_reset(void);
void            render_keylogger_status(uint8_t col, uint8_t line);
void            render_default_layer_state(uint8_t col, uint8_t line);
void            render_layer_state(uint8_t col, uint8_t line);
void            render_keylock_status(led_t led_usb_state, uint8_t col, uint8_t line);
void            render_matrix_scan_rate(uint8_t col, uint8_t line);
void            render_mod_status(uint8_t modifiers, uint8_t col, uint8_t line);
void            render_bootmagic_status(uint8_t col, uint8_t line);
void            render_user_status(uint8_t col, uint8_t line);
void            render_wpm(uint8_t col, uint8_t line);
void            render_pointing_dpi_status(uint16_t cpi, uint8_t col, uint8_t line);
void            render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset);
void            render_unicode_mode(uint8_t col, uint8_t line);
void            render_rgb_hsv(uint8_t col, uint8_t line);
void            render_mouse_mode(uint8_t col, uint8_t line);
void            render_rgb_effect(uint8_t col, uint8_t line);
void            matrix_scan_oled(void);
void            render_auto_shift(uint8_t col, uint8_t line);

void oled_pan_section(bool left, uint16_t y_start, uint16_t y_end, uint16_t x_start, uint16_t x_end);

#define OLED_RENDER_KEYLOGGER "KL"
#ifndef OLED_KEYLOGGER_LENGTH
#    define OLED_KEYLOGGER_LENGTH 5
#endif

#define OLED_RENDER_LAYOUT_NAME "LT"
#define OLED_RENDER_LAYOUT_QWERTY " QW"
#define OLED_RENDER_LAYOUT_COLEMAK_DH " cmDH"
#define OLED_RENDER_LAYOUT_COLEMAK " COLE"
#define OLED_RENDER_LAYOUT_DVORAK " DVRK"
#define OLED_RENDER_LAYOUT_WORKMAN " WKMN"
#define OLED_RENDER_LAYOUT_NORMAN " NORM"
#define OLED_RENDER_LAYOUT_MALTRON " MLTN"
#define OLED_RENDER_LAYOUT_EUCALYN " ECLN"
#define OLED_RENDER_LAYOUT_CARPLAX " CRPX"

#define OLED_RENDER_LAYER_NAME "LR"
#define OLED_RENDER_LAYER_LOWER "L"
#define OLED_RENDER_LAYER_RAISE "R"
#define OLED_RENDER_LAYER_ADJUST "A"
#define OLED_RENDER_LAYER_MODS " M"

#define OLED_RENDER_LOCK_NAME "Lock:"
#define OLED_RENDER_LOCK_NUML "Nu"
#define OLED_RENDER_LOCK_CAPS "Ca"
#define OLED_RENDER_LOCK_SCLK "S"

#define OLED_RENDER_MODS_NAME "Mods: "
#define OLED_RENDER_MODS_SFT "Sh"
#define OLED_RENDER_MODS_CTL "Ct"
#define OLED_RENDER_MODS_ALT "Al\n"
#define OLED_RENDER_MODS_GUI "G\n"

#define OLED_RENDER_BOOTMAGIC_NAME "BTMGK"
#define OLED_RENDER_BOOTMAGIC_NKRO "NK"
#define OLED_RENDER_BOOTMAGIC_GRV "GRV"
#define OLED_RENDER_BOOTMAGIC_ONESHOT "1S"
#define OLED_RENDER_BOOTMAGIC_SWAP "SWAP"
#define OLED_RENDER_BOOTMAGIC_CAPS "CAPS"

#define OLED_RENDER_USER_NAME "USER:"
#define OLED_RENDER_USER_ANIM "A"
#define OLED_RENDER_USER_LAYR "Layr"
#define OLED_RENDER_USER_NUKE "Nuke"

#define OLED_RENDER_WPM_COUNTER "W: "

extern char keylog_str[OLED_KEYLOGGER_LENGTH];

#ifndef OLED_WPM_GRAPH_MAX_WPM
#    define OLED_WPM_GRAPH_MAX_WPM 120
#endif
#ifndef OLED_WPM_GRAPH_REFRESH_INTERVAL
#    define OLED_WPM_GRAPH_REFRESH_INTERVAL 300
#endif
#ifndef OLED_WPM_GRAPH_AREA_FILL_INTERVAL
#    define OLED_WPM_GRAPH_AREA_FILL_INTERVAL 3
#endif
#ifndef OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL
#    define OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL 3
#endif
#ifndef OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS
#    define OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS 2
#endif

#define OLED_DEFAULT_LAYER_TIMEOUT 3000
