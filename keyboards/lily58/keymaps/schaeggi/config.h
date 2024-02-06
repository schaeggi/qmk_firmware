/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* set number of layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5  

/* Select hand configuration */
// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

/* Change SpaceCadet Control-Brackets to DE layout */
#define LCPO_KEYS KC_LCTL, KC_LSFT, KC_8
#define RCPC_KEYS KC_LCTL, KC_LSFT, KC_9

#define TAPPING_TOGGLE 5
#define USB_POLLING_INTERVAL_MS 5  // set the USB polling rate in milliseconds; default is 10

// #define QUICK_TAP_TERM 0
#define TAPPING_TERM 250

/* Setup trackball */
// #define POINTING_DEVICE_LEFT
#define POINTING_DEVICE_ROTATION_90