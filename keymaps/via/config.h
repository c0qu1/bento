/*
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

#include "config_common.h"

#define QMK_ESC_OUTPUT F1 // usually COL
#define QMK_ESC_INPUT D5 // usually ROW
#define QMK_LED B0
#define QMK_SPEAKER C6
#define AUDIO_PIN C6

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6E67  // 'NG'uyedt
#define PRODUCT_ID      0x2133
#define DEVICE_VER      0x0100
#define MANUFACTURER    nguyedt
#define PRODUCT         Bento
#define DESCRIPTION     2x3 Macropad with Rotary Encoder

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 3

/* Keyboard Matrix Assignments */
#define DIRECT_PINS { \
    { D2, D4, F4 }, \
    { D7, B1, B3 } \
}

/* Handwired Pin Layout:

    { D7, B1, D2 }, \
    { E6, B4, B2 } \
*/

#define ENCODERS_PAD_A {D1}
#define ENCODERS_PAD_B {F5}
#define ENCODER_DIRECTION_FLIP

#define BACKLIGHT_PIN B6
#define BACKLIGHT_LEVELS 7

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #undef RGBLED_NUM
  #define RGBLED_NUM 3
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
  /*== all animations enable ==*/
  /* #define RGBLIGHT_ANIMATIONS */
  #define RGBLIGHT_EFFECT_TWINKLE
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_MAX_LAYERS 5
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
  #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_TWINKLE
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
