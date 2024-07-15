/* Copyright 2019 Leo Batyuk
 * Copyright 2020 Drashna Jaelre <@drashna>
 * Copyright 2020 @ben_roe (keycapsss.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// ------------------------------------------------------------------------
// Combos - multiple keys pressed at the same time
// ------------------------------------------------------------------------
// const uint16_t PROGMEM combo_fp[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_wf[] = {KC_W, KC_F, COMBO_END};

const uint16_t PROGMEM combo_st[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM combo_rt[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_tg[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_rs[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM combo_rst[] = {KC_R, KC_S, KC_T, COMBO_END};

// const uint16_t PROGMEM combo_lu[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_uz[] = {KC_U, KC_Y, COMBO_END};

const uint16_t PROGMEM combo_ne[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM combo_ni[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM combo_mn[] = {KC_M, KC_N, COMBO_END};
const uint16_t PROGMEM combo_ei[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_nei[] = {KC_N, KC_E, KC_I, COMBO_END};


combo_t key_combos[] = {
    // COMBO(combo_fp, LCTL(KC_DEL)),
    COMBO(combo_wf, LCTL(KC_BSPC)),
    
    COMBO(combo_st, KC_LEFT),
    COMBO(combo_rt, LCTL(KC_LEFT)),
    COMBO(combo_rs, KC_BSPC),
    COMBO(combo_tg, RSFT(KC_8)),
    COMBO(combo_rst, LCTL(KC_BSPC)),
    
    // COMBO(combo_lu, LCTL(KC_LEFT)),
    COMBO(combo_uz, LCTL(KC_DEL)),

    COMBO(combo_ne, KC_RIGHT),
    COMBO(combo_ni, LCTL(KC_RIGHT)),
    COMBO(combo_ei, KC_DEL),
    COMBO(combo_mn, RSFT(KC_9)),
    COMBO(combo_nei, LCTL(KC_DEL)),
};


// ---------------------------------------------------------
// Tap Dance - let one key do more with one, two, three taps
// ---------------------------------------------------------

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(tap_dance_state_t *state);

// For the tap dance. Put it here so it can be used in any keymap
void l1_double_shift_register(tap_dance_state_t *state, void *user_data);
void l1_double_shift_reset(tap_dance_state_t *state, void *user_data);
void esc_kill_register(tap_dance_state_t *state, void *user_data);
void esc_kill_reset(tap_dance_state_t *state, void *user_data);
void square_bracket_double_register(tap_dance_state_t *state, void *user_data);
void square_bracket_double_reset(tap_dance_state_t *state, void *user_data);
void braces_double_register(tap_dance_state_t *state, void *user_data);
void braces_double_reset(tap_dance_state_t *state, void *user_data);
void double_ae_register(tap_dance_state_t *state, void *user_data);
void double_ae_reset(tap_dance_state_t *state, void *user_data);
void double_oe_register(tap_dance_state_t *state, void *user_data);
void double_oe_reset(tap_dance_state_t *state, void *user_data);
void double_ue_register(tap_dance_state_t *state, void *user_data);
void double_ue_reset(tap_dance_state_t *state, void *user_data);
void move_window_desktop1_register(tap_dance_state_t *state, void *user_data);
void move_window_desktop1_reset(tap_dance_state_t *state, void *user_data);
void move_window_desktop2_register(tap_dance_state_t *state, void *user_data);
void move_window_desktop2_reset(tap_dance_state_t *state, void *user_data);
void move_window_desktop3_register(tap_dance_state_t *state, void *user_data);
void move_window_desktop3_reset(tap_dance_state_t *state, void *user_data);

// Tap Dance declarations
enum {
    SHIFT_TO_CAPS, // = SAFE_RANGE,
    DOUBLE_RESET,
    L1_DOUBLE_SHIFT,
    ESC_KILL,
    SQUARE_BRACKET_DOUBLE,
    BRACES_DOUBLE,
    AE_DOUBLE,
    OE_DOUBLE,
    UE_DOUBLE,
    MOVE_TO_1,
    MOVE_TO_2,
    MOVE_TO_3,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_TO_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [DOUBLE_RESET] = ACTION_TAP_DANCE_DOUBLE(QK_REBOOT, QK_BOOTLOADER),  // Bootloader for flashing new firmware
    [L1_DOUBLE_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l1_double_shift_register, l1_double_shift_reset),
    [ESC_KILL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, esc_kill_register, esc_kill_reset),
    [SQUARE_BRACKET_DOUBLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, square_bracket_double_register, square_bracket_double_reset),
    [BRACES_DOUBLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, braces_double_register, braces_double_reset),
    [AE_DOUBLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_ae_register, double_ae_reset),    
    [OE_DOUBLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_oe_register, double_oe_reset),
    [UE_DOUBLE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, double_ue_register, double_ue_reset),
    [MOVE_TO_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, move_window_desktop1_register, move_window_desktop1_reset),
    [MOVE_TO_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, move_window_desktop2_register, move_window_desktop2_reset),
    [MOVE_TO_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, move_window_desktop3_register, move_window_desktop3_reset),   
};







// custom keycode definitions
enum custom_keycodes {
    DRAG_SCROLL = SAFE_RANGE,
    CC_LITM,
    CC_WPDT,
    CC_WNDT,
    CC_NDSH,
    CC_STC = TD(SHIFT_TO_CAPS),
    CC_DRST = TD(DOUBLE_RESET),
    CC_L1DS = TD(L1_DOUBLE_SHIFT),
    CC_ESK = TD(ESC_KILL),
    CC_BRAK = TD(SQUARE_BRACKET_DOUBLE),
    CC_BRAC = TD(BRACES_DOUBLE),
    CC_AE = TD(AE_DOUBLE),
    CC_OE = TD(OE_DOUBLE),
    CC_UE = TD(UE_DOUBLE),
    CC_MOV1 = TD(MOVE_TO_1),
    CC_MOV2 = TD(MOVE_TO_2),
    CC_MOV3 = TD(MOVE_TO_3),
};



// https://docs.qmk.fm/#/feature_macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case CC_LITM:
            if (record->event.pressed) {
                SEND_STRING( SS_TAP(X_SLASH) SS_TAP(X_SPC) SS_RALT(SS_TAP(X_8)) SS_TAP(X_SPC) SS_RALT(SS_TAP(X_9)) SS_TAP(X_SPC) );
            } else {
            }
            break;

        case CC_NDSH:  // FIXME: ndash from alt code (add linux way [ralt] + [-] )
            if (record->event.pressed) {
                SEND_STRING(SS_LALT(SS_TAP(X_KP_0) SS_TAP(X_KP_1) SS_TAP(X_KP_5) SS_TAP(X_KP_0)));
            } else {
            }
            break;

        case CC_WPDT:  // previous virtual desktop on win10
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_LEFT))));
            } else {
            }
            break;
      
        case CC_WNDT:  // next virtual desktop on win10
            if (record->event.pressed) {
                SEND_STRING(SS_LCTL(SS_LGUI(SS_TAP(X_RIGHT))));
            } else {
            }
            break;
    }
    return true;
};


// --------------------------
// Keyboard Layer Definitions
// --------------------------

enum layers {
    _ALPHAS,    // Alpha Layer (0)
    _SPECIAL,   // Special Character Layer (1)
    _CONTROL,   // Control Layer with arrows/numpad (2)
    _ADVANCED,  // Mousekeys and Macros (3)
    _GAMING,    // Gaming layer with modified wasd (4)
    _ADJUST,    // Control Keyboard RGB and more (5)
};

#define L0 MO(_ALPHAS)
#define L1 MO(_SPECIAL)
#define L2 TT(_CONTROL)
#define L3 MO(_ADVANCED)
#define L4 MO(_GAMING)
#define L5 MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* ALPHA CHARACTERS
 * ,--------------------------------------------.                    ,----------------------------------------------.
 * |   ESC   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Escape   |
 * |---------+------+------+------+------+------|                    |------+------+------+------+------+-----------|
 * |   Tab   |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Z  |   #  |  Delete   |
 * |---------+------+------+------+------+------|                    |------+------+------+------+------+-----------|
 * |  LShift |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  |  Enter    |
 * |---------+------+------+------+------+------| Enter |    | Space |------+------+------+------+------+-----------|
 * |  LCTRL  |   Y  |   X  |   D  |   C  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  |  RCTRL    |
 * `-------------------------------------------|       /     \ Shift \-----------------------------------------------'
 *                 | LALT | LGUI | L3   | L2  | Space /       \Enter \  |  L1  | RGUI | RALT |      |
 *                 `----------------------------------'       '------------------------------------'
 */
 [_ALPHAS] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_NUHS, KC_DEL,
    KC_LSFT,  KC_A,   KC_R,    KC_S,    KC_T,    KC_G,                        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LCTL,  KC_Z,   KC_X,    KC_D,    KC_C,    KC_V,    KC_ENT,   KC_SPC,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RCTL,
                      KC_LALT, KC_LGUI, L3,      L2,      KC_SPC,   SC_SENT,  L1,      KC_RGUI, KC_RALT, L4
),

