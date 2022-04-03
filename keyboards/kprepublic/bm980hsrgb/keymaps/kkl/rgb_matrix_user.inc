RGB_MATRIX_EFFECT(HUE_PENDULUM2)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Hue pendulum but with a larger huedelta
static HSV HUE_PENDULUM2_math(HSV hsv, uint8_t i, uint8_t time) {
    uint8_t huedelta = 70;
    hsv.h            = hsv.h + scale8(abs8(sin8(time) + (g_led_config.point[i].x) - 128), huedelta);
    return hsv;
}

bool HUE_PENDULUM2(effect_params_t* params) { return effect_runner_i(params, &HUE_PENDULUM2_math); }


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
