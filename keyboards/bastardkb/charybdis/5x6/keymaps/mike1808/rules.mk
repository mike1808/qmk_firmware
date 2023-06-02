USER_NAME = drashna

# drashan configs
CUSTOM_TAP_DANCE       = no
CUSTOM_OLED_DRIVER     = no
CUSTOM_POINTING_DEVICE = yes
PER_KEY_TAPPINP        = no
AUTOCORRECTION_ENABLE  = no
KEYLOGGER_ENABLE       = no

# generic
TAP_DANCE_ENABLE      = yes
SWAP_HANDS_ENABLE     = yes
CAPS_WORD_ENABLE      = yes
WPM_ENABLE            = yes
MOUSEKEY_ENABLE       = yes

OLED_ENABLE           = yes
OLED_TIMEOUT          = 10000
OLED_SCROLL_TIMEOUT   = 5000
AUTO_SHIFT_ENABLE     = no
ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled/oled_stuff.c
	SRC += oled/rgb_effects_names.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	SRC += tap_dance.c
endif

# debug
CONSOLE_ENABLE                = yes
DEBUG_MATRIX_SCAN_RATE_ENABLE = no


POINTING_DEVICE_DRIVER = pmw3360
