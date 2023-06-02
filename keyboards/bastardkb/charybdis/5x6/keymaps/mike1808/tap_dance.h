#pragma once
#include QMK_KEYBOARD_H

enum {
    TD_HT_START,
    TD_HT_Q_1 = 0,
    TD_HT_W_2,
    TD_HT_E_3,
    TD_HT_R_4,
    TD_HT_T_5,
    TD_HT_Y_6,
    TD_HT_U_7,
    TD_HT_I_8,
    TD_HT_O_9,
    TD_HT_P_0,
    TD_HT_TAB_GRV,
    TD_HT_END,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_tapdance(uint16_t keycode, keyrecord_t *record);
