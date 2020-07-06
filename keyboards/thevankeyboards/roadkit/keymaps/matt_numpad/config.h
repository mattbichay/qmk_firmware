#ifndef CONFIG_H
#define CONFIG_H
#include "config_common.h"

#define VENDOR_ID     0xFEAE
#define PRODUCT_ID    0x8846
#define DEVICE_VER    0x0003
#define MANUFACTURER  TheVan Keyboards
#define PRODUCT       Roadkit Micro
#define DESCRIPTION   USB C Roadkit

#define MATRIX_ROWS 4
#define MATRIX_COLS 4
#define MATRIX_ROW_PINS { F0, F5, D7, B4 }
#define MATRIX_COL_PINS { F1, F4, D6, D4 }
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_LEVELS 1
#define BACKLIGHT_PIN B5

#define DEBOUNCE 5
#define TAPPING_TERM 175

#define USB_MAX_POWER_CONSUMPTION 100
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PERMISSIVE_HOLD
#define IS_COMMAND() ( keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) )
#endif
