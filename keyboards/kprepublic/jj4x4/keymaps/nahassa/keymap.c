/* Copyright 2019
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

enum layers {
    _BASE = 0,
    _PAD,
    _RGB,
    _SEL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT_ortho_4x4(
        KC_PAUS,   KC_INS,    KC_HOME,   KC_PGUP,
        KC_SLCK,   KC_DEL,    KC_END,    KC_PGDN,
        KC_NO,     KC_WH_U,   KC_UP,     KC_WH_D,
        MO(_SEL),  KC_LEFT,   KC_DOWN,   KC_RGHT
    ),
	[_PAD] = LAYOUT_ortho_4x4(
        KC_P7,     KC_P8,     KC_P9,     KC_PAST,
        KC_P4,     KC_P5,     KC_P6,     KC_PMNS,
        KC_P1,     KC_P2,     KC_P3,     KC_PPLS,
        LT(_SEL,KC_PENT), KC_P0, KC_PDOT,   KC_PEQL
    ),
	[_RGB] = LAYOUT_ortho_4x4(
        RGB_TOG,   RGB_HUI,   RGB_SAI,   RGB_VAI,
        RGB_MOD,   RGB_HUD,   RGB_SAD,   RGB_VAD,
        BL_STEP,   KC_BTN1,   KC_MS_U,   KC_BTN2,
        MO(_SEL),  KC_MS_L,   KC_MS_D,   KC_MS_R
    ),
	[_SEL] = LAYOUT_ortho_4x4(
        KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_NO,     RESET,     KC_NO,     KC_NO,
        KC_NO,     KC_NO,     KC_NO,     KC_NO,
        KC_TRNS,   TO(_BASE), TO(_PAD),  TO(_RGB)
    )
};

// RGB LAYERS
// Light LEDs 1 & 2 in purple when keyboard layer 1 is active
const rgblight_segment_t PROGMEM layer_base[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_PURPLE}
);
// Light LEDs 1 & 2 in cyan when keyboard layer 2 is active
const rgblight_segment_t PROGMEM layer_pad[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_GOLDENROD}
);
// Light LEDs 1 & 2 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM layer_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_CHARTREUSE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_base,     // 0
    layer_pad,      // 1
    layer_rgb       // 2
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}

/*
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _PAD));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RGB));
    return state;
}
*/
