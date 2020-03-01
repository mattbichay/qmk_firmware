#include "V4N4G0N.h"

// Custom Keys
#define OSX_LOCK LCTL(LGUI(KC_Q))
#define JMP_LEFT LALT(KC_LEFT)
#define JMP_RIGHT LALT(KC_RIGHT)

// Layer Names
enum {
    BASE_LAYER = 0,
    BASE_AUX_LAYER = 1,
    GAME_LAYER = 2,
    GAME_AUX_LAYER = 3,
    NUMROW_SYMBOL_LAYER = 4,
    NAV_LAYER = 5,
    NUMPAD_FN_LAYER = 6
};

// Macro Names
enum {
    BSPC_SHFT_DEL = SAFE_RANGE,
    PGDN_SHFT_PGUP,
    MO_NUMROW_AUX
};

// Function Prototypes


// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT(KC_F16, KC_F17, KC_VOLD, KC_VOLU, KC_SLCK, KC_PAUS, // 6
          KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, BSPC_SHFT_DEL, // 12
          MO(6), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, // 12
          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, //12
          KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, LT(4, KC_SPC), KC_NO, TG(2), JMP_LEFT, JMP_RIGHT), //10

  [BASE_AUX_LAYER] = LAYOUT(KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, KC_F18, KC_POWER, 
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [GAME_LAYER] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          MO(6), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [GAME_AUX_LAYER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [NUMROW_SYMBOL_LAYER] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_EQL, KC_BSLS, KC_TRNS),

  [NAV_LAYER] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_UP, KC_END,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RIGHT),

  [NUMPAD_FN_LAYER] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
          KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
          KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
          KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),
};

// Macro State
static uint8_t BSPC_SHFT_DEL_KEYCODE = KC_BSPC;
static uint8_t PGDN_SHFT_PGUP_KEYCODE = KC_PGDN;
static uint8_t AUX_LAYER = BASE_AUX_LAYER;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case BSPC_SHFT_DEL:
            if (record->event.pressed) {
                // If Left-Shift or Right-Shift is held
                if (keyboard_report->mods & MOD_BIT (KC_RSFT) || keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    // Set key to delete
                    BSPC_SHFT_DEL_KEYCODE = KC_DEL;
                } else {
                    // Otherwise set key to backspace
                    BSPC_SHFT_DEL_KEYCODE = KC_BSPC;
                }
                register_code(BSPC_SHFT_DEL_KEYCODE);
            } else {
                unregister_code(BSPC_SHFT_DEL_KEYCODE);
            }
            break;

        case PGDN_SHFT_PGUP:
            if (record->event.pressed) {
                // If Left-Shift or Right-Shift is held
                if (keyboard_report->mods & MOD_BIT (KC_RSFT) || keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    // Set key to page up
                    PGDN_SHFT_PGUP_KEYCODE = KC_PGUP;
                } else {
                    // Otherwise set key to page down
                    PGDN_SHFT_PGUP_KEYCODE = KC_PGDN;
                }
                register_code(PGDN_SHFT_PGUP_KEYCODE);
            } else {
                unregister_code(PGDN_SHFT_PGUP_KEYCODE);
            }
            break;

        case MO_NUMROW_AUX:
            if (record->event.pressed) {
                // If the Game Layer is active
                if (layer_state_is(GAME_LAYER)) {
                    // Set the game auxilary layer
                    AUX_LAYER = GAME_AUX_LAYER;
                } else {
                    // Set the base auxilary layer
                    AUX_LAYER = BASE_AUX_LAYER; 
                }
                // Momentarily turn on both the auxilary layer and numrow layer
                layer_on(AUX_LAYER);
                layer_on(NUMROW_SYMBOL_LAYER);
            } else {
                layer_off(NUMROW_SYMBOL_LAYER);
                layer_off(AUX_LAYER);
            }
            break;
    }
    return true;
};


// Tap Dance States
typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};



void process_indicator_update(uint32_t state, uint8_t usb_led) {
    if (state & (1<<1)) {
        writePinHigh(B6);
    } else {
        writePinLow(B6);
    }
    
    if (state & (1<<3)) {
        writePinHigh(B5);
    } else {
        writePinLow(B5);
    }
    
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        writePinHigh(B4);
    } else {
        writePinLow(B4);
    }
};

void keyboard_post_init_user(void) {
    setPinOutput(B6);
    setPinOutput(B5);
    setPinOutput(B4);
    process_indicator_update(layer_state, host_keyboard_leds());
};

void led_set_user(uint8_t usb_led) {
    process_indicator_update(layer_state, host_keyboard_leds());
};

uint32_t layer_state_set_user(uint32_t state) {
    process_indicator_update(state, host_keyboard_leds());
    return state;
};