/* Layer 1 - SPECIAL CHARACTERS
 * ,-------------------------------------------.                    ,-----------------------------------------.
 * |  ESC   |      |  ²   |  ³   |      |      |                    |      |  {   |  [   |  ]   |  }   |  Bspc |
 * |--------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB   |  @   |  %   |  +   |  (   |  {   |                    |  [   |  )   |  ü   |  $   |   ~  |  Del  |
 * |--------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  Lsft  |  ä   |   !  |   ß  |   -  |   –  |-------.    ,-------|   µ  |   =  |   €  |   ?  |   ö  | Enter |
 * |--------+------+------+------+------+------| Enter |    | Space |------+------+------+------+------+------|
 * |  Lctl  |   <  |   >  |   *  |   _  |  ^   |-------|    |-------|   ´  |   "  |   &  |   °  |   |  | Rctl  |
 * `-------------------------------------------|       /     \      \------------------------------------------'
 *                 | LCTRL| LGUI |  L3  |  L2  | Space /      \Enter \   | L1  | RGUI | RALT |  L5 |
 *                 `----------------------------------'       '------------------------------------'
 */
[_SPECIAL] = LAYOUT(
    KC_TRNS, RALT(KC_1), RALT(KC_2),    RALT(KC_3),    RALT(KC_4),    RALT(KC_5),                   RALT(KC_6), RALT(KC_7), RALT(KC_8), RALT(KC_9),     RALT(KC_0),    KC_TRNS,
    KC_TRNS, RALT(KC_Q), LSFT(KC_5),    KC_RBRC,       RSFT(KC_8),    CC_BRAC,                      CC_BRAK,    RSFT(KC_9), CC_UE,      LSFT(KC_4),     RALT(KC_RBRC), KC_TRNS,
    KC_TRNS, CC_AE,      LSFT(KC_1),    KC_MINUS,      KC_SLASH,      CC_NDSH,                      RALT(KC_M), RSFT(KC_0), RALT(KC_E), LSFT(KC_MINUS), CC_OE,         KC_TRNS,
    KC_TRNS, KC_NUBS,    LSFT(KC_NUBS), LSFT(KC_RBRC), LSFT(KC_SLSH), KC_GRAVE, KC_TRNS,   KC_TRNS, KC_EQUAL,   LSFT(KC_2), LSFT(KC_6), LSFT(KC_GRAVE), RALT(KC_NUBS), KC_TRNS,
                         KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
),

