/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 John Ezra - wpm graph
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

#include "drashna.h"
#include "oled_stuff.h"
#ifdef UNICODE_COMMON_ENABLE
#    include "process_unicode_common.h"
#    include "keyrecords/unicode.h"
#endif
#if defined(AUTOCORRECTION_ENABLE)
#    include "keyrecords/autocorrection/autocorrection.h"
#endif
#include <string.h>

#include "rgb_effects_names.h"

// #define OLED_DISPLAY_VERBOSE

bool is_oled_enabled = true;

extern bool host_driver_disabled;

uint32_t        oled_timer                        = 0;
char            keylog_str[OLED_KEYLOGGER_LENGTH] = {0};
static uint16_t log_timer                         = 0;
uint32_t        rgb_effect_timer                  = 0;
uint32_t        autoshift_timer                   = 0;

enum oled_render_mode {
    OLED_RENDER_LAYER_DEFAULT = 0,
    OLED_RENDER_LAYER_RGB     = 1,
    OLED_RENDER_LAYER_AUTOSHIFT,
    OLED_RENDER_LAYER_LAST,
};

int current_render_mode = OLED_RENDER_LAYER_DEFAULT;

// clang-format off
static const char PROGMEM code_to_name[256] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128,0xD5,0xD6,0xD7,0xD8,0xD9,0xDA,  // 3x
    0xDB,0xDC,0xDD,0xDE,0XDF,0xFB,'P', 'S',  19, ' ',  17,  30,  16,  16,  31,  26,  // 4x
     27,  25,  24, 'N', '/', '*', '-', '+',  23, '1', '2', '3', '4', '5', '6', '7',  // 5x
    '8', '9', '0', '.','\\', 'A',   0, '=', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ',   0, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  24,  26,  24,  // Ex
     25,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,0x9D,  24,  25,  27,  26, ' ', ' ', ' '   // Fx
};
// clang-format on

/**
 * @brief parses pressed keycodes and saves to buffer
 *
 * @param keycode Keycode pressed from switch matrix
 * @param record keyrecord_t data structure
 */
void add_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        if (((keycode & 0xFF) == KC_BSPC) && mod_config(get_mods() | get_oneshot_mods()) & MOD_MASK_CTRL) {
            memset(keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
            return;
        }
        if (record->tap.count) {
            keycode &= 0xFF;
        } else if (keycode > 0xFF) {
            return;
        }
    }
    if (keycode > 0xFF) {
        return;
    }

    memmove(keylog_str, keylog_str + 1, OLED_KEYLOGGER_LENGTH - 1);

    if (keycode < ARRAY_SIZE(code_to_name)) {
        keylog_str[(OLED_KEYLOGGER_LENGTH - 1)] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

/**
 * @brief Keycode handler for oled display.
 *
 * This adds pressed keys to buffer, but also resets the oled timer
 *
 * @param keycode Keycode from matrix
 * @param record keyrecord data struture
 * @return true
 * @return false
 */
bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer_reset();
#if defined(KEYLOGGER_ENABLE)
        add_keylog(keycode, record);
#endif
        switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
            case RGB_TOG ... RGB_MODE_RGBTEST:
                rgb_effect_timer = timer_read32();
                break;
#endif
#ifdef AUTO_SHIFT_ENABLE
            case KC_ASUP ... KC_ASOFF:
                autoshift_timer = timer_read32();
                break;
#endif
        }
    }
    return true;
}

void oled_timer_reset(void) {
    oled_timer = timer_read32();
}
/**
 * @brief Renders keylogger buffer to oled
 *
 */
void render_keylogger_status(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
    oled_write(keylog_str, false);
}

/**
 * @brief Renders default layer state (aka layout) to oled
 *
 */
void render_default_layer_state(uint8_t col, uint8_t line) {
#ifdef OLED_DISPLAY_VERBOSE
    oled_set_cursor(col, line);
#endif
    oled_write_P(PSTR(OLED_RENDER_LAYOUT_NAME), false);
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_QWERTY), false);
            break;
        case _COLEMAK_DH:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK_DH), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_COLEMAK), false);
            break;
        case _DVORAK:
            oled_write_P(PSTR(OLED_RENDER_LAYOUT_DVORAK), false);
            break;
    }
#ifdef OLED_DISPLAY_VERBOSE
    oled_advance_page(true);
#endif
}

/**
 * @brief Renders the active layers to the OLED
 *
 */
void render_layer_state(uint8_t col, uint8_t line) {
    // clang-format off
    static const char PROGMEM tri_layer_image[][3][24] = {
        // base
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0x5D, 0x3E, 0x3E, 0x7C, 0x7C, 0xF8,
                0xF8, 0x7C, 0x7C, 0x3E, 0x3E, 0x5D,
                0x5D, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // raise
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0xC0,
                0xC0, 0xE0, 0xE0, 0xF0, 0xF0, 0xF8,
                0xF8, 0xF0, 0xF0, 0xE0, 0xE0, 0xC0,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x55,
                0x55, 0x23, 0x23, 0x47, 0x47, 0x8F,
                0x8F, 0x47, 0x47, 0x23, 0x23, 0x55,
                0x55, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x02, 0x02, 0x04, 0x04, 0x08,
                0x08, 0x04, 0x04, 0x02, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // lower
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0x40, 0x20, 0x20, 0x10, 0x10, 0x08,
                0x08, 0x10, 0x10, 0x20, 0x20, 0x40,
                0x40, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0xD5,
                0xD5, 0xE2, 0xE2, 0xC4, 0xC4, 0x88,
                0x88, 0xC4, 0xC4, 0xE2, 0xE2, 0xD5,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x03, 0x07, 0x07, 0x0F,
                0x0F, 0x07, 0x07, 0x03, 0x03, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // adjust
        {
            {
                0x00, 0x00, 0x00, 0x80, 0x80, 0x40,
                0xC0, 0x60, 0xA0, 0x50, 0xB0, 0x58,
                0xA8, 0x50, 0xB0, 0x60, 0xA0, 0x40,
                0xC0, 0x80, 0x80, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x88, 0x88, 0x5D,
                0xD5, 0x6B, 0xB6, 0x6D, 0xD6, 0xAD,
                0xDA, 0x6D, 0xD6, 0x6B, 0xB6, 0x5D,
                0xD5, 0x88, 0x88, 0x00, 0x00, 0x00
            },
            {
                0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                0x01, 0x03, 0x02, 0x05, 0x06, 0x0D,
                0x0A, 0x05, 0x06, 0x03, 0x02, 0x01,
                0x01, 0x00, 0x00, 0x00, 0x00, 0x00
            }
        },
        // blank
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 }
        },
        // mouse
        {
            { 0,  0,  0,  0,  0,  0,  0,  0,192, 32, 32, 32,160, 32, 32, 32,192,  0,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,240, 15,  0,  0,  0,  3,  0,  0,  0, 15,240,  0,  0,  0,  0,  0,  0 },
            { 0,  0,  0,  0,  0,  0,  0,  3,  6,  4,  4,  4,  4,  4,  4,  4,  6,  3,  0,  0,  0,  0,  0,  0 }
        }
    };

  #define L_BASE 0
  #define L_RAISE 1
  #define L_LOWER 2
  #define L_ADJUST 3
  #define L_BLANK 4
  #define L_MOUSE 5

    // clang-format on
    uint8_t layer_is[4] = {L_BASE, L_BLANK};
    if (layer_state_is(_ADJUST)) {
        layer_is[0] = L_ADJUST;
    } else if (layer_state_is(_RAISE)) {
        layer_is[0] = L_RAISE;
    } else if (layer_state_is(_LOWER)) {
        layer_is[0] = L_LOWER;
    }

    if (layer_state_is(_MOUSE)) {
        layer_is[1] = L_MOUSE;
    }

    oled_set_cursor(col, line);
    oled_write_raw_P(tri_layer_image[layer_is[0]][0], sizeof(tri_layer_image[0][0]));

    oled_set_cursor(col, line + 1);
    oled_write_raw_P(tri_layer_image[layer_is[0]][1], sizeof(tri_layer_image[0][0]));

    oled_set_cursor(col, line + 2);
    oled_write_raw_P(tri_layer_image[layer_is[0]][2], sizeof(tri_layer_image[0][0]));

    // oled_set_cursor(col, line + 3);
    // oled_write_raw_P(tri_layer_image[layer_is[1]][0], sizeof(tri_layer_image[0][0]));
    // oled_set_cursor(col, line + 4);
    // oled_write_raw_P(tri_layer_image[layer_is[1]][1], sizeof(tri_layer_image[0][0]));
    // oled_set_cursor(col, line + 5);
    // oled_write_raw_P(tri_layer_image[layer_is[1]][2], sizeof(tri_layer_image[0][0]));
}

