// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// Copyright 2020 @jola5
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "drashna.h"

#undef _________________QWERTY_L1_________________
#undef _________________QWERTY_L2_________________
#undef _________________QWERTY_L3_________________

#undef _________________QWERTY_R1_________________
#undef _________________QWERTY_R2_________________
#undef _________________QWERTY_R3_________________

#undef ___________________BLANK___________________

#undef _________________LOWER_L1__________________
#undef _________________LOWER_L2__________________
#undef _________________LOWER_L3__________________

#undef _________________LOWER_R1__________________
#undef _________________LOWER_R2__________________
#undef _________________LOWER_R3__________________

#undef _________________RAISE_L1__________________
#undef _________________RAISE_L2__________________
#undef _________________RAISE_L3__________________

#undef _________________RAISE_R1__________________
#undef _________________RAISE_R2__________________
#undef _________________RAISE_R3__________________

#undef _________________ADJUST_L1_________________
#undef _________________ADJUST_L2_________________
#undef _________________ADJUST_L3_________________

#undef _________________ADJUST_R1_________________
#undef _________________ADJUST_R2_________________
#undef _________________ADJUST_R3_________________

// clang-format off

#define _________________QWERTY_L1_________________       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________       KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS
#define _________________QWERTY_R2_________________       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT
#define _________________QWERTY_R3_________________       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define ___________________BLANK___________________       _______, _______, _______, _______, _______


#define _________________LOWER_L1__________________       KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC
#define _________________LOWER_L2__________________       _______, _______, _______, _______, _______
#define _________________LOWER_L3__________________       _______, _______, _______, _______, _______

#define _________________LOWER_R1__________________       KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
#define _________________LOWER_R2__________________       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS
#define _________________LOWER_R3__________________       KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE 



#define _________________RAISE_L1__________________       ________________NUMBER_LEFT________________
#define _________________RAISE_L2__________________       _________________FUNC_LEFT_________________
#define _________________RAISE_L3__________________       _________________FUNC_RIGHT________________


#define _________________RAISE_R1__________________       ________________NUMBER_RIGHT_______________
#define _________________RAISE_R2__________________       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______
#define _________________RAISE_R3__________________       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, _______ 


#if defined(AUTO_SHIFT_ENABLE) && !defined(AUTO_SHIFT_NO_SETUP)
#define _________________ADJUST_L0_________________       KC_ASDN, KC_ASUP, KC_ASTG, _______, _______
#else
#define _________________ADJUST_L0_________________       _______, _______, _______, _______, _______
#endif // AUTO_SHIFT_ENABLED

#define _________________ADJUST_L1_________________       RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
#define _________________ADJUST_L2_________________       MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  AG_NORM
#define _________________ADJUST_L3_________________       RGB_M_P, RGB_SPI, RGB_SAD, RGB_VAD, KC_RGB_T

#define _________________ADJUST_R1_________________       KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
#define _________________ADJUST_R2_________________       AG_SWAP, _______, _______, _______, _______
#define _________________ADJUST_R3_________________       MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT
