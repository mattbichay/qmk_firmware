#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(KC_P7, KC_P8, KC_P9, KC_P4, KC_P5, KC_P6, KC_P1, KC_P2, KC_P3, LT(2,KC_PDOT), KC_P0, LT(1,KC_PENT)),
	[1] = LAYOUT(KC_HOME, KC_UP, KC_PGUP, KC_LEFT, KC_NO, KC_RGHT, KC_END, KC_DOWN, KC_PGDN, KC_DEL, KC_INS, KC_TRNS),
	[2] = LAYOUT(KC_PPLS, KC_PMNS, KC_DLR, KC_PAST, KC_PSLS, KC_COMM, KC_LPRN, KC_RPRN, KC_HASH, KC_TRNS, KC_PEQL, KC_BSPC)
};
