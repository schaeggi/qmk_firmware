# Bootloader for ProMicro Controller
# BOOTLOADER = caterina
# Bootloader for Elite-C Controller
BOOTLOADER = atmel-dfu

VIA_ENABLE = yes
NKRO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
KEY_LOCK_ENABLE = yes
SPACE_CADET_ENABLE = yes
EXTRAKEY_ENABLE = yes        # Audio control and System control
MOUSEKEY_ENABLE = yes        # Mouse keys
TAP_DANCE_ENABLE = yes

# LTO_ENABLE = yes  # link time optimization; compilation takes longer, but makes hex file smaller

OLED_ENABLE = no            # OLED display
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
