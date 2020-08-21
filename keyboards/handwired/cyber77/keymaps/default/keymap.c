/*
  Copyright (c) 2022 Bryan065

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

#include QMK_KEYBOARD_H
#include "bryan065.h"
#include "rgb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BASE] = LAYOUT( /* Base */
		KC_ESC,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  KC_MUTE,
		KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS, KC_DEL,
		KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,        KC_CALC,
		KC_LSFT, KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   LALT(KC_PSCR),
		KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,  MO(_FUNCTION),           KC_SPC,    MO(_RGB), MO(_FUNCTION),          KC_LEFT, KC_DOWN, KC_RGHT
  	),

	[_FUNCTION] = LAYOUT( /* FN */
		KC_TILD,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, _______, _______, KC_MPLY,
		 KC_GRV, _______, _______, _______, _______, _______, _______,   KC_P7,   KC_P8,   KC_P9, _______, _______, _______,    LGUI(KC_PAUS), _______,
		_______, _______, _______, _______, _______, _______, _______,   KC_P4,   KC_P5,   KC_P6, _______, _______,          KC_PENT,          KC_MYCM,
		_______, _______, _______, _______, _______, _______, _______, _______,   KC_P1,   KC_P2,   KC_P3, _______,  KC_NUM,          KC_PGUP, KC_PSCR,
		_______, _______, _______,          _______,          _______,            KC_P0,          KC_PDOT, _______,          KC_HOME, KC_PGDN, KC_END
  	),

	[_RGB] = LAYOUT(
		_______, _______, _______,   _______, _______, _______,   _______, _______, _______,   _______, _______, _______,  _______, _______, _______, RGB_TOG,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, RGB_MOD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_SPI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_VAI, RGB_SPD,
		_______, _______, _______,          _______,          _______,          _______,          _______, _______,          RGB_SAD, RGB_VAD, RGB_SAI
  	),

	[_SYSTEM] = LAYOUT(
		EE_CLR, _______, _______,   _______, _______, _______,   _______, _______, _______,   _______, _______, _______,  _______, _______, _______, KC_SLEP,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,             VRSN, RGB_DEF,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_MAKE,          _______,
		_______, _______, _______, _______, _______, _______, QK_BOOT, NK_TOGG, _______, _______, _______, _______, KC_SCRL,          _______, _______,
		_______, GU_TOGG, _______,          _______,          _______,          _______,          _______, _______,          _______, _______, _______
  	)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FUNCTION] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [_RGB] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_SYSTEM] = { ENCODER_CCW_CW(_______, _______) },
};
#endif
