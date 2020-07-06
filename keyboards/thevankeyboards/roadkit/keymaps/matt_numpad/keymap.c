#include "roadkit.h"
enum custom_keycodes {
  M_IME = SAFE_RANGE
};

enum {
    DY_MCRO1_TAP = 0,
    DY_MCRO2_TAP = 1,
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


void mcro_key1_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key2_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key_finished(qk_tap_dance_state_t *state, void *user_data);
void mcro_key_reset(qk_tap_dance_state_t *state, void *user_data);

int cur_dance(qk_tap_dance_state_t *state);

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
  [0] = LAYOUT(KC_P7, KC_P8, KC_P9, KC_PPLS, KC_P4, KC_P5, KC_P6, KC_PMNS, KC_P1, KC_P2, KC_P3, LT(2, KC_PENT), LT(1, KC_P0), KC_NO, KC_PDOT, KC_NO),
  [1] = LAYOUT(KC_TRNS, KC_LPRN, KC_RPRN, KC_PAST, KC_TRNS, KC_DLR, KC_CIRC, KC_PSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PEQL, KC_TRNS, KC_NO, KC_TRNS, KC_NO),
  [2] = LAYOUT(TD(DY_MCRO1_TAP), TD(DY_MCRO2_TAP), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, RESET, KC_NO, KC_NO, KC_NO)
};



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

qk_tap_dance_action_t tap_dance_actions[] = {
    [DY_MCRO1_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mcro_key1_finished, mcro_key_reset),
    [DY_MCRO2_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mcro_key2_finished, mcro_key_reset),
};

