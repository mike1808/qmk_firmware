USER_NAME = drashna

TAP_DANCE_ENABLE = yes
CUSTOM_TAP_DANCE = no 
CUSTOM_OLED_DRIVER = no
CUSTOM_POINTING_DEVICE = yes
PER_KEY_TAPPINP = yes

SWAP_HANDS_ENABLE     = no
AUTOCORRECTION_ENABLE = no
CAPS_WORD_ENABLE      = yes
CONSOLE_ENABLE        = yes
KEYLOGGER_ENABLE      = no
WPM_ENABLE            = yes
OLED_ENABLE           = yes

AUTO_SHIFT_ENABLE = yes


DEBUG_MATRIX_SCAN_RATE_ENABLE = no

ifeq ($(strip $(OLED_ENABLE)), yes)
SRC += oled/oled_stuff.c
SRC += oled/rgb_effects_names.c
endif
