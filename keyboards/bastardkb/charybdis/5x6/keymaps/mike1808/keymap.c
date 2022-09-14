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
#include "drashna.h"
#include "wrappers.h"
#if defined(OLED_ENABLE)
#    include "oled/oled_stuff.h"
#endif // OLED_ENABLE

enum my_keycodes {
    MEDIAMODE = SAFE_RANGE,
};

// clang-format off
#define LAYOUT_charybdis_5x6_wrapper(...) LAYOUT_charybdis_5x6(__VA_ARGS__)
#define LAYOUT_charybdis_5x6_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A  \
  ) \
  LAYOUT_charybdis_5x6_wrapper( \
     KC_GRV,  ________________NUMBER_LEFT________________,            ________________NUMBER_RIGHT_______________, KC_MINS, \
     KC_TAB,   K01,    K02,     K03,     K04,     K05,                K06,     K07,     K08,     K09,     K0A,     K0B, \
     LALT_T(KC_ESC), K11, K12,  K13,     K14,     K15,                K16,     K17,     K18,     K19,     K1A,     RALT_T(K1B), \
     OS_LSFT, CTL_T(K21), K22,  K23,     K24,     K25,                K26,     K27,     K28,     K29, RCTL_T(K2A), OS_RSFT, \
                       OS_LGUI, OS_LALT,                                                OS_RALT, OS_RGUI, \
                                KC_SPC, BK_LWER,                                        DL_RAIS,  \
                                         SH_TT,   KC_CCCV,                     KC_ENT,  \
                                         KC_MUTE, TT(_MOUSE),      TT(_MOUSE), MO(_MEDIA) \
  )
#define LAYOUT_base_wrapper(...)       LAYOUT_charybdis_5x6_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT_LAYER_1] = LAYOUT_base_wrapper(
        _________________QWERTY_L1_________________, _________________QWERTY_R1_________________,
        _________________QWERTY_L2_________________, _________________QWERTY_R2_________________,
        _________________QWERTY_L3_________________, _________________QWERTY_R3_________________
    ),

    [_MOUSE] = LAYOUT_charybdis_5x6(
        _______, _______, _______, _______, _______, _______,                        DRGSCRL, DPI_RMOD,DPI_MOD, S_D_RMOD,S_D_MOD, SNP_TOG,
        _______, _______, _______, _______, _______, _______,                        KC_WH_U, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, DRGSCRL, _______,                        KC_WH_D, KC_BTN1, KC_BTN3, KC_BTN2, KC_BTN6, SNIPING,
        _______, _______, _______, _______, SNIPING, _______,                        KC_BTN7, KC_BTN4, KC_BTN5, KC_BTN8, _______, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 KC_BTN3,
                                                    KC_ACCEL, _______,               _______,
                                                     _______, _______,      _______, _______
    ),

    [_LOWER] = LAYOUT_charybdis_5x6_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                        _________________FUNC_RIGHT________________, KC_F11,
        _______, _________________LOWER_L1__________________,                        _________________LOWER_R1__________________, _______,
        _______, _________________LOWER_L2__________________,                        _________________LOWER_R2__________________, KC_PIPE,
        _______, _________________LOWER_L3__________________,                        _________________LOWER_R3__________________, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 _______,
                                                     KC_MPRV, KC_MNXT,               _______,
                                                     _______, KC_MPLY,      _______, _______
    ),
    [_RAISE] = LAYOUT_charybdis_5x6_wrapper(
        KC_F12,  _________________FUNC_LEFT_________________,                        _________________FUNC_RIGHT________________, KC_F11,
        KC_GRV,  _________________RAISE_L1__________________,                        _________________RAISE_R1__________________, _______,
        _______, _________________RAISE_L2__________________,                        _________________RAISE_R2__________________, KC_BSLS,
        _______, _________________RAISE_L3__________________,                        _________________RAISE_R3__________________, _______,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 _______,
                                                     _______, _______,               TT(_MEDIA),
                                                     _______, _______,      _______, _______
    ),
    [_ADJUST] = LAYOUT_charybdis_5x6_wrapper(
       QK_MAKE, _________________ADJUST_L0_________________,                        _______, _______, _______ , _______, _______, QK_BOOT,
          VRSN, _________________ADJUST_L1_________________,                        _________________ADJUST_R1_________________,  EE_CLR,
       KEYLOCK, _________________ADJUST_L2_________________,                        _________________ADJUST_R2_________________,  TG_MODS,
       _______, _________________ADJUST_L3_________________,                        _________________ADJUST_R3_________________,  KC_MPLY,
                           DEBUG, _______,                                                            OS_TOGG, _______,
                                            _______, QK_RBT,                                  KC_NUKE,
                                                     _______, _______,               _______,
                                                     _______, _______,      KC_NUKE, _______
    ),

    [_MEDIA] = LAYOUT_charybdis_5x6(
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                        KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_MUTE, KC_VOLU,
                          _______, _______,                                                            _______, _______,
                                            _______, _______,                                 _______,
                                                     _______, _______,               _______,
                                                     _______, _______,      _______, _______
    ),
};
// clang-format on

#if defined(OLED_ENABLE)
oled_rotation_t oled_init_keymap(oled_rotation_t rotation) {
    return OLED_ROTATION_90;
}
#endif // OLED_ENABLE

layer_state_t layer_state_set_keymap(layer_state_t state) {
    if (layer_state_cmp(state, _MEDIA)) {
        pointing_device_set_cpi(200);
    } else {
        pointing_device_set_cpi(charybdis_get_pointer_default_dpi());
    }
    return state;
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
#if defined(OLED_ENABLE)
    if (!process_record_user_oled(keycode, record)) {
        return false;
    }
#endif // OLED_ENABLE
    return true;
}

void keyboard_post_init_keymap(void) {
    // debug_enable = true;
    // debug_mouse  = true;

    // pimoroni_trackball_set_rgbw(0, 0, 0, 255);
}

report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
    mouse_xy_report_t x = mouse_report.x, y = mouse_report.y;

    static int mouse_x_buffer = 0, mouse_y_buffer = 0;

    if (layer_state_is(_MEDIA) && (x != 0 || y != 0)) {
        mouse_report.x = mouse_report.y = 0;

        mouse_x_buffer += x;
        mouse_y_buffer += y;

        if (abs(mouse_y_buffer) > TRACKBALL_MEDIA_BUFFER) {
            if (mouse_y_buffer > 0) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }

            mouse_y_buffer = 0;
        }

        if (abs(mouse_x_buffer) > TRACKBALL_MEDIA_BUFFER) {
            if (mouse_x_buffer > 0) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
            }

            mouse_x_buffer = 0;
        }
    }
    return mouse_report;
}
