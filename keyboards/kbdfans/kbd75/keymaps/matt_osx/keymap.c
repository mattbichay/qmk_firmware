#include QMK_KEYBOARD_H

// TAP STATE Definition
typedef struct
{
    bool is_press_action;
    int state;
} tap;

// TAP DANCE STATES
enum
{
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3
};

// TAP DANCE ENUMS
enum
{
    FN_KEY_TAP = 0,
    RCTL_KEY_TAP = 1
};

//LAYER ENUMS
enum
{
    DEFAULT_LAYER = 0,
    FUNCTION_LAYER = 1,
    KEYBOARD_SETTINGS_LAYER = 2
};

enum
{
    ENGLISH = 0,
    JAPANESE = 1
};

//Helper PROTOTYPES
int cur_dance (qk_tap_dance_state_t *state);

//FN Key Function Prototypes
void fn_key_finished (qk_tap_dance_state_t *state, void *user_data);
void fn_key_reset (qk_tap_dance_state_t *state, void *user_data);

//RCTL Key Function Prototypes
void rctl_key_finished (qk_tap_dance_state_t *state, void *user_data);
void rctl_key_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
    [0] = LAYOUT_75_ansi(KC_ESC, KC_F14, KC_F15, KC_F16, KC_F17, BL_DEC, BL_INC, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, KC_F18, KC_DEL, KC_EJCT, KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_PGUP, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGDN, KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_HOME, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_END, KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, TD(FN_KEY_TAP), TD(RCTL_KEY_TAP), KC_LEFT, KC_DOWN, KC_RGHT),
	[1] = LAYOUT_75_ansi(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT_75_ansi(RESET, DEBUG, KC_NO, KC_NO, KC_NO, BL_OFF, BL_ON, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, KC_NO, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_RMOD, KC_NO, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MAGIC_TOGGLE_NKRO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO)
};

//Determine the current tap dance state
int cur_dance (qk_tap_dance_state_t *state)
{
    if (state->count == 1)
    {
        if (!state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    }
    else if (state->count == 2)
        return DOUBLE_TAP;
    else
        return 8;
}

/* BEGIN FN_KEY_TAP */
static tap fn_tap_state =
{
    .is_press_action = true,
    .state = 0
};


void fn_key_finished (qk_tap_dance_state_t *state, void *user_data)
{
    fn_tap_state.state = cur_dance(state);
    switch (fn_tap_state.state)
    {
        case SINGLE_TAP:
            if (layer_state_is(KEYBOARD_SETTINGS_LAYER))
                layer_off(KEYBOARD_SETTINGS_LAYER);
            else if (layer_state_is(FUNCTION_LAYER))
                layer_off(FUNCTION_LAYER);
            else
                layer_on(FUNCTION_LAYER);
            break;
    
        case SINGLE_HOLD: 
            if (layer_state_is(DEFAULT_LAYER))
                layer_on(FUNCTION_LAYER);
            else if (layer_state_is(FUNCTION_LAYER))
                layer_off(FUNCTION_LAYER);
            break;
    
        case DOUBLE_TAP: 
        if (layer_state_is(KEYBOARD_SETTINGS_LAYER))
            layer_off(KEYBOARD_SETTINGS_LAYER);
        else
            layer_on(KEYBOARD_SETTINGS_LAYER);
        break;
    }
}

void fn_key_reset (qk_tap_dance_state_t *state, void *user_data)
{
    if (fn_tap_state.state==SINGLE_HOLD)
    {
        if (layer_state_is(FUNCTION_LAYER))
            layer_off(FUNCTION_LAYER);
        else if (layer_state_is(DEFAULT_LAYER))
            layer_on(FUNCTION_LAYER);
    }
    fn_tap_state.state = 0;
}
/* END FN_KEY_TAP */



/* BEGIN RCTL_KEY_TAP */

static tap rctl_tap_state =
{
    .is_press_action = true,
    .state = 0
};

static int current_language = 0;

void rctl_key_finished (qk_tap_dance_state_t *state, void *user_data)
{
    rctl_tap_state.state = cur_dance(state);
    switch (rctl_tap_state.state)
    {
        case SINGLE_TAP:
            tap_code(KC_RCTL);
            break;
        
        case SINGLE_HOLD: 
            register_code(KC_RCTL);
            break;
        
        case DOUBLE_TAP: 
            if (current_language==ENGLISH)
            {
                tap_code(KC_LANG1);
                current_language = JAPANESE;
            }
            else
            { 
                tap_code(KC_LANG2);
                current_language = ENGLISH;
            }
            break;
    }
}

void rctl_key_reset (qk_tap_dance_state_t *state, void *user_data)
{
    if (rctl_tap_state.state==SINGLE_HOLD)
        unregister_code(KC_RCTL);

    rctl_tap_state.state = 0;
}
/* END RCTL_KEY_TAP */


//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = 
{
    [FN_KEY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_key_finished, fn_key_reset),
    [RCTL_KEY_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rctl_key_finished, rctl_key_reset)
};
