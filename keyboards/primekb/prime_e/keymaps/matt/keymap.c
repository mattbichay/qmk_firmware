#include "prime_e.h"

#define OSX_LOCK LCTL(LGUI(KC_Q))
#define OSX_PSCR LGUI(LSFT(KC_5))

// Layer Names
enum {
    BASE_LAYER = 0,
    NUMROW_SYMBOL_LAYER = 1,
    NAV_LAYER = 2,
    NUMPAD_FN_LAYER = 3
};

// Tapdance Names
enum {
    UPPER_FN_TAP = 0,
    LOWER_FN_TAP = 1,
    DY_MCRO1_TAP = 2,
};

// Combo Names
enum {
	SUPER_BSPC_DEL,
	MEGA_BSPC,
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


// Combos
const uint16_t PROGMEM super_bspc_del_combo[] = {KC_DEL, KC_BSPC, COMBO_END};
const uint16_t PROGMEM mega_bspc_combo[] = {KC_DEL, KC_BSPC, KC_P, COMBO_END};
const uint16_t PROGMEM tabq_esc_combo[] = {KC_TAB, KC_Q, COMBO_END};

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE_LAYER] = LAYOUT(
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                    KC_Y, KC_U, KC_I, KC_O, KC_P, KC_DEL, KC_BSPC,
		TD(UPPER_FN_TAP), KC_A, KC_S, KC_D, KC_F, KC_G,          KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                   TD(LOWER_FN_TAP), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
		KC_LCTL, KC_LALT, KC_LGUI, LT(NAV_LAYER, KC_SPC),	     KC_SPC, KC_PGDN, KC_LEFT, KC_RIGHT
    ),

    [NUMROW_SYMBOL_LAYER] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5,                    KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_BSLS, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_EQL, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,	                     KC_TRNS, KC_PGUP, KC_DOWN, KC_UP
    ),

    [NAV_LAYER] = LAYOUT(
		KC_TRNS, KC_F17, KC_F16, OSX_PSCR, OSX_LOCK, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_SLCK, KC_PAUS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
		KC_MPRV, KC_MNXT, KC_MPLY, KC_TRNS,	                     KC_TRNS, KC_TRNS, KC_HOME, KC_END
    ),

    [NUMPAD_FN_LAYER] = LAYOUT(
		RESET, KC_PPLS, KC_PMNS, KC_LPRN, KC_RPRN, KC_PERC,      KC_NO, KC_NO, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS,
        KC_PEQL, KC_PAST, KC_PSLS, KC_LBRC, KC_RBRC, KC_HASH,    KC_NO, KC_NO, KC_P4, KC_P5, KC_P6, KC_TRNS, 
        KC_CIRC, KC_LT, KC_GT, KC_LCBR, KC_RCBR, KC_DLR,         KC_TRNS, KC_NO, KC_P0, KC_P1, KC_P2, KC_P3, KC_PDOT, 
		KC_EXLM, KC_AMPR, KC_PIPE, TD(DY_MCRO1_TAP),             KC_TRNS, KC_EQL, KC_COMM, KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	return true;
};

static tap upper_fn_tap_state = {
    .is_press_action = true,
    .state = 0
};

void upper_fn_key_press(qk_tap_dance_state_t *state, void *user_data) {
    layer_on(NUMROW_SYMBOL_LAYER);
}

void upper_fn_key_finished(qk_tap_dance_state_t *state, void *user_data) {
    upper_fn_tap_state.state = cur_dance(state);
    switch (upper_fn_tap_state.state) {
		case SINGLE_TAP:
			set_oneshot_layer(NUMROW_SYMBOL_LAYER, ONESHOT_START);
			break;
        case DOUBLE_HOLD:
            register_code(KC_ESC);
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
		case DOUBLE_HOLD:
			unregister_code(KC_ESC);
		default:
			layer_off(NUMROW_SYMBOL_LAYER);
	}
    upper_fn_tap_state.state = 0;
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
			tap_code(KC_B);
			break;
        case SINGLE_HOLD:
            layer_on(NUMPAD_FN_LAYER);
            break;

        case DOUBLE_HOLD:
            if (layer_state_is(NUMPAD_FN_LAYER)) {
                layer_off(NUMPAD_FN_LAYER);
            } else {
                layer_on(NUMPAD_FN_LAYER);
            }
            break;
    }
}

void lower_fn_key_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (lower_fn_tap_state.state == SINGLE_HOLD)
        layer_off(NUMPAD_FN_LAYER);
    lower_fn_tap_state.state = 0;
}


