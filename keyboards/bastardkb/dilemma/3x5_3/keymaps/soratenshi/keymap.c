/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#include "keycodes.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

/*
  TODO:
  Some "funny ideas:
    - Use combo with num to get to fn keys <=> gives me an additional layer to easy access
    - Combo keys for closing brackets
    - maybe try and chord more? Sounds easily doable
*/

// [left|right]:[main|move]
enum dilemma_keymap_layers {
    LAYER_GRAPHITE = 0, // default (main)
    LAYER_QWERTY, // default (ternary) <- preparation for split "gaming" keyboard

    // others may call it also "nav", although this layer does much more than just nav
    LAYER_PROGRAMMER, // left:hover
    LAYER_SYMBOL, // left:main

    LAYER_NUMBER, // right:hover
    LAYER_EXTRA_INT, // right:main

    LAYER_FUNCTION, // sub-layer of NUMBER
    LAYER_MOUSE, // own thing
};

#define NAV QK_TRI_LAYER_LOWER
#define SYM QK_TRI_LAYER_UPPER

 // ä Ä
#define KC_ETT UP(0xe4, 0xc4)
// ö Ö
#define KC_OEE UP(0xf6, 0xd6)
// ü Ü
#define KC_UEE UP(0xfc, 0xdc)
// ß
#define KC_SZ  UC(0xdf)

// homerow mods
#define WIN_N LGUI_T(KC_N)
#define WIN_I RGUI_T(KC_I)
#define ALT_R LALT_T(KC_R)
#define ALT_E RALT_T(KC_E)
#define CTL_TT LCTL_T(KC_T)
#define CTL_A RCTL_T(KC_A)
#define SFT_S LSFT_T(KC_S)
#define SFT_H RSFT_T(KC_H)

// other mods
#define PNT_Q LT(LAYER_MOUSE, KC_Q)
#define PNT_SLSH LT(LAYER_MOUSE, KC_SLASH)

#define SPC_SYM LT(LAYER_SYMBOL, KC_SPACE)
#define TAB_PRO LT(LAYER_PROGRAMMER, KC_TAB)
#define BSPC_NUM LT(LAYER_NUMBER, KC_BSPC)
#define ENT_I18 LT(LAYER_EXTRA_INT, KC_ENT)

enum programmer_macros {
    FN_PROG = SAFE_RANGE,
    PRONG_PROG,
    NS_PROG,
    DEREF_PROG,
};

// qwerty
#define PNT_Z LT(LAYER_MOUSE, KC_Z)

#ifndef POINTING_DEVICE_ENABLE
    #define DRGSCRL KC_NO
    #define DPI_MOD KC_NO
    #define S_D_MOD KC_NO
    #define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_GRAPHITE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_B,    KC_L,    KC_D,    KC_W,    KC_Z,    KC_SCLN,    KC_F,    KC_O,    KC_U,    KC_J,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          WIN_N,  ALT_R,   CTL_TT,  SFT_S,    KC_G,    KC_Y,      SFT_H,   CTL_A,   ALT_E,   WIN_I,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          PNT_Q,  KC_X,     KC_M,    KC_C,    KC_V,    KC_K,       KC_P, KC_COMM,  KC_DOT, PNT_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        XXXXXXX,  SPC_SYM, TAB_PRO,    BSPC_NUM,ENT_I18, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_QWERTY] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
          KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
         PNT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PNT_SLSH,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        XXXXXXX,  SPC_SYM, TAB_PRO,    BSPC_NUM,ENT_I18, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_PROGRAMMER] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    FN_PROG, PRONG_PROG, XXXXXXX, XXXXXXX , XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN   , KC_UP  , KC_RIGHT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    NS_PROG, DEREF_PROG, XXXXXXX, XXXXXXX , XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          XXXXXXX, XXXXXXX, _______,  XXXXXXX, KC_CAPS, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_SYMBOL] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, KC_NUBS, KC_PIPE, KC_PMNS, KC_UNDS,    KC_TILD, KC_LPRN, KC_LCBR, KC_LBRC, KC_LABK,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,  KC_PLUS,    KC_GRV,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        XXXXXXX, _______, XXXXXXX,    KC_QUOT, KC_DQUO, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_NUMBER] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      XXXXXXX, KC_7,    KC_8,       KC_9, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, KC_4,    KC_5,       KC_6, XXXXXXX,    XXXXXXX, MO(LAYER_FUNCTION), XXXXXXX, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      KC_0,    KC_1,    KC_2,       KC_3, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        XXXXXXX, XXXXXXX, XXXXXXX,    _______, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_EXTRA_INT] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, KC_SZ,   KC_OEE, KC_UEE, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX,    XXXXXXX, XXXXXXX, KC_ETT, XXXXXXX, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, _______, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      KC_F9, KC_F10, KC_F11, KC_F12,      XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      KC_F5, KC_F6, KC_F7, KC_F8,         XXXXXXX,    XXXXXXX, _______, XXXXXXX, XXXXXXX, RGB_RMOD,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      KC_F1, KC_F2, KC_F3, KC_F4,         XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                          XXXXXXX, XXXXXXX, _______,  XXXXXXX, XXXXXXX, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),

  [LAYER_MOUSE] = LAYOUT_split_3x5_3(
  // ╭─────────────────────────────────────────────╮ ╭─────────────────────────────────────────────╮
      QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX,
  // ├─────────────────────────────────────────────┤ ├─────────────────────────────────────────────┤
      _______, XXXXXXX, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, XXXXXXX, _______,
  // ╰─────────────────────────────────────────────┤ ├─────────────────────────────────────────────╯
                        XXXXXXX, MS_BTN1, MS_BTN2,    MS_BTN2, MS_BTN1, XXXXXXX
  //                   ╰───────────────────────────╯ ╰──────────────────────────╯
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
case FN_PROG: 
    if(record->event.pressed) {
        SEND_STRING("->");
    }
    return false;
case PRONG_PROG: 
    if(record->event.pressed) {
        SEND_STRING("=>");
    }
    return false;
case NS_PROG: 
    if(record->event.pressed) {
        SEND_STRING("::");
    }
    return false;
case DEREF_PROG: 
    if(record->event.pressed) {
        SEND_STRING(".*");
    }
    return false;
    }

    return true;
}

const uint16_t PROGMEM paren_combo[] = {KC_LPRN, KC_UNDS, COMBO_END};
const uint16_t PROGMEM bracket_combo[] = {KC_LBRC, KC_UNDS, COMBO_END};
const uint16_t PROGMEM brace_combo[] = {KC_LCBR, KC_UNDS, COMBO_END};
const uint16_t PROGMEM a_bracket_combo[] = {KC_LT, KC_UNDS, COMBO_END};

combo_t key_combos[] = {
  COMBO(paren_combo, KC_RPRN),
  COMBO(bracket_combo, KC_RBRC),
  COMBO(brace_combo, KC_RCBR),
  COMBO(a_bracket_combo, KC_GT),
};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[] = {
  &delete_key_override,
};

#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_MOUSE
#ifdef POINTING_DEVICE_ENABLE
#ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_GRAPHITE]   = {ENCODER_CCW_CW(KC_WH_D, KC_WH_U),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_QWERTY]     = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_PROGRAMMER] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_SYMBOL]     = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_NUMBER]     = {ENCODER_CCW_CW(RGB_HUD, RGB_HUI),  ENCODER_CCW_CW(RGB_SAD, RGB_SAI)},
    [LAYER_EXTRA_INT]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI),  ENCODER_CCW_CW(RGB_SPD, RGB_SPI)},
    [LAYER_MOUSE]      = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE

