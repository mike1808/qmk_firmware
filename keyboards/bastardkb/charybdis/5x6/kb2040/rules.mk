# MCU name
# MCU = RP2040

# Bootloader selection
# BOOTLOADER = rp2040

OPT_DEFS += -DHAL_USE_I2C=TRUE -DHAL_USE_SPI=TRUE

# RP2040-specific options
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no # ATM Unsupported by ChibiOS.

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output

AUDIO_SUPPORTED = no        # Audio is not supported
RGB_MATRIX_SUPPORTED = yes  # RGB matrix is supported and enabled by default
RGBLIGHT_SUPPORTED = yes    # RGB underglow is supported, but not enabled by default
RGB_MATRIX_ENABLE = yes     # Enable keyboard RGB matrix functionality
RGB_MATRIX_DRIVER = WS2812

SPLIT_KEYBOARD = yes

POINTING_DEVICE_ENABLE = yes # Enable trackball

SERIAL_DRIVER = vendor
# WS2812_DRIVER = vendor

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
