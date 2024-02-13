#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* VSCode Layer
 * ┌─────────┬──────┬──────┐
 * │ Bookmark│ Next │ Prev │
 * ├─────────┼──────┼──────┤
 * │ Comment │ Prev.│ Edit │
 * └─────────┴──────┴──────┘
 */
    [0] = LAYOUT_ortho_2x3(
        MEH(KC_T),        MEH(KC_B),         MEH(KC_G),
        LCTL(KC_NUHS),    LCTL(KC_KP_SLASH), KC_NO
    ),
/* DaVinci Resolve Layer
 * ┌───┬───┬───┐
 * │ A │ B │ C │
 * ├───┼───┼───┤
 * │ D │ E │ F │
 * └───┴───┴───┘
 */
    // [1] = LAYOUT_ortho_2x3(
    //     KC_A,    KC_B,    KC_C,
    //     KC_D,    KC_E,    KC_F
    // ),
/*
 * ┌───┬───┬───┐
 * │ A │ B │ C │
 * ├───┼───┼───┤
 * │ D │ E │ F │
 * └───┴───┴───┘
 */
    // [2] = LAYOUT_ortho_2x3(
    //     KC_A,    KC_B,    KC_C,
    //     KC_D,    KC_E,    KC_F
    // )
};
