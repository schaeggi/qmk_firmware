#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* VSCode Layer
 * ┌─────────┬──────┬──────┐
 * │ Bookmark│ Next │ Prev │
 * ├─────────┼──────┼──────┤
 * │ Comment │      │      │
 * └─────────┴──────┴──────┘
 */
    [0] = LAYOUT_ortho_2x3(
        LCA(KC_K),        LCA(KC_L),         KC_F,
        LCTL(KC_NUHS),    LCTL(KC_KP_SLASH), KC_F
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
