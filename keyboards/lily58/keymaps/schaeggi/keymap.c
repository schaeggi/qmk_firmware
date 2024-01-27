#include QMK_KEYBOARD_H
#include <stdio.h>


// ------------------ DEVTEST START ----------------------------- //
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    X_CTL,
    SOME_OTHER_DANCE
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

// ------------------ DEVTEST END ----------------------------- //




// Tap Dance declarations
enum {
    SHIFT_TO_CAPS,
    DOUBLE_RESET,

};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [SHIFT_TO_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [DOUBLE_RESET] = ACTION_TAP_DANCE_DOUBLE(QK_REBOOT, QK_BOOTLOADER),  // Bootloader for flashing new firmware
};


// custom keycode definitions
enum custom_keycodes {
    CC_WPDT = SAFE_RANGE,
    CC_WNDT,
    CC_STC = TD(SHIFT_TO_CAPS),
    CC_DRST = TD(DOUBLE_RESET),
};


// https://docs.qmk.fm/#/feature_macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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




/* Custom Colemak keyboard layout with small modifications for german language */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Layer 0 - Alphas
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  Bsp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   B  |                    |   J  |   L  |   U  |   Z  |   #  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSft |   A  |   R  |   S  |   T  |   G  |-------.    ,-------|   M  |   N  |   E  |   I  |   O  | Enter|
 * |------+------+------+------+------+------| Enter |    | Space |------+------+------+------+------+------|
 * | LCtl |   Y  |   X  |   D  |   C  |   V  |-------|    |-------|   K  |   H  |   ,  |   .  |   /  | RCtl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Layer3|Layer2| /Space  /       \Enter \  |Layer1| LGUI| Menu |
 *                   |      |      |      |/       /         \+LSft \ |      |      |+AltGr|
 *                   `----------------------------'           '------''--------------------'
 */

 [0] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,  KC_3,    KC_4,  KC_5,                        KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,  KC_F,    KC_P,  KC_B,                        KC_J,   KC_L,    KC_U,    KC_Y,    KC_NUHS, KC_DEL,
  KC_LSFT, KC_A,    KC_R,  KC_S,    KC_T,  KC_G,                        KC_M,   KC_N,    KC_E,    KC_I,    KC_O,    KC_ENTER,
  SC_LCPO, KC_Z,    KC_X,  KC_D,    KC_C,  KC_V,  KC_ENTER,   KC_SPC,   KC_K,   KC_H,    KC_COMM, KC_DOT,  KC_PSLS, SC_RCPC,
                           KC_LALT, MO(3), TT(2), KC_SPC,     SC_SENT,  MO(1),  KC_LGUI, RALT_T(KC_APP)
),

/* Layer 1 - Special characters
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |   ²  |   ³  |      |      |                    |      |   {  |   [  |   ]  |   }  |  Bsp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   @  |   %  |   +  |   {  |   [  |                    |   ]  |   }  |   Ü  |   $  |   ~  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSft |   ä  |   !  |   ß  |   -  |   (  |-------.    ,-------|   )  |   =  |   €  |   ?  |   Ö  | Enter|
 * |------+------+------+------+------+------|(ndash)|    |    µ  |------+------+------+------+------+------|
 * | LCtl |   <  |   >  |   *  |   _  |   ^  |-------|    |-------|   ´  |   "  |   &  |   °  |   |  | RCtl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Layer3|Layer2| /Space  /       \Enter \  |Layer1| LGUI| Menu |
 *                   |      |      |      |/       /         \+LSft \ |      |      |+AltGr|
 *                   `----------------------------'           '------''--------------------'
 */

[1] = LAYOUT(
  KC_TRNS, RALT(KC_1),  RALT(KC_2),     RALT(KC_3),    RALT(KC_4),    RALT(KC_5),                              RALT(KC_6), RALT(KC_7),  RALT(KC_8), RALT(KC_9),     RALT(KC_0),    KC_TRNS,
  KC_TRNS, RALT(KC_Q),  LSFT(KC_5),     KC_RBRC,       RALT(KC_7),    RALT(KC_8),                              RALT(KC_9), RALT(KC_0),  KC_LBRC,    LSFT(KC_4),     RALT(KC_RBRC), KC_TRNS,
  KC_TRNS, KC_QUOTE,    LSFT(KC_1),     KC_MINUS,      KC_SLASH,      RSFT(KC_8),                              RSFT(KC_9), RSFT(KC_0),  RALT(KC_E), LSFT(KC_MINUS), KC_SCLN,       KC_TRNS,
  KC_TRNS, KC_NUBS,     LSFT(KC_NUBS),  LSFT(KC_RBRC), LSFT(KC_SLSH), KC_GRAVE,    RSA(KC_SLSH),   RALT(KC_M), KC_EQUAL,   LSFT(KC_2),  LSFT(KC_6), LSFT(KC_GRAVE), RALT(KC_NUBS), KC_TRNS,
                                        KC_TRNS,       KC_TRNS,       KC_TRNS,     KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS
),

/* Layer 2 - Control and movement
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  Bsp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (CC)*|  Ins | Home |  Up  |  End | PgUp |                    |   +  |   7  |   8  |   9  |  F11 |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSft |  Del | Right| Down | Left | PgDn |-------.    ,-------|   -  |   4  |   5  |   6  |  F12 | Enter|
 * |------+------+------+------+------+------| KLock |    |NumLock|------+------+------+------+------+------|
 * | LCtl |PrntS |  Cut |SelAll| Copy | Paste|-------|    |-------|   0  |   1  |   2  |   3  |   ,  | RCtl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Layer3|Layer2| /Space  /       \Enter \  |  0   |   * |   /  |
 *                   |      |      |      |/       /         \+LSft \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 *  *(EX) ... LAlt + F4
 *  *(CC) ... LCtl + #
 */

