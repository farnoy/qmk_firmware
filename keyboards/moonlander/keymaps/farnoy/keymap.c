/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
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

enum layers {
    BASE,   
    COLEMAK,
    SYMB, 
    NAV,
    MDIA,
};

enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    [TRANS] = LAYOUT_moonlander(
        _______,   _______,   _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,                               _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,              _______,         _______,              _______,   _______,   _______,   _______,   _______,
                                                    _______,   _______,   _______,         _______,   _______,   _______
    ),
    */

    [BASE] = LAYOUT_moonlander(
        KC_EQL,           KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    _______,             _______, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,             KC_MINS,
        KC_TAB,           KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    _______,             _______, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,             KC_BSLS,
        KC_BSPC,          KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    _______,             _______, KC_H,   KC_J,    KC_K,    KC_L,    LT(MDIA,KC_SCLN), LGUI_T(KC_QUOT),
        KC_LSFT,     LCTL_T(KC_Z),  KC_X,    KC_C,    KC_V,    KC_B,                                  KC_N,   KC_M,    KC_COMM, KC_DOT,  RCTL_T(KC_SLSH),  KC_RSFT,
    LT(SYMB,KC_GRV), TG(COLEMAK), _______,_______, _______,                KC_LALT,    RCTL_T(KC_ESC),        _______, _______, _______, _______,          _______,
                                                LT(SYMB, KC_SPC), KC_BSPC, MO(NAV),           KC_ENT,  KC_TAB,  MO(SYMB)
    ),

    [COLEMAK] = LAYOUT_moonlander(
        _______,   _______,   _______,   _______,   _______,   _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   KC_Q,      KC_W,      KC_F,      KC_P,      KC_G,      _______,         _______,   KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   _______,
        _______,   KC_A,      KC_R,      KC_S,      KC_T,      KC_D,      _______,         _______,   KC_H,      KC_N,      KC_E,      KC_I,   LT(MDIA,KC_O),_______,
        _______,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,                                  KC_K,      KC_M,      KC_COMM,   KC_DOT,    _______,   _______,
        _______,   _______,   _______,   _______,   _______,              _______,         _______,              _______,   _______,   _______,   _______,   _______,
                                                    _______,   _______,   _______,         _______,   _______,   _______
    ),

    [SYMB] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,           _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, KC_LCBR, KC_RCBR, _______, _______,           _______, _______, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_F12,
        _______, _______, _______, KC_LPRN, KC_RPRN, _______, _______,           _______, _______, KC_4,    KC_5,    KC_6,    KC_PLUS, _______,
        _______, _______, _______, KC_LBRC, KC_RBRC, _______,                             _______, KC_1,    KC_2,    KC_3,    KC_MINS, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, KC_DOT,  KC_0,    KC_EQL,  _______,
                                            _______, _______, _______,           _______, _______, _______
    ),

    [NAV] = LAYOUT_moonlander(
        _______,   _______,   _______,   KC_PGUP,   KC_HOME,   _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   KC_PGDN,   KC_END,    _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   KC_LEFT,   KC_DOWN,   KC_UP,     KC_RIGHT,  _______,   _______,         _______,   _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,   _______,                               _______,   _______,   _______,   _______,   _______,   _______,
        _______,   _______,   _______,   _______,   _______,              _______,         _______,              _______,   _______,   _______,   _______,   _______,
                                                    _______,   _______,   _______,         _______,   _______,   _______
    ),

    [MDIA] = LAYOUT_moonlander(
        VRSN,     _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, EE_CLR,  QK_BOOT,
        _______,  KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, KC_VOLD, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,         RGB_VAI,            RGB_TOG,          _______, _______, _______, _______, _______,
                                            RGB_HUD, RGB_VAD, RGB_HUI,   RGB_SPD, RGB_SPI, RGB_MOD
    ),

    /*
    [MOUSE] = LAYOUT_moonlander(
        LED_LEVEL,_______,_______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, RESET,
        _______, _______, _______, KC_MS_U, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,           _______, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______, _______, _______, _______,                             _______, _______, KC_MPRV, KC_MNXT, _______, _______,
        EEP_RST, _______, _______, KC_BTN1, KC_BTN2,         _______,            _______,          KC_VOLU, KC_VOLD, KC_MUTE, _______, _______,
                                            _______, _______, _______,           _______, _______, _______
    ),
    */
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        }
    }
    return true;
}
