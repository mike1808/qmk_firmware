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
#define _________________RAISE_R3__________________       _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC

