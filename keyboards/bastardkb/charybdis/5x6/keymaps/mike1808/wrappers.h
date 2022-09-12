// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2020 @jola5
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "drashna.h"
/*
Since our quirky block definitions are basically a list of comma separated
arguments, we need a wrapper in order for these definitions to be
expanded before being used as arguments to the LAYOUT_xxx macro.
*/

/*
Blocks for each of the four major keyboard layouts
Organized so we can quickly adapt and modify all of them
at once, rather than for each keyboard, one at a time.
And this allows for much cleaner blocks in the keymaps.
For instance Tap/Hold for Control on all of the layouts

NOTE: These are all the same length.  If you do a search/replace
  then you need to add/remove underscores to keep the
  lengths consistent.
Cinemark
*/
// clang-format off

// add back slash
#undef _________________QWERTY_R1_________________
#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS

// swap RAISE_R2 and RAISE_R3 to move navigation to the home row
#undef _________________RAISE_R2__________________ 
#define _________________RAISE_R2__________________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
#undef _________________RAISE_R3__________________
#define _________________RAISE_R3__________________       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______ 

#undef _________________LOWER_R2__________________
#undef _________________LOWER_R3__________________

#define _________________LOWER_R2__________________       _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
#define _________________LOWER_R3__________________       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______ 
#undef  _________________ADJUST_L2_________________
#define _________________ADJUST_L2_________________       MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  AG_NORM

#undef  _________________ADJUST_L3_________________
#define _________________ADJUST_L3_________________       RGB_M_P, RGB_SPI, RGB_SAD, RGB_VAD, KC_RGB_T

#undef  _________________ADJUST_R2_________________
#define _________________ADJUST_R2_________________       AG_SWAP, DEFLYR1, DEFLYR2, DEFLYR3, DEFLYR4

#if defined(AUTO_SHIFT_ENABLE) && !defined(AUTO_SHIFT_NO_SETUP)
#define _________________ADJUST_L0_________________       KC_ASDN, KC_ASUP, KC_ASTG, _______, _______
#else
#define _________________ADJUST_L0_________________       _______, _______, _______, _______, _______
#endif // AUTO_SHIFT_ENABLED