[2] = LAYOUT(
  KC_TRNS,           KC_F1,    KC_F2,      KC_F3,      KC_F4,      KC_F5,                             KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_TRNS,
  LCTL(KC_NUHS),     KC_INS,   KC_HOME,    KC_UP,      KC_END,     KC_PGUP,                           KC_KP_PLUS,  KC_KP_7, KC_KP_8, KC_KP_9, KC_F11,   KC_TRNS,
  CC_STC,            KC_DEL,   KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,                           KC_KP_MINUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_F12,   KC_TRNS,
  KC_TRNS,           KC_PSCR,  LCTL(KC_X), LCTL(KC_A), LCTL(KC_C), LCTL(KC_V),  QK_LOCK,    KC_NUM,   KC_KP_0,     KC_KP_1, KC_KP_2, KC_KP_3, KC_COMMA,  KC_TRNS,
                                           KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_KP_0,     KC_KP_ASTERISK, KC_KP_SLASH
),

/* Layer 3 - Shortcuts, Custom config
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | (EX)*| GoD1 | GoD2 | GoD3 |  MtP |  MtN |                    |      |      |      |      |      | Reset|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (TM)*| SC_Q | Mail |FileMn| SC_P | SC_B |                    | LMB  | RMB  |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (V+)*| SC_A | SC_R | SC_S | SC_T | SC_G |-------.    ,-------|      |      |      |      |      | SC_Q |
 * |------+------+------+------+------+------|  NVD  |    |  PVD  |------+------+------+------+------+------|
 * | (V-)*|MsBtn3| SC_X |  Web | Calc | SC_V |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | (MP)*| Layer3|Layer2| /Space  /       \Enter \  |      |     |      |
 *                   |      |      |      |/       /         \+LSft \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 *  *(EX) ... LAlt + F4
 *  *(TM) ... LCtl + LAlt + Del  LCA(KC_DEL)
 *  *GoDn ... Go to Desktop n (xfce only)
 *  *MtP/MtN ... Move active window to Previous/Next desktop (xfce only)
 *  *(MP) ... Media play/pause
 *  *(V+)/(V-) ... Volume up/down
 *  SC_n ... LAlt + LCtl + LSft + n
 *  NVD / PVD ... Goto next/previous virtual desktop (Windows 10)
 */

[3] = LAYOUT(
  LALT(KC_F4),  LCTL(KC_F1),  LCTL(KC_F2), LCTL(KC_F3),  LCA(KC_HOME),  LCA(KC_END),                         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  CC_DRST,
  TD(X_CTL),  MEH(KC_Q),    KC_MAIL,     KC_MYCM,      MEH(KC_P),     MEH(KC_B),                           KC_BTN1, KC_BTN2, KC_NO,   KC_NO,   KC_NO,  KC_NO,
  KC_VOLU,      MEH(KC_A),    MEH(KC_R),   MEH(KC_S),    MEH(KC_T),     MEH(KC_G),                           KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  MEH(KC_Q),
  KC_VOLD,      KC_BTN3,      MEH(KC_X),   KC_WHOM,      KC_CALC,       MEH(KC_V),    CC_WPDT,    CC_WNDT,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  DF(4),
                                           KC_MPLY,      KC_TRNS,       KC_TRNS,      KC_TRNS,    KC_TRNS,   KC_NO,   KC_NO,   KC_NO
  ),

/* Layer 4 - Gaming Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSpc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB |   I  |   Q  |   W  |   E  |   R  |                    |   J  |   L  |  Up  |   Z  |   #  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   G  | LSft |   A  |   S  |   D  |   F  |-------.    ,-------|   M  | Left | Down | Right|   O  | Enter|
 * |------+------+------+------+------+------| Enter |    |       |------+------+------+------+------+------|
 * |   T  | LCtl |   Y  |   X  |   C  |   V  |-------|    |-------|   K  |   H  |   G  |   T  |   /  | Lay0*|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |  MMB  | LAlt| / Space /       \ RSft \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 * Lay0*  ... Toggle Back to Layer0
 */

[4] = LAYOUT(  // WASD-Gaming-Layer on home row
  KC_ESC, KC_1,    KC_2, KC_3,    KC_4,    KC_5,                           KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB, KC_I,    KC_Q, KC_W,    KC_E,    KC_R,                           KC_J,   KC_L,    KC_UP,   KC_Z,    KC_NUHS, KC_DEL,
  KC_G,   KC_LSFT, KC_A, KC_S,    KC_D,    KC_F,                           KC_M,   KC_LEFT, KC_DOWN, KC_RGHT, KC_O,    KC_ENT,
  KC_T,   KC_LCTL, KC_Y, KC_X,    KC_C,    KC_V,    KC_ENT,       DF(0),   KC_K,   KC_H,    KC_G,    KC_T,    KC_PSLS, DF(0),
                         KC_LALT, KC_BTN3, KC_LALT, KC_SPC,       KC_RSFT, KC_NO,  KC_NO,   KC_NO
  )
};


/* KEY OVERRIDES:
 *  Shift + Backspace ... Delete 
 *  Shift + Slash (KP) ... Backslash  */
const key_override_t slash_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_KP_SLASH, RALT(KC_MINUS));
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t backspace_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_BSPC);

const key_override_t** key_overrides = (const key_override_t*[]){
    &delete_key_override,
    &slash_key_override,
    &backspace_key_override,
    NULL
};


// ------------------ DEVTEST START ----------------------------- //
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

void x_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ESC); break;
        case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: register_code(KC_LALT); register_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X); break;
        default: break;
    }
}

void x_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ESC); break;
        case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LALT); unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions_test[] = {
    [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
};