static tap mcro_tap_state = {
    .is_press_action = true,
    .state = 0
};

static bool recording = false;
static int DYN_MACRO_PLAY = DYN_MACRO_PLAY1;
static int DYN_REC_START = DYN_REC_START1;

void mcro_key1_finished(qk_tap_dance_state_t *state, void *user_data) {
    DYN_MACRO_PLAY = DYN_MACRO_PLAY1;
    DYN_REC_START = DYN_REC_START1;
    mcro_key_finished(state, user_data);
}

void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data) {
    mcro_tap_state.state = cur_dance(state);
    keyrecord_t kr;
    kr.event.pressed = false;

    if (recording) {
        kr.event.pressed = true;
        process_dynamic_macro(DYN_REC_STOP, &kr);
        recording = false;
    }

    else if (mcro_tap_state.state == SINGLE_TAP) {
        kr.event.pressed = false;
        process_dynamic_macro(DYN_MACRO_PLAY, &kr);
    }

    else if (mcro_tap_state.state == DOUBLE_TAP) {
        kr.event.pressed = false;
        recording = true;
        process_dynamic_macro(DYN_REC_START, &kr);
    }
}

void mcro_key_reset(qk_tap_dance_state_t *state, void *user_data) {
    mcro_tap_state.state = 0;
}


//Associate Combos with Functionality
combo_t key_combos[COMBO_COUNT] = {
	[SUPER_BSPC_DEL] = COMBO_ACTION(super_bspc_del_combo),
	[MEGA_BSPC]      = COMBO_ACTION(mega_bspc_combo),
	[TAB_Q_ESC]      = COMBO_ACTION(tabq_esc_combo)
};

//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [UPPER_FN_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(upper_fn_key_press, upper_fn_key_finished, upper_fn_key_reset),
    [LOWER_FN_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(lower_fn_key_press, lower_fn_key_finished, lower_fn_key_reset),
    [DY_MCRO1_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mcro_key_finished, mcro_key_reset),
};


// Custom Combo Processing
void process_combo_event(uint8_t combo_index, bool pressed) {
	switch(combo_index) {
		case SUPER_BSPC_DEL:
			if (pressed) {
        		if (layer_state_is(NUMROW_SYMBOL_LAYER)) {
					SEND_STRING(SS_DOWN(X_LALT));
					SEND_STRING(SS_TAP(X_DEL));
					SEND_STRING(SS_UP(X_LALT));
				} else {
					SEND_STRING(SS_DOWN(X_LALT));
					SEND_STRING(SS_TAP(X_BSPC));
					SEND_STRING(SS_UP(X_LALT));
				}
      		}
			break;
		case MEGA_BSPC:
			if (pressed) {
				SEND_STRING(SS_DOWN(X_LGUI));
				SEND_STRING(SS_TAP(X_BSPC));
				SEND_STRING(SS_UP(X_LGUI));
			}
			break;
		case TAB_Q_ESC:
			if (pressed) {
				SEND_STRING(SS_DOWN(X_ESC));
			} else {
				SEND_STRING(SS_UP(X_ESC));
			}
			break;
	}
}

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


void process_indicator_update(uint32_t state, uint8_t usb_led) {
	bool set_red = false;
	bool set_blue = false;
	bool set_green = false;
	if (usb_led & (1<<USB_LED_CAPS_LOCK))
		set_red = true;
	
	if (state & (1<<NUMROW_SYMBOL_LAYER))
		set_blue = true;

	if (state & (1<<NAV_LAYER))
		set_green = true;

	if (state & (1<<NUMPAD_FN_LAYER)) {
		set_blue = true;
		set_green = true;
	}
	if (set_red)
		writePinHigh(B3);
	else
		writePinLow(B3);
	if (set_green)
		writePinHigh(B2);
	else
		writePinLow(B2);
	if (set_blue)
		writePinHigh(B1);
	else
		writePinLow(B1);
};

void keyboard_post_init_user(void) {
	setPinOutput(B1);
	setPinOutput(B2);
	setPinOutput(B3);
	process_indicator_update(layer_state, host_keyboard_leds());
};

void led_set_user(uint8_t usb_led) {
	process_indicator_update(layer_state, host_keyboard_leds());
};

uint32_t layer_state_set_user(uint32_t state) {
	process_indicator_update(state, host_keyboard_leds());
	return state;
};