/**
 * @brief Renders the current lock status to oled
 *
 * @param led_usb_state Current keyboard led state
 */
void render_keylock_status(led_t led_usb_state, uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);

#ifdef CAPS_WORD_ENABLE
    led_usb_state.caps_lock |= is_caps_word_on();
#endif
    oled_write_P(PSTR(OLED_RENDER_LOCK_NUML), led_usb_state.num_lock);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_LOCK_CAPS), led_usb_state.caps_lock);
}

/**
 * @brief Renders the matrix scan rate to the host system
 *
 */
void render_matrix_scan_rate(uint8_t col, uint8_t line) {
#ifdef DEBUG_MATRIX_SCAN_RATE
    oled_set_cursor(col, line);
    oled_write(get_u16_str(get_matrix_scan_rate(), ' '), false);
#endif
}

/**
 * @brief Renders the modifier state
 *
 * @param modifiers Modifiers to check against (real, weak, onesheot, etc;)
 */
void render_mod_status(uint8_t modifiers, uint8_t col, uint8_t line) {
    static const char PROGMEM mod_status[5][3] = {{0xE8, 0xE9, 0}, {0xE4, 0xE5, 0}, {0xE6, 0xE7, 0}, {0xEA, 0xEB, 0}, {0xEC, 0xED, 0}};
    oled_set_cursor(col, line);

#if defined(OLED_DISPLAY_VERBOSE)
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_LSHIFT)));
    oled_write_P(mod_status[!keymap_config.swap_lalt_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_LGUI)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_LALT)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_LCTL)));
    oled_write_P(mod_status[1], (modifiers & MOD_BIT(KC_RCTL)));
    oled_write_P(mod_status[2], (modifiers & MOD_BIT(KC_RALT)));
    oled_write_P(mod_status[!keymap_config.swap_lalt_lgui ? 3 : 4], (modifiers & MOD_BIT(KC_RGUI)));
    oled_write_P(mod_status[0], (modifiers & MOD_BIT(KC_RSHIFT)));
#else
    oled_write_P(mod_status[0], (modifiers & MOD_MASK_SHIFT));
    oled_write_P(mod_status[!keymap_config.swap_lalt_lgui ? 3 : 4], (modifiers & MOD_MASK_GUI));
    oled_write_P(PSTR(" "), false);
    oled_write_P(mod_status[2], (modifiers & MOD_MASK_ALT));
    oled_write_P(mod_status[1], (modifiers & MOD_MASK_CTRL));
#endif
}

#ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#endif

void render_bootmagic_status(uint8_t col, uint8_t line) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    oled_set_cursor(col, line);

    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(logo[1][0], false);
    } else {
        oled_write_P(logo[0][0], false);
    }

#ifdef SWAP_HANDS_ENABLE
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_SWAP), swap_hands);
    oled_write_P(PSTR(" "), false);
#else
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
#endif

#if defined(AUTOCORRECTION_ENABLE) || defined(AUTOCORRECT_ENABLE)
    oled_write_P(PSTR("CRCT"), autocorrect_is_enabled());
    oled_write_P(PSTR(" "), false);
#endif

    oled_set_cursor(col, line + 1);

    if (keymap_config.swap_lalt_lgui) {
        oled_write_P(logo[1][1], false);
    } else {
        oled_write_P(logo[0][1], false);
    }

    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_ONESHOT), is_oneshot_enabled());
}

#if defined(CUSTOM_POINTING_DEVICE)
extern bool tap_toggling;
#endif

void render_user_status(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);

    oled_write_P(PSTR(OLED_RENDER_USER_ANIM), userspace_config.rgb_matrix_idle_anim);
    oled_write_P(PSTR(" "), false);

#if defined(CUSTOM_POINTING_DEVICE)
    static const char PROGMEM mouse_lock[3] = {0xF2, 0xF3, 0};
    oled_write_P(mouse_lock, tap_toggling);
