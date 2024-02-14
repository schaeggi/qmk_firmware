/* Custom Colemak keyboard layout with small modifications for german language */

#include QMK_KEYBOARD_H
#include <stdio.h>

// Combos - multiple keys pressed at the same time
const uint16_t PROGMEM combo_fp[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_wf[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_st[] = {KC_S, KC_T, COMBO_END};
// const uint16_t PROGMEM combo_rs[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM combo_ne[] = {KC_N, KC_E, COMBO_END};
// const uint16_t PROGMEM combo_ei[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_lu[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_uz[] = {KC_U, KC_Y, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_fp, LCTL(KC_DEL)),
    COMBO(combo_wf, LCTL(KC_BSPC)),
    COMBO(combo_st, RSFT(KC_8)),
    COMBO(combo_ne, RSFT(KC_9)),
    COMBO(combo_lu, LCTL(KC_LEFT)),
    COMBO(combo_uz, LCTL(KC_RIGHT)),
};

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

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 12.0
#define SCROLL_DIVISOR_V 12.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;


bool set_scrolling = true;


// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}


// https://docs.qmk.fm/#/feature_macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case DRAG_SCROLL:
            if (record->event.pressed) {
                set_scrolling = !set_scrolling;
            } else {
            }
            break;

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

layer_state_t layer_state_set_user(layer_state_t state) {
    // Enable set_scrolling if the current layer is layer 3
    if (get_highest_layer(state) == 3) {  
        set_scrolling = false;  // TODO: somehow invert y axis
    }
    else {
        set_scrolling = true;
    }
    return state;
}

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
  KC_ESC,  KC_1,    KC_2,  KC_3,    KC_4,  KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,  KC_F,    KC_P,  KC_B,                        KC_J,    KC_L,    KC_U,    KC_Y,    KC_NUHS, KC_DEL,
  KC_LSFT, KC_A,    KC_R,  KC_S,    KC_T,  KC_G,                        KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENTER,
  SC_LCPO, KC_Z,    KC_X,  KC_D,    KC_C,  KC_V,  KC_ENTER,   KC_SPC,   KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_PSLS, SC_RCPC,
                           KC_LALT, MO(3), TT(2), KC_SPC,     SC_SENT,  MO(1),   KC_LGUI, RALT_T(KC_APP)
),

/* Layer 1 - Special characters
 * ,----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |      |   ²  |   ³  |      |      |                    |      |   {  |   [  |   ]  |   }  |  Bsp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   @  |   %  |   +  |   (  |  {/} |                    |  [/] |   )  |   Ü  |   $  |   ~  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSft |   ä  |   !  |   ß  |   -  |ndash*|-------.    ,-------|   µ  |   =  |   €  |   ?  |   Ö  | Enter|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | LCtl |   <  |   >  |   *  |   _  |   ^  |-------|    |-------|   ´  |   "  |   &  |   °  |   |  | RCtl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Layer3|Layer2| /Space  /       \Enter \  |Layer1| LGUI| Menu |
 *                   |      |      |      |/       /         \+LSft \ |      |      |+AltGr|
 *                   `----------------------------'           '------''--------------------'
 */

[1] = LAYOUT(
  KC_TRNS, RALT(KC_1),  RALT(KC_2),     RALT(KC_3),    RALT(KC_4),    RALT(KC_5),                              RALT(KC_6), RALT(KC_7),  RALT(KC_8), RALT(KC_9),     RALT(KC_0),    KC_TRNS,
  KC_TRNS, RALT(KC_Q),  LSFT(KC_5),     KC_RBRC,       RSFT(KC_8),    CC_BRAC,                                 CC_BRAK,    RSFT(KC_9),  CC_UE,      LSFT(KC_4),     RALT(KC_RBRC), KC_TRNS,  // KC_LBRC
  KC_TRNS, CC_AE,       LSFT(KC_1),     KC_MINUS,      KC_SLASH,      CC_NDSH,                                 RALT(KC_M), RSFT(KC_0),  RALT(KC_E), LSFT(KC_MINUS), CC_OE,         KC_TRNS, // KC_QUOTE, KC_SCLN
  KC_TRNS, KC_NUBS,     LSFT(KC_NUBS),  LSFT(KC_RBRC), LSFT(KC_SLSH), KC_GRAVE,    KC_TRNS,        KC_TRNS,    KC_EQUAL,   LSFT(KC_2),  LSFT(KC_6), LSFT(KC_GRAVE), RALT(KC_NUBS), KC_TRNS,
                                        KC_TRNS,       KC_TRNS,       KC_TRNS,     KC_TRNS,        KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS
),

/* Layer 2 - Control and movement
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |(ESK)*|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  |  F10 |  Bsp |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (TM)*|  Ins | Home |  Up  |  End | PgUp |                    |   +  |   7  |   8  |   9  |  F11 |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | LSft |  Del | Right| Down | Left | PgDn |-------.    ,-------|   -  |   4  |   5  |   6  |  F12 | Enter|
 * |------+------+------+------+------+------| KLock |    |NumLock|------+------+------+------+------+------|
 * | LCtl |PrntS |  Cut |SelAll| Copy | Paste|-------|    |-------|   0  |   1  |   2  |   3  |   ,  | RCtl |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | Layer3|Layer2| /Space  /       \Enter \  |  0   |   * |   /  |
 *                   |      |      |      |/       /         \+LSft \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 *  *(ESK) ... Escape / LAlt + F4 Double tap
 *  *(TM) ... LCtl + LAlt + Del  LCA(KC_DEL)
 */

