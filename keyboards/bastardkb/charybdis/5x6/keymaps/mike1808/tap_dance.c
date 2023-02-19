#include "tap_dance.h"

bool process_record_tapdance(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_HT_START) ... TD(TD_HT_END) :  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_HT_Q_1] = ACTION_TAP_DANCE_TAP_HOLD(KC_Q, KC_1),
    [TD_HT_W_2] = ACTION_TAP_DANCE_TAP_HOLD(KC_W, KC_2),
    [TD_HT_E_3] = ACTION_TAP_DANCE_TAP_HOLD(KC_E, KC_3),
    [TD_HT_R_4] = ACTION_TAP_DANCE_TAP_HOLD(KC_R, KC_4),
    [TD_HT_T_5] = ACTION_TAP_DANCE_TAP_HOLD(KC_T, KC_5),
    [TD_HT_Y_6] = ACTION_TAP_DANCE_TAP_HOLD(KC_Y, KC_6),
    [TD_HT_U_7] = ACTION_TAP_DANCE_TAP_HOLD(KC_U, KC_7),
    [TD_HT_I_8] = ACTION_TAP_DANCE_TAP_HOLD(KC_I, KC_8),
    [TD_HT_O_9] = ACTION_TAP_DANCE_TAP_HOLD(KC_O, KC_9),
    [TD_HT_P_0] = ACTION_TAP_DANCE_TAP_HOLD(KC_P, KC_0),
};
