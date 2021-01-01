#include "V4N4G0N.h"

// Custom Keys
#define OSX_LOCK LCTL(LGUI(KC_Q))
#define OSX_PSCR LGUI(LSFT(KC_5))
#define JMP_LEFT LALT(KC_LEFT)
#define JMP_RIGHT LALT(KC_RIGHT)

#define NORMAL_TAP_TIME 180

// Layer Names
enum {
    BASE_LAYER = 0,
    BASE_AUX_LAYER = 1,
    GAME_LAYER = 2,
    GAME_AUX_LAYER = 3,
    NUMROW_SYMBOL_LAYER = 4,
    FN_NAV_LAYER = 5,
};
static uint8_t CURRENT_AUX_LAYER = BASE_AUX_LAYER;

// Macro Names
enum {
    BSPC_SHFT_DEL = SAFE_RANGE,
};

// Tapdance Names
enum {
    UPPER_FN_TAP = 0,
    LOWER_FN_TAP = 1,
    DY_MCRO1_TAP = 2,
    DY_MCRO2_TAP = 3,
};

// Macro NAmes
enum {
	TAB_Q_ESC
};

// Tap Dance Function Prototypes
void upper_fn_key_press(qk_tap_dance_state_t *state, void *user_data);
void upper_fn_key_finished(qk_tap_dance_state_t *state, void *user_data);
void upper_fn_key_reset (qk_tap_dance_state_t *state, void *user_data);

void lower_fn_key_press(qk_tap_dance_state_t *state, void *user_data);
void lower_fn_key_finished(qk_tap_dance_state_t *state, void *user_data);
void lower_fn_key_reset (qk_tap_dance_state_t *state, void *user_data);

void mcro_key1_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key2_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key_reset(qk_tap_dance_state_t *state, void *user_data);

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

// Helper Function Prototypes
int cur_dance(qk_tap_dance_state_t *state);
void set_v4n_led_state(uint8_t led, bool led_state);

// Combos
const uint16_t PROGMEM tabq_esc_combo[] = {KC_TAB, KC_Q, COMBO_END};

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT(KC_F17, KC_F16, KC_VOLD, KC_VOLU, KC_SLCK, KC_PAUS, // 6
          KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, BSPC_SHFT_DEL, // 12
          TD(UPPER_FN_TAP), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, // 12
          KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, //12
          KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_SPC, KC_NO, TD(LOWER_FN_TAP), KC_LEFT, KC_RIGHT), //10

  [BASE_AUX_LAYER] = LAYOUT(KC_MPRV, KC_MNXT, KC_MPLY, KC_MUTE, OSX_PSCR, OSX_LOCK, 
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [GAME_LAYER] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [GAME_AUX_LAYER] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS),

  [NUMROW_SYMBOL_LAYER] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSLS, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_DOWN, KC_UP),

  [FN_NAV_LAYER] = LAYOUT(TD(DY_MCRO1_TAP), TD(DY_MCRO2_TAP), KC_TRNS, KC_TRNS, KC_TRNS, RESET,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
          KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_TRNS, KC_HOME, KC_END),
};


// Custom Combo Processing
void process_combo_event(uint8_t combo_index, bool pressed) {
	switch(combo_index) {
		case TAB_Q_ESC:
			if (pressed) {
				SEND_STRING(SS_TAP(X_ESC));
			}
			break;
	}
}



// Macro State
static uint8_t BSPC_SHFT_DEL_KEYCODE = KC_BSPC;
static bool SHIFTED = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BSPC_SHFT_DEL:
            if (record->event.pressed) {
                if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
                    BSPC_SHFT_DEL_KEYCODE = KC_DEL;
                    SHIFTED = true;
                } else {
                    BSPC_SHFT_DEL_KEYCODE = KC_BSPC;
                    SHIFTED = false;
                }
                if (SHIFTED) unregister_code(KC_LSFT);
                register_code(BSPC_SHFT_DEL_KEYCODE);
            } else {
                unregister_code(BSPC_SHFT_DEL_KEYCODE);
                if (SHIFTED) register_code(KC_LSFT);
            }
            break;
     }
    return true;
};

static tap upper_fn_tap_state = {
    .is_press_action = true,
    .state = 0
};

void upper_fn_key_press(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(CURRENT_AUX_LAYER);
    layer_on(NUMROW_SYMBOL_LAYER);
}

void upper_fn_key_finished(qk_tap_dance_state_t *state, void *user_data) {
    upper_fn_tap_state.state = cur_dance(state);
    switch (upper_fn_tap_state.state) {
		case SINGLE_TAP:
			set_oneshot_layer(NUMROW_SYMBOL_LAYER, ONESHOT_START);
			break;
        case TRIPLE_HOLD:
            tap_code(KC_CAPS);
            break;
    }
}

void upper_fn_key_reset (qk_tap_dance_state_t *state, void *user_data) {
	switch (upper_fn_tap_state.state) {
		case SINGLE_TAP:
			clear_oneshot_layer_state(ONESHOT_PRESSED);
			break;
		default:
    		layer_off(NUMROW_SYMBOL_LAYER);
    		layer_off(CURRENT_AUX_LAYER);
	}
    upper_fn_tap_state.state = 0;
}