[2] = LAYOUT(
  CC_ESK,        KC_F1,    KC_F2,      KC_F3,      KC_F4,      KC_F5,                             KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_TRNS,
  LCA(KC_DEL),   KC_INS,   KC_HOME,    KC_UP,      KC_END,     KC_PGUP,                           KC_KP_PLUS,  KC_KP_7, KC_KP_8, KC_KP_9, KC_F11,   KC_TRNS,
  CC_STC,        KC_DEL,   KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_PGDN,                           KC_KP_MINUS, KC_KP_4, KC_KP_5, KC_KP_6, KC_F12,   KC_TRNS,
  KC_TRNS,       KC_PSCR,  LCTL(KC_X), LCTL(KC_A), LCTL(KC_C), LCTL(KC_V),  QK_LOCK,    KC_NUM,   KC_KP_0,     KC_KP_1, KC_KP_2, KC_KP_3, KC_COMMA,  KC_TRNS,
                                           KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,    KC_TRNS,  KC_KP_0,     KC_KP_ASTERISK, KC_KP_SLASH
),

/* Layer 3 - Shortcuts, Custom config, Mouse Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | SC_Q | GoD1 | GoD2 | GoD3 |  MtP |  MtN |                    | SC_6 | SC_7 | SC_8 | SC_9 | SC_0 | Reset|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (CC)*| SC_Q | SC_W | SC_F | SC_P | SC_B |                    |  -[] | LMB  | M_UP | RMB  | ScrUp|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | (V+)*| SC_A | SC_R | SC_S | SC_T | SC_G |-------.    ,-------|      | M_LT | M_DN | M_RT | ScrDn| SC_Q |
 * |------+------+------+------+------+------|  NVD  |    |  PVD  |------+------+------+------+------+------|
 * | (V-)*| SC_Y | SC_X | SC_D | Calc | SC_V |-------|    |-------|      |      | MMB  |      |      |TgLay4|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | (MP)*| Layer3|Layer2| /Space  /       \Enter \  |      |     |      |
 *                   |      |      |      |/       /         \+LSft \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 *  
 *  *(CC) ... LCtl + # (VSCode toggle comment)
 *  *GoDn ... Go to Desktop n (xfce only)
 *  *MtP/MtN ... Move active window to Previous/Next desktop (xfce only)
 *  *(MP) ... Media play/pause
 *  *(V+)/(V-) ... Volume up/down
 *  SC_n ... LAlt + LCtl + LSft + n
 *  NVD / PVD ... Goto next/previous virtual desktop (Windows 10)
 */

[3] = LAYOUT(
  MEH(KC_Q),      CC_MOV1,    CC_MOV2,     CC_MOV3,      LCA(KC_HOME),  LCA(KC_END),                         MEH(KC_6), MEH(KC_7),  MEH(KC_8),  MEH(KC_9),  MEH(KC_0),  CC_DRST,
  LCTL(KC_NUHS),  MEH(KC_Q),  MEH(KC_W),   MEH(KC_F),    MEH(KC_P),     MEH(KC_B),                           CC_LITM, KC_BTN1,  KC_MS_U,    KC_BTN2,    KC_WH_U,    KC_NO,
  KC_VOLU,        MEH(KC_A),  MEH(KC_R),   MEH(KC_S),    MEH(KC_T),     MEH(KC_G),                           KC_NO,   KC_MS_L,  KC_MS_D,    KC_MS_R,    KC_WH_D,    MEH(KC_Q),
  KC_VOLD,        MEH(KC_Y),  MEH(KC_X),   MEH(KC_D),    KC_CALC,       MEH(KC_V),    CC_WPDT,    CC_WNDT,   KC_NO,   KC_NO,    KC_BTN3,    KC_NO,      KC_NO,      DF(4),
                                           KC_MPLY,      KC_TRNS,       KC_TRNS,      KC_TRNS,    KC_TRNS,   KC_NO,   KC_NO,    KC_NO
  ),

/* Layer 4 - Gaming Layer
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  ESC |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | BSpc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB |   I  |   Q  |   W  |   E  |   R  |                    |   J  |   L  |  Up  |   Z  |   #  |  Del |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   G  | LSft |   A  |   S  |   D  |   F  |-------.    ,-------|   M  | Left | Down | Right|   O  | Enter|
 * |------+------+------+------+------+------| Enter |    |       |------+------+------+------+------+------|
 * |   T  | LCtl |   Y  |   X  |   C  |   V  |-------|    |-------|   K  |   H  |   B  |   T  |   /  | Lay0*|
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
  KC_T,   KC_LCTL, KC_Y, KC_X,    KC_C,    KC_V,    KC_ENT,       DF(0),   KC_K,   KC_H,    KC_B,    KC_T,    KC_PSLS, DF(0),
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