/* Layer 2 - CONTROL LAYER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESK  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |      |   7  |   8  |   9  | F11  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|     |   4  |   5  |   6  | F12  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|      |   1  |   2  |   3  |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                 | LCTRL| LGUI | LALT |LOWER| Space /       \Enter \  |   0  |BackSP| RGUI | RALT |
 *                 `----------------------------------'       '------------------------------------'
 */
[_CONTROL] = LAYOUT(
    CC_ESK,      KC_F1,   KC_F2,      KC_F3,      KC_F4,      KC_F5,                        KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_TRNS,
    LCA(KC_DEL), KC_INS,  KC_HOME,    KC_UP,      KC_END,     KC_PGUP,                      KC_KP_PLUS,  KC_KP_7, KC_KP_8, KC_KP_9, KC_F11,   KC_TRNS,
    CC_STC,      KC_DEL,  KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,                      KC_KP_MINUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_F12,   KC_TRNS,
    KC_TRNS,     KC_PSCR, LCTL(KC_X), LCTL(KC_A), LCTL(KC_C), LCTL(KC_V), QK_LOCK, KC_NUM , KC_KP_0,     KC_KP_1, KC_KP_2, KC_KP_3, KC_COMMA, KC_TRNS,
                          KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS,     KC_KP_ASTERISK, KC_KP_SLASH, KC_TRNS
),

/* Layer 3 - ADVANCED LAYER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                 | LCTRL| LGUI | LALT |LOWER| Space /       \Enter \  |RAISE |BackSP| RGUI | RALT |
 *                 `----------------------------------'       '------------------------------------'
 */
[_ADVANCED] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                      _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______
),

/* Layer 4 - GAMING LAYER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|      | Left | Down |  Up  |Right |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                 | LCTRL| LGUI | LALT |LOWER| Space /       \Enter \  |RAISE |BackSP| RGUI | RALT |
 *                 `----------------------------------'       '------------------------------------'
 */
