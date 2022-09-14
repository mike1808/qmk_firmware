USER_NAME = drashna

# drashan configs
CUSTOM_TAP_DANCE       = no 
CUSTOM_OLED_DRIVER     = no
CUSTOM_POINTING_DEVICE = yes
PER_KEY_TAPPINP        = yes
AUTOCORRECTION_ENABLE  = no
KEYLOGGER_ENABLE       = no

# generic
TAP_DANCE_ENABLE      = no
SWAP_HANDS_ENABLE     = yes
CAPS_WORD_ENABLE      = yes
WPM_ENABLE            = yes

OLED_ENABLE           = yes
AUTO_SHIFT_ENABLE     = yes
ifeq ($(strip $(OLED_ENABLE)), yes)
SRC += oled/oled_stuff.c
SRC += oled/rgb_effects_names.c
endif

# debug
CONSOLE_ENABLE                = yes
DEBUG_MATRIX_SCAN_RATE_ENABLE = no


