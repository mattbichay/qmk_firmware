
#ifndef CONFIG_H
#define CONFIG_H
#include "config_common.h"

#define VENDOR_ID     0xFEAE
#define PRODUCT_ID    0x8858
#define DEVICE_VER    0x0001
#define MANUFACTURER  PrimeKB
#define PRODUCT       Prime_E
#define DESCRIPTION   Ergo_45

#define MATRIX_ROWS 4
#define MATRIX_COLS 13
#define MATRIX_ROW_PINS { E6, C7, B5, B4 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4, D5, D3, D2, D1, D0 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_PIN B7

#define DEBOUNCE 5
#define TAPPING_TERM 175

#define USB_MAX_POWER_CONSUMPTION 100
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PERMISSIVE_HOLD
#define IS_COMMAND() ( keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) )

#define TAPPING_TERM 175
#define ONESHOT_TIMEOUT 5000

#define COMBO_COUNT 3
#endif