[_GAMING] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                      _______, _______, _______, _______,  _______, _______,  _______, _______, _______, _______
),

/* Layer 5 - ADJUST (Press LOWER and RAISE together)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |QK_BOOT |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RGB ON| HUE+ | SAT+ | VAL+ |      |      |                    | PREV | PLAY | NEXT |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | MODE | HUE- | SAT- | VAL- |      |      |-------.    ,-------| VOL+ | MUTE | VOL- |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                 |LCTRL| LGUI | LALT |LOWER| Space /       \Enter \  |RAISE |BackSP| RGUI | RALT |
 *                 `----------------------------------'       '------------------------------------'
 */
[_ADJUST] = LAYOUT(
    QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                   KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                   KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
  )
};


/* KEY OVERRIDES:
 *  Shift + Slash (KP) ... Backslash  */
const key_override_t slash_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_KP_SLASH, RALT(KC_MINUS));
const key_override_t** key_overrides = (const key_override_t*[]){
    &slash_key_override,
    NULL
};

// Tap dance status check
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void l1_double_shift_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD: layer_on(1); break;
        case TD_DOUBLE_HOLD: layer_on(1); register_code(KC_LEFT_SHIFT); break;
        default: break;
    }
}
void l1_double_shift_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_HOLD: layer_off(1); break;
        case TD_DOUBLE_HOLD: layer_off(1); unregister_code(KC_LEFT_SHIFT); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void esc_kill_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_DOUBLE_TAP: register_code(KC_LALT); register_code(KC_F4); break;
        default: break;
    }
}
void esc_kill_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LALT); unregister_code(KC_F4); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void square_bracket_double_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_RALT); register_code(KC_8); break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_9); break;
        default: break;
    }
}
void square_bracket_double_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_RALT); unregister_code(KC_8); break;
        case TD_DOUBLE_TAP: unregister_code(KC_RALT); unregister_code(KC_9); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void braces_double_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_RALT); register_code(KC_7); break;
        case TD_DOUBLE_TAP: register_code(KC_RALT); register_code(KC_0); break;
        default: break;
    }
}
void braces_double_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_RALT); unregister_code(KC_7); break;
        case TD_DOUBLE_TAP: layer_off(1); unregister_code(KC_RALT); unregister_code(KC_0); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void double_ae_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_QUOTE); break;
        case TD_DOUBLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_QUOTE); break;
        default: break;
    }
}
void double_ae_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_QUOTE); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT_SHIFT); unregister_code(KC_QUOTE); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void double_oe_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SCLN); break;
        case TD_DOUBLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_SCLN); break;
        default: break;
    }
}
void double_oe_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SCLN); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT_SHIFT); unregister_code(KC_SCLN); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void double_ue_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: register_code(KC_LEFT_SHIFT); register_code(KC_LBRC); break;
        default: break;
    }
}
void double_ue_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LBRC); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LEFT_SHIFT); unregister_code(KC_LBRC); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

void move_window_desktop1_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_F1); break;
        case TD_DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_KP_1); break;
        default: break;
    }
}
void move_window_desktop1_reset(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_F1); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_KP_1); break;
        default: break;
    }
}

void move_window_desktop2_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_F2); break;
        case TD_DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_KP_2); break;
        default: break;
    }
}
void move_window_desktop2_reset(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_F2); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_KP_2); break;
        default: break;
    }
}

void move_window_desktop3_register(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_F3); break;
        case TD_DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_KP_3); break;
        default: break;
    }
}
void move_window_desktop3_reset(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_F3); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LCTL); unregister_code(KC_LALT); unregister_code(KC_KP_3); break;
        default: break;
    }
}


layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _CONTROL, _ADVANCED, _ADJUST);
    return state;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_270;
    }
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
    oled_write_P(corne_logo, false);
    // oled_write_P(PSTR("Kimiko"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_ADVANCED)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_CONTROL)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_space();
    render_space();
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_space();
    render_space();
    render_logo();
    render_space();
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
    return false;
}

#endif

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_ALPHAS] = { ENCODER_CCW_CW(KC_DOWN, KC_UP),          ENCODER_CCW_CW(KC_LEFT, KC_RGHT) },
    [_ADVANCED] =  { ENCODER_CCW_CW(RGB_HUI, KC_TAB),         ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_CONTROL] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),        ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),       ENCODER_CCW_CW(RGB_SAD, RGB_SAI) },
};
#endif // ENCODER_MAP_ENABLE


