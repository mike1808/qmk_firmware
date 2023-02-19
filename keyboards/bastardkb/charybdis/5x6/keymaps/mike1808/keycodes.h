#pragma once
#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE

#    define HT_Q_1 TD(TD_HT_Q_1)
#    define HT_W_2 TD(TD_HT_W_2)
#    define HT_E_3 TD(TD_HT_E_3)
#    define HT_R_4 TD(TD_HT_R_4)
#    define HT_T_5 TD(TD_HT_T_5)
#    define HT_Y_6 TD(TD_HT_Y_6)
#    define HT_U_7 TD(TD_HT_U_7)
#    define HT_I_8 TD(TD_HT_I_8)
#    define HT_O_9 TD(TD_HT_O_9)
#    define HT_P_0 TD(TD_HT_P_0)

#elif

#    define HT_Q_1 KC_Q
#    define HT_W_2 KC_W
#    define HT_E_3 KC_E
#    define HT_R_4 KC_R
#    define HT_T_5 KC_T
#    define HT_Y_6 KC_Y
#    define HT_U_7 KC_U
#    define HT_I_8 KC_I
#    define HT_O_9 KC_O
#    define HT_P_0 KC_P

#endif
