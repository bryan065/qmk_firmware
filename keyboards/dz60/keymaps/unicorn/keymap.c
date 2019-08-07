#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BASE = 0, 	// Base Layer
  _FUNC,     	// Function Layer
  _RGB,     	// RGB control Layer
  _SYS			  // System control layer (reset, sleep, etc)
};

enum my_keycodes {
  KC_00 = SAFE_RANGE
};

//rgb variables
extern 			    rgblight_config_t rgblight_config;
int					    RGB_LAYER0_mode;


  /* RGBLIGHT strip wiring. LED #75 to #99 is for underglow
  *  NEED TO REWRITE SECTION
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │0  │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10│ 11│ 12│ 13    │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │ 14  │15 │16 │17 │18 │19 │20 │21 │22 │23 │24 │25 │26 │27   │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │ 28   │29 │30 │31 │32 │33 │34 │35 │36 │37 │38 │39 │ 40     │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │ 41     │42 │43 │44 │45 │46 │47 │48 │49 │50 │51 │52    │53 │
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │ 54 │ 55 │ 56 │  57      │ 58 │  59    │60 │61 │62 │63 │64 │
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base layer / keyboard layout (FN2 = scroll lock when pressed)
  *  Backspace & left shift is full size compared to default layout
  *  2.75u * 2.25u space bars are swapped (longer one on left hand side)
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10│ 11│ 12│ bkspc │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │tab  │ q │ w │ e │ r │ t │ y │ u │ i │ o │ p │ [ │ ] │ \   │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │caps  │ a │ s │ d │ f │ g │ h │ j │ k │ l │ ; │ ' │ enter  │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │  shift │ z │ x │ c │ v │ b │ n │ m │ , │ . │ / │shift │ ↑ │
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │ctrl│win │alt │          │ FN │        │FN2│FN │ ← │ ↓ │ → │
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_BASE] = LAYOUT(
    LT(_SYS, KC_ESC), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, _______, KC_BSPC,
    KC_TAB , KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, _______, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(_FUNC), KC_SPC, LT(_RGB, KC_SLCK), MO(_FUNC), KC_LEFT, KC_DOWN, KC_RIGHT
    ),
  /* function layer - NEED TO ADD INSERT KEYCODE
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │~  │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│delete │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │     │   │   │   │   │   │   │ 7 │ 8 │ 9 │   │   │   │     │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │      │   │   │   │   │   │   │ 4 │ 5 │ 6 │   │   │ insert │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │   │   │ 1 │ 2 │ 3 │   │   │NLCK  │pup│
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │  0     │   │   │hom│pdn│end│
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_FUNC] = LAYOUT(
    KC_TILD, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, _______, KC_DEL,
    _______, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, _______, _______, KC_INS,
    _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______, _______, KC_NLCK, KC_PGUP,
    _______, _______, _______, _______, _______, KC_P0, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
  /* RGB layer (RMD = RGB_RMOD, MSW = RGB_M_SW)
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │   │   │   │   │   │   │   │   │   │   │   │   │   │wininfo│
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │     │   │   │   │VAD│VAI│   │   │HUI│   │   │   │   │pscr │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │      │   │   │   │TOG│MOD│RMD│SAD│HUD│SAI│   │   │        │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │MSW│   │   │   │   │   │   │      │vup│
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │        │   │mut│ply│ply│vdn│
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_RGB] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_PAUS),
    _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, RGB_HUI, _______, _______, _______, _______, LGUI(KC_PSCR),
    _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_SAD, RGB_HUD, RGB_SAI, _______, _______, _______,
    _______, _______, _______, _______, _______, RGB_M_SW, _______, _______, _______, _______, _______, _______, _______, KC_VOLU,
    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_MPLY, KC_MPLY, KC_VOLD
    ),
  /* System layer
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │   │   │   │   │   │   │   │   │   │   │   │   │   │sleep  │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │Reset │   │   │   │   │   │   │   │   │   │   │   │power   │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │   │   │   │   │   │   │   │      │   │
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │        │   │   │   │   │   │
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_SYS] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    RESET  , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PWR,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};

// OLD****************************************************
//light up per key LED based on keycode. If keycode is KC_NO or KC_TRNS, don't light up that key
//void rgblight_set_layer(uint8_t RGB_r,uint8_t RGB_g,uint8_t RGB_b, uint32_t state) {
//  //turn per led on
//  int KeyCounter = 0; //keycounter contains the physical offset to match up rgblight_setrgb_at with the physical position
//  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
//    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
//      switch (keymap_key_to_keycode(biton32(state), (keypos_t){ .row = r, .col = c })) {
//        case KC_TRNS:
//          break;
//        case KC_NO:
//          break;
//        default:
//          rgblight_setrgb_at(RGB_r,RGB_g,RGB_b, KeyCounter);
//          break;
//      }
//      KeyCounter = (r*15) + c;
//    }
//  }
//}
// OLD****************************************************

//light up per key LED based on keycode. If keycode is KC_NO or KC_TRNS, don't light up that key
void rgblight_set_layer(uint8_t RGB_r,uint8_t RGB_g,uint8_t RGB_b, uint32_t state) {
  //turn per led on
  int KeyCounter = 0; //keycounter contains the physical offset to match up rgblight_setrgb_at with the physical position
  for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
    if (record->event.pressed) { break; }
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
      if (record->event.pressed) { break; }
      switch (keymap_key_to_keycode(biton32(state), (keypos_t){ .row = r, .col = c })) {
        case KC_TRNS:
          break;
        case KC_NO:
          break;
        default:
          rgblight_setrgb_at(RGB_r,RGB_g,RGB_b, KeyCounter);
          break;
      }
      KeyCounter = (r*15) + c;
    }
  }
}

//turn underglow back on
void rgblight_set_underglow(uint8_t RGB_r,uint8_t RGB_g,uint8_t RGB_b) {
  for (int i = 74; i < 100; i++) {
    rgblight_setrgb_at(RGB_r,RGB_g,RGB_b, i);
  }
}

void keyboard_post_init_user(void) {
  //save last used RGB mode on init
  RGB_LAYER0_mode = rgblight_config.mode;
}

//set the RGB lights based on the layer
uint32_t layer_state_set_user(uint32_t state) {
    switch (biton32(state)) {
      case _FUNC:
        if (rgblight_config.enable == 1) {
          rgblight_mode( 1 );
          rgblight_setrgb (0, 0, 50);
          rgblight_set_underglow (0, 255, 255);
          rgblight_set_layer(0, 255, 255, state);
        }
        break;
      case _RGB:
        if (rgblight_config.enable == 1) {
          rgblight_mode( 1 );
          rgblight_setrgb (0, 0, 50);
          rgblight_set_underglow (188, 93, 255);
          rgblight_set_layer(0, 255, 255, state);
        }
        break;
      case _SYS:
        if (rgblight_config.enable == 1) {
          rgblight_mode( 1 );
          rgblight_setrgb (0, 0, 0);
          rgblight_set_underglow (255, 0, 0);
          rgblight_set_layer(255, 255, 0, state);
        }
        break;
      default: //  for any other layers, or the default layer
        if (rgblight_config.enable == 1) {
          rgblight_mode( RGB_LAYER0_mode );
        }
        break;
    }
    return state;
}

/*Intercept RGB keycodes
* When any of the keycodes below are called for the first time after shifting into another layer, we'll intercept it and show the base layer
* RGB mode/color before cycling/saving states.
*    This allow us to shift into another layer (such as our RGB adjustment layer) and have the RGB indicate which layer we are in. While shifted,
*    we can still adjust our base layer RGB color/mode.
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_MOD:
    case RGB_RMOD:
    case RGB_M_SW:
    case RGB_VAI:
    case RGB_VAD:
      if (rgblight_config.enable == 1) {
        if (record->event.pressed) {
          if (rgblight_config.mode == RGB_LAYER0_mode) {;
                    return true;
                } else {
                    rgblight_mode( RGB_LAYER0_mode );
                    return false;
                }
        } else {
          RGB_LAYER0_mode = rgblight_config.mode;
          return true;
        }
      }
    case RGB_TOG: //fix weird issue with toggle and also don't write toggle state to eeprom
      if (record->event.pressed) {
        rgblight_mode( RGB_LAYER0_mode );
        rgblight_toggle_noeeprom();
      }
      return false;
    default:
      return true; //process all other keycodes normally
  }
}
