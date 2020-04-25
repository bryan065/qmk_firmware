#include QMK_KEYBOARD_H

static uint16_t   dynamic_loop_timer;
static uint16_t   idle_timer;
static bool       timeout;
static uint16_t   timeout_delay = TIMEOUT_DELAY;
static uint16_t   fadetime;
static uint16_t   rgb_matrix_v;

enum keyboard_layers {
  _BASE = 0, 	// Base Layer
  _FUNC,     	// Function Layer
  _RGB,     	// RGB control Layer
_SYS	};		  // System control layer (reset, sleep, etc)


enum my_keycodes {
  KC_00 = SAFE_RANGE };


//LED TO MATRIX MAP
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {  0,      1,      2,      3,      4,      5,      6,      7,  8,      9, 10, 11,     12, NO_LED,     13 },
        { 14, NO_LED,     15,     16,     17,     18,     19,     20, 21,     22, 23, 24,     25,     26,     27 },
        { 28, NO_LED,     29,     30,     31,     32,     33,     34, 35,     36, 37, 38,     39,     40, NO_LED },
        { 41, NO_LED,     42,     43,     44,     45,     46,     47, 48,     49, 50, 51, NO_LED,     52,     53 },
        { 54,     55, NO_LED,     56,     57, NO_LED,     58, NO_LED, 59, NO_LED, 60, 61,     62,     63,     64 }
    }, {
        // LED Index to Physical Position
        { 216,   0 }, { 192,   0 }, { 176,   0 }, { 160,   0 }, { 144,   0 }, { 128,   0 }, { 112,   0 }, {  96,   0 }, {  80,   0 }, {  64,   0 }, {  48,   0 }, {  32,   0 }, {  16,   0 },               {   0,   0 }, 
        { 220,  16 },               { 200,  16 }, { 184,  16 }, { 168,  16 }, { 152,  16 }, { 136,  16 }, { 120,  16 }, { 104,  16 }, {  88,  16 }, {  72,  16 }, {  56,  16 }, {  40,  16 }, {  24,  16 }, {   0,  16 },
        { 214,  32 },               { 188,  32 }, { 172,  32 }, { 156,  32 }, { 140,  32 }, { 124,  32 }, { 108,  32 }, {  92,  32 }, {  76,  32 }, {  60,  32 }, {  44,  32 }, {  28,  32 }, {   6,  32 },
        { 224,  48 },               { 208,  48 }, { 186,  48 }, { 164,  48 }, { 148,  48 }, { 132,  48 }, { 116,  48 }, { 100,  48 }, {  84,  48 }, {  68,  48 }, {  52,  48 },               {  24,  48 }, {   0,  48 },
        { 224,  64 }, { 208,  64 }, { 192,  64 },               { 128,  64 }, { 116,  64 }, { 100,  64 },                                           {  58,  64 }, {  50,  64 }, {  42,  64 }, {  24,  64 }, {   0,  64 },
        //underglow
        { 242,  64 }, { 216,  64 }, { 192,  64 }, { 176,  64 }, { 160,  64 }, { 144,  64 }, { 128,  64 }, { 112,  64 }, {  96,  64 }, {  80,  64 }, {  64,  64 }, {  48,  64 }, {  32,  64 }, {  16,  64 }, {   0,  64 },
        {   0,  16 }, {  16,  16 }, {  32,  16 },                                    {  88,   0 }, { 104,   0 }, { 120,   0 }, { 136,   0 },                                    { 176,  16 }, { 192,  16 }, { 216,  16 }
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,
        1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
        1, 1, 1,     4,   1,    4, 1, 1, 1, 1, 1,
        // Underglow LED's
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2
    } };


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
  * │Gsc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 10│ 11│ 12│ bkspc │
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
  * │`    │   │   │   │   │   │   │ 7 │ 8 │ 9 │   │   │   │     │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │      │   │   │   │   │   │   │ 4 │ 5 │ 6 │   │   │ insert │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │   │   │   │ 1 │ 2 │ 3 │   │NLCK  │pup│
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │  0     │   │   │hom│pdn│end│
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_FUNC] = LAYOUT(
    KC_TILD , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7, KC_F8, KC_F9, KC_F10 , KC_F11 , KC_F12 , _______, KC_DEL,
    KC_GRV, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______, _______, _______,
    _______ , _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, _______, _______, KC_INS,
    _______ , _______, _______, _______, _______, _______, _______, _______, KC_P1, KC_P2, KC_P3, _______, KC_NLCK, KC_PGUP,
    _______ , _______, _______, _______, _______, KC_P0, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
  /* RGB layer (RMD = RGB_RMOD, MSW = RGB_M_SW)
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │   │   │   │   │   │   │   │   │   │   │   │   │   │wininfo│
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │     │   │   │   │VAD│VAI│   │   │HUI│   │psc│   │   │pscr │
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │      │   │   │   │TOG│MOD│RMD│SAD│HUD│SAI│   │   │        │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │MSW│SPI│SPD│   │   │   │   │      │vup│
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │        │   │mut│ply│ply│vdn│
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_RGB] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LGUI(KC_PAUS),
    _______, _______, _______, _______, RGB_VAD, RGB_VAI, _______, _______, RGB_HUI, _______, LALT(KC_PSCR), _______, _______, LGUI(KC_PSCR),
    _______, _______, _______, _______, RGB_TOG, RGB_MOD, RGB_RMOD, RGB_SAD, RGB_HUD, RGB_SAI, _______, _______, _______,
    _______, _______, _______, _______, _______, RGB_M_SW, RGB_SPI, RGB_SPD, _______, _______, _______, _______, _______, KC_VOLU,
    _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_MPLY, KC_MPLY, KC_VOLD
    ),
  /* System layer
  * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐
  * │   │   │   │   │   │   │   │   │   │   │   │   │   │sleep  │
  * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
  * │     │   │   │   │   │   │   │   │   │   │   │   │   │Reset│
  * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
  * │      │   │   │   │   │   │   │   │   │   │   │   │        │
  * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
  * │        │   │   │   │   │   │   │   │   │   │   │      │   │
  * ├────┬───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴──┬┴──┬┴──┬───┼───┤
  * │    │    │    │          │    │        │   │   │   │   │   │
  * └────┴────┴────┴──────────┴────┴────────┴───┴───┴───┴───┴───┘
  */
  [_SYS] = LAYOUT(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SLEP,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ), };

//===============USB Suspend Functions====================//
void suspend_power_down_kb(void) {
  rgb_matrix_set_suspend_state(true);
  suspend_power_down_user(); }
void suspend_wakeup_init_kb(void) {
  rgb_matrix_set_suspend_state(false);
  suspend_wakeup_init_user(); }
//===============USB Suspend Functions====================//


//===============Custom Functions=========================//
//fade in animation
void rgb_matrix_fade_in(void) {
  //animation
  uint16_t rgb_matrix_v = rgb_matrix_config.hsv.v;
  for (uint16_t i = 0; i < rgb_matrix_v; i++) {     //fade from 0 to the current V value
    rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, i );
    matrix_scan();
  } }

//fade out animation
void rgb_matrix_fade_out(void) {
  //animation
  rgb_matrix_v = rgb_matrix_config.hsv.v;  //grab current V value to restore
  for (uint16_t i = rgb_matrix_v; i > 0; i--) {     //fade from the current V value to 0
    rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, i );
    matrix_scan();
  }
  rgb_matrix_disable_noeeprom();
  rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_v ); }  //restore V value
//===============Custom Functions=========================//


//===============Initialization Functions=================//
void keyboard_post_init_user(void) {
  dynamic_loop_timer = timer_read();
  rgb_matrix_fade_in(); }
//===============Initialization Functions=================//


//===============Main Loops===============================//
//RGB Matrix scan
void rgb_matrix_indicators_user (void) {
  //RGB timout, running every second
  if (timer_elapsed(dynamic_loop_timer) > 1000) {
    idle_timer++;
    dynamic_loop_timer = timer_read();
    if (idle_timer >= timeout_delay) {
      rgb_matrix_fade_out();
      idle_timer = 0;
      timeout = true;
    }
  } //End of RGB timeout
  
  //RGB Matrix with fade-in animation once flagged by "timeout"
  if ((timeout == false) && fadetime < rgb_matrix_v) {
    fadetime++;
    rgb_matrix_sethsv_noeeprom( rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, fadetime );
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  idle_timer = 0;          //reset idle timer
  if (timeout == true) {   //flag key pressed
    timeout = false;
    fadetime = 0;
    rgb_matrix_enable_noeeprom();
  }
  return true;
}
//===============Main Loops===============================//