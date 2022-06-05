#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    MD_BOOT,               //Restart into bootloader after hold timeout
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, _______,  \
        KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, _______, \
        KC_LCTL, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  _______, \
        KC_LSFT, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   MO(1), \
        KC_LCTL, MO(2), KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RIGHT  \
    ),
    [1] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______, _______, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    [2] = LAYOUT_65_ansi_blocker(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______, \
        _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, _______, KC_PGUP, KC_HOME, KC_PGDN,  KC_PSCR, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, KC_END,  _______, _______, _______,  _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                             _______, _______, _______, _______, _______  \
    ),
};

static uint8_t layer_indicators[] = {
    // layer_id, led_id, r, g, b
    1, 75, 255, 0, 0,
    2, 76, 0, 255, 0,
};

void rgb_matrix_indicators_user(void) {
    static layer_state_t layer_state_was = 0;
    for (int i = 0; i < sizeof(layer_indicators)/sizeof(layer_indicators[0]); i += 5) {
        const uint8_t layer_ix = layer_indicators[i];
        if (layer_state_cmp(layer_state, layer_ix))
            rgb_matrix_set_color(layer_indicators[i+1], layer_indicators[i+2], layer_indicators[i+3], layer_indicators[i+4]);
        // clear just after turning off, or when LEDs are disabled
        if (!rgb_matrix_config.enable || (layer_state_cmp(layer_state_was, layer_ix) && !layer_state_cmp(layer_state, layer_ix)))
            rgb_matrix_set_color(layer_indicators[i+1], 0, 0, 0);
    }
    layer_state_was = layer_state;
};

#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t boot_entry_timer;

    switch (keycode) {
        case KC_ESC:
            if (get_mods() & MOD_BIT(KC_LSHIFT)) {
                if (record->event.pressed)
                    register_code(KC_GRAVE);
                else
                    unregister_code(KC_GRAVE);
                return false;
            }
            return true;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                boot_entry_timer = timer_read32();
            } else {
                if (timer_elapsed32(boot_entry_timer) >= 300) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}