void oneshot_layer_changed_user(uint8_t layer) {
	if (!layer)
		layer_off(CURRENT_AUX_LAYER);
}

static tap lower_fn_tap_state = {
    .is_press_action = true,
    .state = 0
};

void lower_fn_key_press(qk_tap_dance_state_t *state, void *user_data) {
}

void lower_fn_key_finished(qk_tap_dance_state_t *state, void *user_data) {
    lower_fn_tap_state.state = cur_dance(state);
    switch (lower_fn_tap_state.state) {
        case SINGLE_TAP:
            if (layer_state_is(NUMROW_SYMBOL_LAYER)) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_PGDN);
            }
            break;

        case SINGLE_HOLD:
            layer_on(FN_NAV_LAYER);
            break;

		case TRIPLE_HOLD:
            if (layer_state_is(GAME_LAYER)) {
                layer_off(GAME_LAYER);
                CURRENT_AUX_LAYER = BASE_AUX_LAYER;
            } else {
                layer_on(GAME_LAYER);
                CURRENT_AUX_LAYER = GAME_AUX_LAYER;
            }
            break;
    }
}

void lower_fn_key_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (lower_fn_tap_state.state == SINGLE_HOLD)
        layer_off(FN_NAV_LAYER);

    lower_fn_tap_state.state = 0;
}

static tap mcro_tap_state =
{
    .is_press_action = true,
    .state = 0
};

static bool RECORDING = false;
static uint16_t DYN_MACRO_PLAY = DYN_MACRO_PLAY1;
static uint16_t DYN_REC_START = DYN_REC_START1;

void mcro_key1_finished(qk_tap_dance_state_t *state, void *user_data) {
    DYN_MACRO_PLAY = DYN_MACRO_PLAY1;
    DYN_REC_START = DYN_REC_START1;
    mcro_key_finished(state, user_data);
}

void mcro_key2_finished(qk_tap_dance_state_t *state, void *user_data) {
    DYN_MACRO_PLAY = DYN_MACRO_PLAY2;
    DYN_REC_START = DYN_REC_START2;
    mcro_key_finished(state, user_data);
}

void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data) {
    mcro_tap_state.state = cur_dance(state);
    keyrecord_t kr;
    kr.event.pressed = false;

    if (RECORDING) {
        kr.event.pressed = true;
        process_dynamic_macro(DYN_REC_STOP, &kr);
        RECORDING = false;
    }

    else if (mcro_tap_state.state == SINGLE_TAP) {
        process_dynamic_macro(DYN_MACRO_PLAY, &kr);
    }

    else if (mcro_tap_state.state == DOUBLE_TAP) {
        RECORDING = true;
        process_dynamic_macro(DYN_REC_START, &kr);
    }
}

void mcro_key_reset(qk_tap_dance_state_t *state, void *user_data) {
    mcro_tap_state.state = 0;
}

//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [UPPER_FN_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(upper_fn_key_press, upper_fn_key_finished, upper_fn_key_reset, NORMAL_TAP_TIME),
    [LOWER_FN_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(lower_fn_key_press, lower_fn_key_finished, lower_fn_key_reset, NORMAL_TAP_TIME),
    [DY_MCRO1_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mcro_key1_finished, mcro_key_reset, NORMAL_TAP_TIME),
    [DY_MCRO2_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, mcro_key2_finished, mcro_key_reset, NORMAL_TAP_TIME),
};

//Associate Combos with Functionality
combo_t key_combos[COMBO_COUNT] = {
	[TAB_Q_ESC]      = COMBO_ACTION(tabq_esc_combo)
};


void process_indicator_update(uint32_t state, uint8_t usb_led) {
	
	bool led_1_state = false;
	bool led_2_state = false;
	bool led_3_state = false;

    if (state & (1<<NUMROW_SYMBOL_LAYER)) {
		led_1_state = true;
    } else {
		led_1_state = led_1_state ? true : false;
    }

	if (state & (1<<FN_NAV_LAYER)) {
		led_1_state = true;
		led_2_state = true;
	} else {
		led_1_state = led_1_state ? true : false;
		led_2_state = led_2_state ? true : false;
	}

    if (state & (1<<GAME_LAYER)) {
		led_3_state = true;
    } else {
		led_3_state = led_3_state ? true : false;
    }
    
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
		led_2_state = true;
    } else {
		led_3_state = led_3_state ? true : false;
    }

	set_v4n_led_state(V4N_LED_1, led_1_state);
	set_v4n_led_state(V4N_LED_2, led_2_state);
	set_v4n_led_state(V4N_LED_3, led_3_state);
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


//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8; //magic number. At some point this method will expand to work for more presses
}

// Toggle Input LED on or Off
void set_v4n_led_state(uint8_t led, bool led_state)
{
    switch (led) {
        case V4N_LED_1:
            led_state ? writePinHigh(B6) : writePinLow(B6);
            break;
        case V4N_LED_2:
            led_state ? writePinHigh(B5) : writePinLow(B5);
            break;
        case V4N_LED_3:
            led_state ? writePinHigh(B4) : writePinLow(B4);
            break;
    }
}
