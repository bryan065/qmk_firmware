/* Copyright 2021 peepeetee
 * Copyright 2021 bdtc123
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

#include "version.h"
#include <lib/lib8tion/lib8tion.h>

uint16_t     spam_timer;
uint16_t     spam_interval = 1000;
HSV          rgb_original_hsv;
uint16_t     boot_timer;
int8_t       boot_status = 0;

static bool  RGB_MOD_FLAG;

// Spam keys for Lost Ark
uint8_t SPAM;

// 0 - Off
// 1 - Q
// 2 - W
// 3 - E
// 4 - R
// 5 - A
// 6 - S
// 7 - D
// 8 - F
// 9 - G

// Define custom values if not defined in config.h
#if STARTUP_ANIM_TIME < 0
#   error STARTUP_ANIM_TIME must be greater than 0
#elif !defined (STARTUP_ANIM_TIME)
#   define STARTUP_ANIM_TIME 2200
#endif

enum keyboard_layers {
  _BASE = 0, 	// Base Layer
  _FUNC,     	// Function Layer
  _SYS,     	// RGB control Layer
  _ETC          // System control layer (reset, sleep, etc)
};

enum custom_keycodes {
    RGB_DEFAULT = SAFE_RANGE,
    VRSN,
    KC_MAKE,
    KC_Q_SPAM,
    KC_W_SPAM,
    KC_E_SPAM,
    KC_R_SPAM,
    KC_A_SPAM,
    KC_S_SPAM,
    KC_D_SPAM,
    KC_F_SPAM,
    KC_G_SPAM,
    NEW_SAFE_RANGE,
};

//============Tap Dance Functions===================//
#ifdef TAP_DANCE_ENABLE
    // Define a type for as many tap dance states as you need
    typedef enum {
        TD_NONE,
        TD_UNKNOWN,
        TD_SINGLE_TAP,
        TD_SINGLE_HOLD,
        TD_DOUBLE_TAP,
        TD_DOUBLE_HOLD
    } td_state_t;

    typedef struct {
        bool is_press_action;
        uint8_t state;
    } td_tap_t;

    // Tap dance keycodes
    enum {
        TD_SYS_QL
    };

    // Function associated with all tap dances
   td_state_t cur_dance(qk_tap_dance_state_t *state);

    // Functions associated with individual tap dances
    void ql_finished(qk_tap_dance_state_t *state, void *user_data);
    void ql_reset(qk_tap_dance_state_t *state, void *user_data);

    // Determine the current tap dance state
    td_state_t cur_dance(qk_tap_dance_state_t *state) {
        if (state->count == 1) {
            if (!state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        } else if (state->count == 2) {
            if (!state->pressed) return TD_DOUBLE_TAP;
            else return TD_DOUBLE_HOLD;
        }
        else return TD_UNKNOWN;
    }

    // Initialize tap structure associated with example tap dance key
    static td_tap_t ql_tap_state = {
        .is_press_action = true,
        .state = TD_NONE
    };

    // Functions that control what our tap dance key does
    void ql_finished(qk_tap_dance_state_t *state, void *user_data) {
        ql_tap_state.state = cur_dance(state);
        switch (ql_tap_state.state) {
            case TD_SINGLE_TAP:
                if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                    tap_code(KC_CAPS); // Disable caps if it's enabled
                }
                break;
            case TD_SINGLE_HOLD:
                break;
            case TD_DOUBLE_TAP:
                //if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {}       // Enable caps if it's disabled
                //else {
                    tap_code(KC_CAPS);
                //}
                break;
            case TD_DOUBLE_HOLD:
                layer_on(_SYS);
                break;
        }
    }

    // Function that controls the reset tap dance
    void ql_reset(qk_tap_dance_state_t *state, void *user_data) {
        // If the key was held down and now is released then switch off the layer
        if (ql_tap_state.state >= TD_DOUBLE_HOLD) {
            layer_off(_SYS);
        }
        ql_tap_state.state = TD_NONE;
    }

    // Associate our tap dance key with its functionality
    qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_SYS_QL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset),        // Caps lock/System layer dance
    };
#endif
//============Tap Dance Functions End================//


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,       KC_F5,   KC_F6,   KC_F7,   KC_F8,        KC_F9,   KC_F10,  KC_F11,  KC_F12,      KC_DEL,  LALT(KC_PSCR), KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,              KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
  TD(TD_SYS_QL),       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                  KC_P4,   KC_P5,   KC_P6,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,     KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_LCTL,   KC_LGUI, KC_LALT,                       KC_SPC,                             KC_RALT, MO(1),   KC_RCTL,      KC_LEFT, KC_DOWN, KC_RGHT,   KC_P0,   KC_PDOT
    ),
    [_FUNC] = LAYOUT(
        _______,          _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,     _______, KC_PSCR, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_HUI, RGB_VAI, RGB_SAI, _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 RGB_RMOD, RGB_TOG, RGB_MOD,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU,   RGB_HUD, RGB_VAD, RGB_SAD, RGB_DEFAULT,
        _______,   _______, _______,                      _______,                             _______, _______, _______,      _______, KC_VOLD, _______,   _______, _______
    ),
    [_SYS] = LAYOUT(
        _______,          _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,     _______, _______, _______, RESET  ,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
        _______, KC_Q_SPAM, KC_W_SPAM, KC_E_SPAM, KC_R_SPAM, _______, _______, _______, _______, _______, _______, _______, _______, VRSN,         _______, _______, _______, _______,
        _______, KC_A_SPAM, KC_S_SPAM, KC_D_SPAM, KC_F_SPAM, KC_G_SPAM, _______, _______, _______, _______, _______, _______, KC_MAKE,             _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______, _______,          _______,   _______, _______, _______, _______,
        _______,   GUI_TOG, _______,                      _______,                             _______, _______, _______,      _______, _______, _______,   _______, _______
    ),
    [_ETC] = LAYOUT(
        _______,          _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,     _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
        _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
        _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______,
        _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   _______, _______, _______, _______,
        _______,   _______, _______,                      _______,                             _______, _______, _______,      _______, _______, _______,   _______, _______
    ),

};

    // [X] = LAYOUT(
    //     _______,          _______, _______, _______, _______,     _______, _______, _______, _______,      _______, _______, _______, _______,     _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,              _______, _______, _______, _______,
    //     _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______,
    //     _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______, _______, _______,
    //     _______,            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,   _______, _______, _______, _______,
    //     _______,   _______, _______,                      _______,                             _______, _______, _______,      _______, _______, _______,   _______, _______
    // ),


//===============Custom Functions=========================//
// Enable splash math function if ENABLE_RGB_MATRIX_SPLASH was not defined
#if !defined (ENABLE_RGB_MATRIX_SPLASH)
    // Splash animation math
    HSV SPLASH_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
        uint16_t effect = tick - dist;
        if (effect > 255) effect = 255;
        hsv.h += effect;
        hsv.v = qadd8(hsv.v, 255 - effect);
        return hsv;
    }
#endif

#if defined (ENABLE_RGB_MATRIX_SPLASH)
    HSV SPLASH_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);
#endif
// End of splash math functions

// Boot animation, run only if RGB_MATRIX_ENABLED is defined and if the matrix is enabled.
void rgb_matrix_boot_anim(uint8_t boot_anim) {
    #if defined (RGB_MATRIX_ENABLE)
        if (rgb_matrix_config.enable) {
            rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, RGB_MATRIX_MAXIMUM_BRIGHTNESS);   // Set brightness to maximum allowed before playing animation
            rgb_matrix_set_speed_noeeprom(64);                                                                              // Set animation speed to default before playing animation
            boot_timer = timer_read();
            boot_status = boot_anim;
        }
    #endif
} // End of boot animation

//===============Custom Functions End=====================//

//=================Keycode Functions ================//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// Custom keycodes - On key release
    if (!record->event.pressed) {
        switch (keycode) {
        case KC_MAKE:   // Compiles the firmware, and adds the flash command based on keyboard bootloader
            clear_mods();
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) tap_code(KC_CAPS); // Disable caps if it's enabled
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
            tap_code(KC_ENT);
            return false;
        case VRSN:      // Prints QMK firmware version information
            send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE), TAP_CODE_DELAY);
            return false;
        case RGB_DEFAULT:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_HUE_PENDULUM2);
            return false;
        case KC_Q_SPAM: // Spam keys for idle farming in lost ark (Skill "Q" and "G" farm)
            if (SPAM != 1) { SPAM = 1;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_W_SPAM:
            if (SPAM != 2) { SPAM = 2;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_E_SPAM:
            if (SPAM != 3) { SPAM = 3;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_R_SPAM:
            if (SPAM != 4) { SPAM = 4;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_A_SPAM:
            if (SPAM != 5) { SPAM = 5;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_S_SPAM:
            if (SPAM != 6) { SPAM = 6;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_D_SPAM:
            if (SPAM != 7) { SPAM = 7;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_F_SPAM:
            if (SPAM != 8) { SPAM = 8;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_G_SPAM:
            if (SPAM != 9) { SPAM = 9;}
            else { SPAM = 0; }
            spam_timer = timer_read();
            return false;
        case KC_Q ... KC_R:      // Easily cancel key spam by pressing the normal key again
            SPAM = 0;
            return true;
        case KC_A ... KC_G:
            SPAM = 0;
            return true;
        default:
            return true;
        }
    } else {    // On key press
        switch (keycode) {
        case RGB_MODE_FORWARD ... RGB_SPD:  // Add RGB_MOD_FLAG = true to all RGB modification keys.
            RGB_MOD_FLAG = true;            //   This is to let the per key indicator know to stop if the RGB settings are modified so
            return true;                    //   the user can see the changes again without the layer indicator in the way
        default:
            return true;
        }
    } // End of custom keycodes
}
//=================Keycode Functions ================//

//==============Layer indicator code==============//
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            if (RGB_MOD_FLAG != false) { RGB_MOD_FLAG = false; }    // Set RGB_MOD_FLAG to false on the default layer
            break;
    }
    return state;
}
//==============Layer indicator code end==========//

//=======Matrix Scan User==========================//
void matrix_scan_user(void) {
    if (timer_elapsed(spam_timer) >= spam_interval) {
        switch(SPAM){
            case 1:
                tap_code(KC_Q);
                break;
            case 2:
                tap_code(KC_W);
                break;
            case 3:
                tap_code(KC_E);
                break;
            case 4:
                tap_code(KC_R);
                break;
            case 5:
                tap_code(KC_A);
                break;
            case 6:
                tap_code(KC_S);
                break;
            case 7:
                tap_code(KC_D);
                break;
            case 8:
                tap_code(KC_F);
                break;
            case 9:
                tap_code(KC_G);
                break;
        }
        spam_timer = timer_read();
    }
}
//=======Matrix Scan User==========================//


/* Boot_status
*   1 = Run splash boot animation
*   0 = Don't run anim / anim complete
*/
//==========Per Layer RGB Matrix indicators========//
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    void rgb_matrix_boot_anim_runner(uint8_t originx, uint8_t originy) {
        for (uint8_t i = led_min; i < led_max; i++) {
                    HSV hsv = rgb_matrix_config.hsv;
                    hsv.v   = 0;
                    for (uint8_t j = 0; j < 1; j++) {
                        int16_t  dx   = g_led_config.point[i].x - originx;     // X origin of splash animation
                        int16_t  dy   = g_led_config.point[i].y - originy;     // y origin of splash animation
                        uint8_t  dist = sqrt16(dx * dx + dy * dy);
                        uint16_t tick = scale16by8(timer_elapsed(boot_timer), qadd8(rgb_matrix_config.speed, 1));
                        hsv           = SPLASH_math(hsv, dx, dy, dist, tick);
                    }
                    hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
                    RGB rgb = hsv_to_rgb(hsv);
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
    }

    // Boot animation Code
    switch(boot_status) {
    case 1:
        if (timer_elapsed(boot_timer) >= STARTUP_ANIM_TIME) {                                                   // If timer is > boot animation time, load the saved RGB mode and fade in
            rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_original_hsv.v);  // Reset HSV.v to original value
            rgb_matrix_set_speed_noeeprom(rgb_matrix_config.speed);                                             // Reset speed to original value
            eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
            rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);                                                   // Load original mode
            boot_status = 0;
        } else {                                                                                                // Otherwise, run boot animation
            rgb_matrix_boot_anim_runner(112,0);
        }
        return;
    }   // End boot animation code

    // Layer indicator code
    if (get_highest_layer(layer_state) > 0 && !RGB_MOD_FLAG) {
        uint8_t layer = get_highest_layer(layer_state);

        // Per configured key indicator
        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                // Comparing LED index to matrix for configured keys or override keys
                if (index >= led_min && index <= led_max && index != NO_LED) {

                    uint16_t keycheck = keymap_key_to_keycode(layer, (keypos_t){col,row});
                    HSV hsv = rgb_matrix_config.hsv;
                    hsv.s   = 255;  // Ensure RGB colors are full saturation regardless of user's setting

                    // If key is configured, light it up
                    if (keycheck > KC_TRNS) {

                        // Per key overrides
                        switch (keycheck) {
                            case RESET:
                                hsv.h = 43; // YELLOW
                                break;
                            case LCTL(KC_BSPC):
                                hsv.h = 0;  // RED
                                break;
                            case KC_MAKE:
                                hsv.h = 43; // YELLOW
                                break;
                            case VRSN:
                                hsv.h = 43; // YELLOW
                                break;
                            // Keep at bottom
                            case NK_TOGG:
                                if (keymap_config.nkro == 1) { hsv.h = 85; } // GREEN if nkro is enabled
                                else
                            case GUI_TOG:
                                if (keymap_config.no_gui == 1) { hsv.h = 0; } // RED if GUI is disabled
                                else
                            default:        // Default per key color
                                hsv.s = 0;  // Set per key lights to white and respect the user's hsv.v value
                        }

                        // Make the key lights a bit brighter
                        if (hsv.v < (RGB_MATRIX_MAXIMUM_BRIGHTNESS - 30)) { hsv.v += 30; }
                        else { hsv.v = RGB_MATRIX_MAXIMUM_BRIGHTNESS; }

                        RGB rgb = hsv_to_rgb(hsv);
                        RGB_MATRIX_INDICATOR_SET_COLOR(index, rgb.r, rgb.g, rgb.b);
                    }
                    else {  // If key is not configured, light it up differently or not at all.
                        RGB_MATRIX_INDICATOR_SET_COLOR(index, 0, 0, 0); //If this line is commented out, the original animation will show through. However, freezes my keyboard after 2s.
                    }
                } // End of comparison code
            }
        } // End of per configured key indicator

    } // End of layer indicator code
}
//==========Per Layer RGB Matrix indicators========//

//==========Keyboard init/suspend functions========//
// code will run on keyboard wakeup
void suspend_wakeup_init_user(void) {
    // Fade in RGB when first plugging in kb or on resume from sleep
    #if (defined (RGB_MATRIX_ENABLE)) || (defined (RGBLIGHT_ENABLE))
        rgb_matrix_boot_anim(1);
    #endif
}
//=======Keyboard init/suspend functions End=======//
