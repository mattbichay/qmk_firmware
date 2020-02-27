#include "minivan.h"

#define OSX_LOCK LCTL(LGUI(KC_Q))
#define JMP_LEFT LALT(KC_LEFT)
#define JMP_RIGHT LALT(KC_RIGHT)

// TAP STATE Definition
typedef struct
{
    bool is_press_action;
    int state;
} tap;

// TAP DANCE STATES
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};


// TAP DANCE ENUMS
enum
{
    LYR1_KEY_TAP = 0,
    BSPC_KEY_TAP = 1,
    MCRO_KEY_TAP = 2,
    LANG_KEY_TAP = 3
};

enum
{
    LAYER_0 = 0,
    LAYER_1 = 1,
    LAYER_2 = 2,
    LAYER_3 = 3
};


//Helper PROTOTYPES
int cur_dance (qk_tap_dance_state_t *state);

//LYR1 Key Function Prototypes
void lyr1_key_press(qk_tap_dance_state_t *state, void *user_data);
void lyr1_key_finished(qk_tap_dance_state_t *state, void *user_data);
void lyr1_key_reset (qk_tap_dance_state_t *state, void *user_data);


//BSPC_DEL Key Function Prototypes
void bspc_key_press(qk_tap_dance_state_t *state, void *user_data);
void bspc_key_reset(qk_tap_dance_state_t *state, void *user_data);

//MCRO Key Function Prototypes
void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key_reset(qk_tap_dance_state_t *state, void *user_data);

// Key Function Prototypes
void lang_key_toggle(qk_tap_dance_state_t *state, void *user_data);


enum custom_keycodes {
  M_IME = SAFE_RANGE
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
      case M_IME:
        SEND_STRING(SS_DOWN(X_LSHIFT)SS_DOWN(X_LALT));
        return false;
    }
  }
  else {
    switch(keycode) {
      case M_IME:
        SEND_STRING(SS_UP(X_LSHIFT)SS_UP(X_LALT));
        return false;
    }
  }
  return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, TD(BSPC_KEY_TAP),
               TD(LYR1_KEY_TAP), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
               KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
               KC_LCTL, KC_LALT, KC_LGUI, KC_NO, LT(LAYER_3, KC_SPC), KC_SPC, LT(LAYER_2, KC_PGDN), KC_PGUP, JMP_LEFT, JMP_RIGHT),
 
  [1] = LAYOUT(KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_EQL, KC_BSLS, KC_TRNS, KC_TRNS),

  [2] = LAYOUT(KC_ESC, KC_LPRN, KC_RPRN, KC_PLUS, KC_MINS, KC_NO, KC_NO, KC_NO, KC_7, KC_8, KC_9, KC_TRNS,
               KC_TRNS, KC_LBRC, KC_RBRC, KC_ASTR, KC_SLSH, KC_NO, KC_NO, KC_DOT, KC_4, KC_5, KC_6, KC_TRNS,
               KC_TRNS, KC_LT, KC_GT, KC_CIRC, KC_EQL, KC_NO, KC_NO, KC_0, KC_1, KC_2, KC_3, KC_TRNS,
               KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_TRNS, KC_TRNS),

  [3] = LAYOUT(KC_NO, KC_F16, KC_F17, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F18, OSX_LOCK,
               KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MNXT, KC_MPLY, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TD(MCRO_KEY_TAP),
               KC_NO, KC_SLCK, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_HOME, KC_UP, KC_END,
               RESET, KC_NO, KC_NO, KC_NO, KC_NO, TD(LANG_KEY_TAP), KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT) 

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


/* BEGIN LYR1_KEY_TAP */
static tap lyr1_tap_state =
{
    .is_press_action = true,
    .state = 0
};


void lyr1_key_press(qk_tap_dance_state_t *state, void *user_data)
{
    layer_on(LAYER_1);
}

void lyr1_key_finished(qk_tap_dance_state_t *state, void *user_data)
{
    lyr1_tap_state.state = cur_dance(state);
    switch (lyr1_tap_state.state)
    {
		case DOUBLE_TAP:
			tap_code(KC_ESC);
			break;
        case TRIPLE_TAP:
            tap_code(KC_CAPS);
            break;
    }
}

