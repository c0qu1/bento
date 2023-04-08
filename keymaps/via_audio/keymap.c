/* Copyright 2020 Dennis Nguyen <u/nguyedt>
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

enum layer_names {
  _MEDIA,
  _BROWSER,
  _INTELLIJ,
  _MACRO,
  _RGBLIGHTS
};

enum custom_keycodes {
  KC_CYCLE_LAYERS = SAFE_RANGE,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        |                  |                    |  Knob : Vol Up/Dn |
        |      Mail        |         Play       |    Press: Mute    |
        |      Prev        |         Next       |  Cycle Layers     |
     */
    [_MEDIA] = LAYOUT(
        KC_MAIL, KC_MPLY, KC_MUTE,
        KC_MPRV, KC_MNXT, KC_CYCLE_LAYERS
    ),
    /*
        |                  |                     |  Knob : Desktops  |
        |       Back       |   Fwd               |    Press: Stop    |
        |     PrevTab      | NextTab             |   Cycle Layers    |
     */
    [_BROWSER] = LAYOUT(
        KC_WBAK, KC_WFWD, KC_WSTP,
        S(C(KC_TAB)), C(KC_TAB), KC_CYCLE_LAYERS
    ),
    /*
        |                  |                     |  Knob : Navigation back/fwd  |
        |       Back       |   Fwd               |    Press: Implementation/Usages    |
        |     PrevTab      | NextTab             |   Cycle Layers    |
     */
    [_INTELLIJ] = LAYOUT(
        KC_A, KC_B, KC_WSTP,
        KC_C, KC_D, KC_CYCLE_LAYERS
    ),
    /*
        |               |                        |  Knob : Windows    |
        | Slack Status  |    Zoom Toggle Mute    |     Enter          |
        |  WinScrnSht   |        Task View       |  Cycle Layers      |
     */
    [_MACRO] = LAYOUT(
        C(S(KC_Y)), CK_RST, CK_TOGG,
        G(S(KC_S)), MU_TOG, KC_CYCLE_LAYERS
    ),
    /*
        |               |                        | Knob : Saturation Up/Dn |
        | RGB MOD Cycle |   Right Shift          |     Toggle RGB          |
        |    Hue Cycle  |   Increase Brightness  |  Cycle Layers           |
     */
    [_RGBLIGHTS] = LAYOUT(
        RGB_MOD, KC_RSFT, RGB_TOG,
        RGB_HUI, RGB_VAI, KC_CYCLE_LAYERS
    ),

};

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 0, HSV_WHITE}
);
// Light LED 1 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN}
);
// Light LED 1 in green when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}
);
// Light LED 1 in purple when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_PURPLE}
);
// Light LED 3 in green when keyboard layer 4 is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 0, HSV_RED}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,    // Overrides other layers
    my_layer2_layer,    // Overrides other layers
    my_layer3_layer,    // Overrides other layers
    my_layer4_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _MEDIA));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BROWSER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _INTELLIJ));
    rgblight_set_layer_state(3, layer_state_cmp(state, _MACRO));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RGBLIGHTS));
    return state;
}

uint8_t selected_layer = 0;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_CYCLE_LAYERS: //custom macro
      if (record->event.pressed) {
        selected_layer++;
        if(selected_layer > 4) { selected_layer = 0;}
        layer_clear();
        layer_on(selected_layer);
      }
    break;
  }
return true;
}

// RGB config, for changing RGB settings on non-VIA firmwares
void change_RGB(bool clockwise) {
    bool shift = get_mods() & MOD_MASK_SHIFT;
    bool alt = get_mods() & MOD_MASK_ALT;
    bool ctrl = get_mods() & MOD_MASK_CTRL;

    if (clockwise) {
        if (alt) {
            rgblight_increase_hue();
        } else if (ctrl) {
            rgblight_increase_val();
        } else if (shift) {
            rgblight_increase_sat();
        } else {
            rgblight_step();
        }

  } else {
      if (alt) {
            rgblight_decrease_hue();
        } else if (ctrl) {
            rgblight_decrease_val();
        } else if (shift) {
            rgblight_decrease_sat();
        } else {
            rgblight_step_reverse();
        }
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (biton32(layer_state))
    {
        case _MEDIA:
            clockwise ? tap_code(KC_VOLU) : tap_code(KC_VOLD);
            break;
        case _BROWSER:
            register_code(KC_LCTRL);
            clockwise ? tap_code(KC_PGDOWN) : tap_code(KC_PGUP);
            unregister_code(KC_LCTRL);
            break;
        case _INTELLIJ:
            clockwise ? tap_code16(C(A(KC_RGHT))) : tap_code16(C(A(KC_LEFT)));
            break;
        case _MACRO:
            clockwise ? tap_code16(CK_UP) : tap_code16(CK_DOWN);
            break;
        case _RGBLIGHTS:
            change_RGB(clockwise);
            break;
    }
    return true;
}
