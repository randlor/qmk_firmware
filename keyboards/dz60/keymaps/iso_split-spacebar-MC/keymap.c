// using as reference
// https://docs.qmk.fm/#/keymap

// thanks to atlacat, hailbreno, itsaferbie and weeheavy...

// and special thanks to  AGausmann and drashna for the layer-activated RGB underglow
// https://www.reddit.com/r/olkb/comments/6t1vdu/update_layeractivated_rgb_underglow/ 
// https://github.com/AGausmann/qmk_firmware/blob/agausmann-v3.x/keyboards/nyquist/keymaps/agausmann/keymap.c

#include QMK_KEYBOARD_H

/* 
* Each layer gets a name for readability.
* The underscores don't mean anything - you can
* have a layer called STUFF or any other name.
* Layer names don't all need to be of the same
* length, and you can also skip them entirely
* and just use numbers.
*
*/
#define BL 0     // Base Layer
#define FL 1     // Function Layer

/* 
* Let's give an easier name to the RGB modes 
* and assign the ones we want to the different layer
* these will then be used by the function below
*
*/
#define RGB_STA RGB_M_P   //rgb static
#define RGB_BRE RGB_M_B   //rgb breathe
#define RGB_RAI RGB_M_R   //rgb rainbow
#define RGB_SWI RGB_M_SW  //rgb swirl
#define RGB_SNA RGB_M_SN  //rgb snake
#define RGB_KNI RGB_M_K   //rgb knight
#define RGB_GRA RGB_M_G   //rgb gradient
#define RGB_XMS RGB_M_X   //rgb christmas
//
#define RGB_BL_MODE    rgblight_mode_noeeprom(3)              //rgb mode for BL layer
#define RGB_BL_LIGHT   rgblight_sethsv_noeeprom_turquoise()   //rgb light for BL layer
//
#define RGB_FL_MODE    rgblight_mode_noeeprom(1)             //rgb mode for FL layer
#define RGB_FL_LIGHT   rgblight_sethsv_noeeprom_orange()      //rgb light for FL layer
      
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
  /* Keymap BL: Base Layer (Default Layer)
   *
   *,-----------------------------------------------------------.
   *|Esc| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - | = |Backsp |
   *|-----------------------------------------------------------|
   *| Tab | q | w | e | r | t | y | u | i | o | p | [ | ] |enter|
   *|------------------------------------------------------     |
   *| Caps  | a | s | d | f | g | h | j | k | l | ; | ' | # |   |
   *|-----------------------------------------------------------|
   *|Shft| \ | z | x | c | v | b | n | m | , | . | / |Rshft |Up |
   *|-----------------------------------------------------------|
   *|Ctrl|Gui |Alt | Space  | FN |  Space  |App |Ctl|Lft|Rgt|Dn |
   *`-----------------------------------------------------------'
   */
   [BL] = LAYOUT_60_c_iso(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	      KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_MINS,   KC_EQL,    KC_BSPC,
        KC_TAB ,   KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_LBRC,   KC_RBRC,
        KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,   KC_NUHS,   KC_ENT,
        KC_LSFT,   KC_NUBS,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_RSFT,   KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,   KC_SPC,    MO(FL),    KC_SPC,    KC_APP,    KC_RCTL,   KC_LEFT,    KC_RIGHT,    KC_DOWN),

  /* Keymap FL: Function Layer
   *
   *,-----------------------------------------------------------.
   *| ` |F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10 |F11 |F12 |Del |
   *|-----------------------------------------------------------|
   *|     |   |   |   |   |   |   |   |   |   |   |V- |V+ |     |
   *|------------------------------------------------------     |
   *|       |   |   |   |   |   |   |   |   |   |   |   |   |   |
   *|-----------------------------------------------------------|
   *| HUI|SAI|VAI|   |   |   |   |   |   |   |   |   | Play |PgU|
   *|-----------------------------------------------------------|
   *| HUD|SAD |VAD |  TOG   | NO |  MOD    |    |   |<M |M> |PgD|
   *`-----------------------------------------------------------'
   */
   [FL] = LAYOUT_60_c_iso(
	//  1          2          3          4          5          6          7          8          9          10         11         12         13         14
	      KC_GRV,    KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,     KC_F10,    KC_F11,     KC_F12,    KC_DEL,
        _______ ,  _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   KC_VOLD,    KC_VOLU,
        _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,
        RGB_HUI,   RGB_SAI,   RGB_VAI,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,   _______,    KC_MPLY,   KC_PGUP,
        RGB_HUD,   RGB_SAD,   RGB_VAD,              RGB_TOG,   KC_TRNS,   RGB_MOD,                         _______,   _______,   KC_MPRV,    KC_MNXT,   KC_PGDN),

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}


// layer-activated RGB underglow

void matrix_scan_user(void) {

  #ifdef RGBLIGHT_ENABLE

  static uint8_t old_layer = 1;
  uint8_t new_layer = biton32(layer_state);

  if (old_layer != new_layer) {
    switch (new_layer) {
      case BL:
          RGB_BL_MODE;
          RGB_BL_LIGHT;        
        break;
      case FL:
          RGB_FL_MODE;
          RGB_FL_LIGHT;  
        break;
    }

    old_layer = new_layer;
  }

  #endif //RGBLIGHT_ENABLE

}