void lyr1_key_reset(qk_tap_dance_state_t *state, void *user_data)
{
    layer_off(LAYER_1);
    lyr1_tap_state.state = 0;
}
/* END LYR1_KEY_TAP */



/* BEGIN BPSC_KEY_TAP */

static uint8_t del_bspc_lastcode = KC_NO;

void bspc_key_reset(qk_tap_dance_state_t *state, void *user_data)
{
    unregister_code(del_bspc_lastcode);
}

void bspc_key_press(qk_tap_dance_state_t *state, void *user_data)
{
    if (keyboard_report->mods & MOD_BIT (KC_RSFT) || keyboard_report->mods & MOD_BIT(KC_LSFT))
        del_bspc_lastcode = KC_DEL;
    else
        del_bspc_lastcode = KC_BSPC;

    register_code(del_bspc_lastcode);
}

/* END BSPC_KEY_TAP */

/* BEGIN MCRO KEY TAP */


static tap mcro_tap_state =
{
    .is_press_action = true,
    .state = 0
};

static bool recording = false;
void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data)
{
    mcro_tap_state.state = cur_dance(state);
    keyrecord_t kr;
    kr.event.pressed = false;

    if (recording)
    {
        kr.event.pressed = true;
        process_dynamic_macro(DYN_REC_STOP, &kr);
        recording = false;
    }
    else if (mcro_tap_state.state == SINGLE_TAP)
    {
        kr.event.pressed = false;
        process_dynamic_macro(DYN_MACRO_PLAY1, &kr);
    }
    else if (mcro_tap_state.state == DOUBLE_TAP)
    {
        kr.event.pressed = false;
        recording = true;
        process_dynamic_macro(DYN_REC_START1, &kr);
    }
}

void mcro_key_reset (qk_tap_dance_state_t *state, void *user_data)
{
    mcro_tap_state.state = 0;
}
/* END MCRO KEY TAP */

/* BEGIN LANG KEY TAP */

static bool japanese_on = false; 

void lang_key_toggle(qk_tap_dance_state_t *state, void *user_data)
{
    if (japanese_on)
    {
        tap_code(KC_LANG2);
        japanese_on = false;
    }
    else
    {
        tap_code(KC_LANG1);
        japanese_on = true;
    }
}
/* END LANG KEY TAP */


void process_indicator_update(uint32_t state, uint8_t usb_led) {
  for (int i = 0; i < 3; i++) {
    setrgb(0, 0, 0, (LED_TYPE *)&led[i]);
  }
  if (state & (1<<1)) {
  setrgb(0, 0, 255, (LED_TYPE *)&led[0]);
}

    if (state & (1<<2)) {
  setrgb(255, 182, 193, (LED_TYPE *)&led[0]);
}

  if (state & (1<<3)) {
  setrgb(0, 255, 255, (LED_TYPE *)&led[1]);
}

    if (state & (1<<2)) {
  setrgb(255, 182, 193, (LED_TYPE *)&led[1]);
}

  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
  setrgb(255, 0, 0, (LED_TYPE *)&led[2]);
}


  rgblight_set();
};

void keyboard_post_init_user(void) {
  process_indicator_update(layer_state, host_keyboard_leds());
};

void led_set_user(uint8_t usb_led) {
  process_indicator_update(layer_state, host_keyboard_leds());
};

uint32_t layer_state_set_user(uint32_t state) {
  process_indicator_update(state, host_keyboard_leds());
  return state;
};


//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = 
{
    [LYR1_KEY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(lyr1_key_press, lyr1_key_finished, lyr1_key_reset),
    [BSPC_KEY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(bspc_key_press, NULL, bspc_key_reset, 50),
    [MCRO_KEY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mcro_key_finished, mcro_key_reset),
    [LANG_KEY_TAP] = ACTION_TAP_DANCE_FN(lang_key_toggle)
};