#endif

    static const char PROGMEM rgb_layer_status[2][3] = {{0xEE, 0xEF, 0}, {0xF0, 0xF1, 0}};
    oled_write_P(rgb_layer_status[userspace_config.rgb_layer_change], false);
    static const char PROGMEM cat_mode[2][3] = {{0xF8, 0xF9, 0}, {0xF6, 0xF7, 0}};
    oled_write_P(cat_mode[0], host_driver_disabled);

#if defined(UNICODE_COMMON_ENABLE)
    static const char PROGMEM uc_mod_status[5][3] = {{0xEC, 0xED, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0x20, 0x20, 0}, {0xEA, 0xEB, 0}};
    oled_write_P(uc_mod_status[get_unicode_input_mode()], false);
#endif

    if (userspace_config.nuke_switch) {
#if !defined(OLED_DISPLAY_VERBOSE)
        oled_write_P(PSTR(" "), false);
#endif
        static const char PROGMEM nukem_good[2] = {0xFA, 0};
        oled_write_P(nukem_good, false);
#if !defined(OLED_DISPLAY_VERBOSE)
        oled_advance_page(true);
#endif
    }
#if defined(OLED_DISPLAY_VERBOSE)
    oled_advance_page(true);
#endif
}

void render_rgb_hsv(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
#ifdef RGB_MATRIX_ENABLE
    oled_write(get_u16_str(rgb_matrix_get_hue(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u16_str(rgb_matrix_get_sat(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u16_str(rgb_matrix_get_val(), ' '), false);
#elif RGBLIGHT_ENABLE
    oled_write(get_u16_str(rgblight_get_hue(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u16_str(rgblight_get_sat(), ' '), false);
    oled_write_P(PSTR(", "), false);
    oled_write(get_u16_str(rgblight_get_val(), ' '), false);
#endif
}

void render_wpm(uint8_t col, uint8_t line) {
#ifdef WPM_ENABLE
    oled_set_cursor(col, line);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
#endif
}

//=============  USER CONFIG PARAMS  ===============
// wpm graph originally designed by john-ezra

// for 128x128:
// max_lines_graph          = 54;
// vertical_offset          = 64;
// for 128x64:
// max_lines_graph          = 64;
// vertical_offset          = 0;

void render_wpm_graph(uint8_t max_lines_graph, uint8_t vertical_offset) {
#ifdef WPM_ENABLE
    static uint16_t timer   = 0;
    static uint8_t  x       = OLED_DISPLAY_HEIGHT - 1;
    uint8_t         currwpm = get_current_wpm();
    float           max_wpm = OLED_WPM_GRAPH_MAX_WPM;

    if (timer_elapsed(timer) > OLED_WPM_GRAPH_REFRESH_INTERVAL) {                  // check if it's been long enough before refreshing graph
        x = (max_lines_graph - 1) - ((currwpm / max_wpm) * (max_lines_graph - 1)); // main calculation to plot graph line
        for (uint8_t i = 0; i <= OLED_WPM_GRAPH_GRAPH_LINE_THICKNESS - 1; i++) {   // first draw actual value line
            oled_write_pixel(3, x + i + vertical_offset, true);
        }
#    ifdef OLED_WPM_GRAPH_VERTICAL_LINE
        static uint8_t vert_count = 0;
        if (vert_count == OLED_WPM_GRAPH_VERTCAL_LINE_INTERVAL) {
            vert_count = 0;
            while (x <= (max_lines_graph - 1)) {
                oled_write_pixel(3, x + vertical_offset, true);
                x++;
            }
        } else {
            for (uint8_t i = (max_lines_graph - 1); i > x; i--) {
                if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                    oled_write_pixel(3, i + vertical_offset, true);
                }
            }
            vert_count++;
        }
#    else
        for (int i = (max_lines_graph - 1); i > x; i--) {
            if (i % OLED_WPM_GRAPH_AREA_FILL_INTERVAL == 0) {
                oled_write_pixel(3, i + vertical_offset, true);
            }
        }
#    endif
#    include <math.h>
        uint8_t y_start  = ceil(vertical_offset / 8);
        uint8_t y_length = y_start + ceil(max_lines_graph / 8);
        oled_pan_section(false, y_start, y_length, 3, 125); // then move the entire graph one pixel to the right
        timer = timer_read();                               // refresh the timer for the next iteration
    }
#endif
}

#if defined(POINTING_DEVICE_ENABLE)
void render_pointing_dpi_status(uint16_t cpi, uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);
    oled_write(get_u16_str(cpi, ' '), false);
}
#endif

void render_unicode_mode(uint8_t col, uint8_t line) {
#ifdef CUSTOM_UNICODE_ENABLE
    oled_set_cursor(col, line);
    oled_write_ln_P(PSTR("Unicode:"), false);
    switch (typing_mode) {
        case UCTM_WIDE:
            oled_write_P(PSTR("        Wide"), false);
            break;
        case UCTM_SCRIPT:
            oled_write_P(PSTR("      Script"), false);
            break;
        case UCTM_BLOCKS:
            oled_write_P(PSTR("      Blocks"), false);
            break;
        case UCTM_REGIONAL:
            oled_write_P(PSTR("    Regional"), false);
            break;
        case UCTM_AUSSIE:
            oled_write_P(PSTR("      Aussie"), false);
            break;
        case UCTM_ZALGO:
            oled_write_P(PSTR("       Zalgo"), false);
            break;
        case UCTM_NO_MODE:
            oled_write_P(PSTR("      Normal"), false);
            break;
        default:
            oled_write_P(PSTR("     Unknown"), false);
            break;
    }
#endif
}

void render_mouse_mode(uint8_t col, uint8_t line) {
#if defined(POINTING_DEVICE_ENABLE)
    // credit and thanks to jaspertandy on discord for these images
    static const char PROGMEM mouse_logo[5][2][16] = {// mouse icon
                                                      {{0, 0, 0, 252, 2, 2, 2, 58, 2, 2, 2, 252, 0, 0, 0, 0}, {0, 0, 63, 96, 64, 64, 64, 64, 64, 64, 64, 96, 63, 0, 0, 0}},
                                                      // mouse icon filled
                                                      {{0, 0, 0, 252, 254, 254, 254, 194, 254, 254, 254, 252, 0, 0, 0, 0}, {0, 0, 63, 127, 127, 127, 127, 127, 127, 127, 127, 127, 63, 0, 0, 0}},
                                                      // mouse icon inverted
                                                      {{255, 255, 255, 3, 253, 253, 253, 197, 253, 253, 253, 3, 255, 255, 255, 255}, {255, 255, 192, 159, 191, 191, 191, 191, 191, 191, 191, 159, 192, 255, 255, 255}},
                                                      // crosshair icon
                                                      {{128, 240, 136, 228, 146, 138, 202, 127, 202, 138, 146, 228, 136, 240, 128, 0}, {0, 7, 8, 19, 36, 40, 41, 127, 41, 40, 36, 19, 8, 7, 0, 0}},
                                                      // dragscroll icon
                                                      {{0, 0, 112, 136, 156, 2, 15, 1, 15, 2, 140, 68, 56, 0, 0, 0}, {0, 0, 2, 6, 15, 28, 60, 124, 60, 28, 15, 6, 2, 0, 0, 0}}};

    uint8_t image_index = 0;

    if (layer_state_is(_MOUSE)) {
        image_index = 1;

#    if defined(CUSTOM_POINTING_DEVICE)
        if (tap_toggling) {
            image_index = 2;
        }
#    endif

        if (charybdis_get_pointer_sniping_enabled()) {
            image_index = 3;
        } else if (charybdis_get_pointer_dragscroll_enabled()) {
            image_index = 4;
        }
    }

    oled_set_cursor(col + 1, line);
    oled_write_raw_P(mouse_logo[image_index][0], 16);
    oled_set_cursor(col + 1, line + 1);
    oled_write_raw_P(mouse_logo[image_index][1], 16);
#endif
}

void render_status_right(void) {}

void render_mode_default(void) {
    render_bootmagic_status(0, 0);
    render_layer_state(0, 2);
    render_mod_status(get_mods() | get_oneshot_mods(), 0, 5);
    render_pointing_dpi_status(charybdis_get_pointer_sniping_enabled() ? charybdis_get_pointer_sniping_dpi() : charybdis_get_pointer_default_dpi(), 0, 8);
    render_keylock_status(host_keyboard_led_state(), 0, 10);
    render_mouse_mode(0, 12);

#if defined(KEYLOGGER_ENABLE)
    render_keylogger_status(0, 15);
#elif defined(DEBUG_MATRIX_SCAN_RATE)
    render_matrix_scan_rate(0, 15);
#elif defined(WPM_ENABLE)
    render_wpm(0, 15);
#endif
}

void render_mode_rgb(void) {
    render_rgb_effect(0, 0);
}

void render_current_mode(void) {
    switch (current_render_mode) {
        case OLED_RENDER_LAYER_DEFAULT:
            render_mode_default();
            break;
        case OLED_RENDER_LAYER_RGB:
            render_mode_rgb();
            break;
        case OLED_RENDER_LAYER_AUTOSHIFT:
            render_auto_shift(0, 0);
            break;
    }
}

void render_status_left(void) {
    int new_mode = current_render_mode;
    if (rgb_effect_timer != 0 && timer_elapsed32(rgb_effect_timer) < OLED_DEFAULT_LAYER_TIMEOUT) {
        new_mode = OLED_RENDER_LAYER_RGB;
    } else if (autoshift_timer != 0 && timer_elapsed32(autoshift_timer) < OLED_DEFAULT_LAYER_TIMEOUT) {
        new_mode = OLED_RENDER_LAYER_AUTOSHIFT;
    } else {
        new_mode = OLED_RENDER_LAYER_DEFAULT;
    }

    if (new_mode != current_render_mode) {
        oled_clear();
    }

    current_render_mode = new_mode;

    render_current_mode();
}

void render_rgb_effect(uint8_t col, uint8_t line) {
    oled_set_cursor(col, line);

    uint8_t mode  = rgb_matrix_get_mode();
    HSV     hsv   = rgb_matrix_get_hsv();
    uint8_t speed = rgb_matrix_get_speed();

    oled_write_P(PSTR(" RGB "), true);
    oled_set_cursor(col, ++line);
    oled_write(get_u8_str(mode, ' '), false);
    line++;
    oled_set_cursor(col, ++line);
    oled_write_P(get_rgb_matrix_anim_text(mode), false);

    line += 7;
    oled_set_cursor(col, line);

    oled_write_P(PSTR("H"), true);
    oled_advance_char();
    oled_write(get_u8_str(hsv.h, ' '), false);
    oled_set_cursor(col, ++line);
    oled_write_P(PSTR("S"), true);
    oled_advance_char();
    oled_write(get_u8_str(hsv.s, ' '), false);
    oled_set_cursor(col, ++line);
    oled_write_P(PSTR("V"), true);
    oled_advance_char();
    oled_write(get_u8_str(hsv.v, ' '), false);
    oled_set_cursor(col, ++line);

    oled_write_P(PSTR("P"), true);
    oled_advance_char();
    oled_write(get_u8_str(speed, ' '), false);
    oled_set_cursor(col, ++line);
}

void render_auto_shift(uint8_t col, uint8_t line) {
#ifdef AUTO_SHIFT_ENABLE
    oled_set_cursor(col, line);

    oled_write_P(PSTR("AUTO "), true);
    oled_write_P(PSTR("SHIFT"), true);
    line += 2;
    oled_set_cursor(col, ++line);

    uint16_t timeout = get_generic_autoshift_timeout();
    bool     enabled = get_autoshift_state();

    if (!enabled) {
        oled_write_P(PSTR(" OFF "), false);
        return;
    }

    oled_write_P(PSTR(" ON  "), true);
    oled_set_cursor(col, ++line);
    oled_set_cursor(col, ++line);
    oled_write(get_u16_str(timeout, ' '), false);
#endif // AUTO_SHIFT_ENABLE
}

__attribute__((weak)) oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return rotation;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        memset(keylog_str, ' ', OLED_KEYLOGGER_LENGTH);
    }

    oled_clear();
    oled_render();
    return oled_init_keymap(rotation);
}

__attribute__((weak)) bool oled_task_keymap(void) {
    return true;
}

bool oled_task_user(void) {
    oled_on();

    if (!oled_task_keymap()) {
        return false;
    }

    render_status_left();

    return false;
}

extern bool oled_initialized;

__attribute__((weak)) void matrix_scan_oled(void) {
    is_oled_enabled = !(timer_elapsed32(oled_timer) > 60000);
}
