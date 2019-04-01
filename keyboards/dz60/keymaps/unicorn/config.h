#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION
#undef RGBLED_NUM
#undef RGBLIGHT_ANIMATIONS

#define MANUFACTURER    Anahein Electronics
#define PRODUCT         Unicorn RX-0 SplitSpace Keyboard
#define DESCRIPTION     DZ60 Keyboard

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

//RBGLIGHT animations
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

//RGB config
#define RGBLED_NUM 100 //per-key LEDS: 65, keycode matrix size: 75, underglow LEDS: 25
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP

//re-order LED strip
#define RGBLIGHT_LED_MAP { \
	0 ,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, \
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, \
	32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 44, 46, 47, 48, \
	49, 50, 51, 52, 53, 54, 55, 57, 58, 59, 60, 62, 63, 65, 67, \
	69, 70, 71, 72, 73, 74,	75, 76, 77, 78, 79, 80, 81, 82, 83, \
	84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, \
	99, 15, 30, 43, 45, 56, 61, 64, 66, 68 }

// 15, 30, 43, 45, 56, 61, 64, 66, 68 are dead/blank keys that dont "exist" and have no LED