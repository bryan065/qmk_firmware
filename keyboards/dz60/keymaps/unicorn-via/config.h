#undef MANUFACTURER
#undef PRODUCT
#undef DESCRIPTION
#undef DEBOUNCE

#define MANUFACTURER    Anahein Electronics
#define PRODUCT         Unicorn RX-0 SplitSpace Keyboard

//disable VIA backlight function
#define RGB_BACKLIGHT_ENABLED 0

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 3

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 15

//RGB Matrix Effects
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#define RGB_MATRIX_KEYPRESSES               // Keypress effects
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS      // Frame buffer effects
  //disable standard effects
  #define DISABLE_RGB_MATRIX_ALPHAS_MODS
  #define DISABLE_RGB_MATRIX_BAND_SAT
  #define DISABLE_RGB_MATRIX_BAND_VAL
  #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
  #define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
  #define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
  #define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
  #define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  #define DISABLE_RGB_MATRIX_RAINDROPS
  //disable keypress effects
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXU
  #define DISABLE_RGB_MATRIX_MULTISPLASH

//RGB Matrix Config
#define RGB_DISABLE_AFTER_TIMEOUT 0         // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 26       // limit refresh rate to ~45fps
#define DRIVER_LED_TOTAL 100                // The number of LEDs connected
#define RGB_DI_PIN E2                       // Assign to pin E2 on DZ60 board
#define RGBLIGHT_SLEEP
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_STARTUP_HUE 0
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL 240