#include <HID-Project.h>
#include <HID-Settings.h>
#include <JC_Button.h>

const byte BUTTON_PIN = 7;
const Button btn(BUTTON_PIN);

const KeyboardKeycode ZOOM_MAC_MUTE_ALL[] = {
  KEY_LEFT_GUI,
  KEY_LEFT_CTRL,
  KEY_M,
};

const KeyboardKeycode ZOOM_WIN_MUTE_ALL[] = {
  KEY_LEFT_ALT,
  KEY_M,
};

void setup() {
  Serial.begin(9600);

  btn.begin();
  NKROKeyboard.begin();
}

void loop() {
  btn.read();
  if (btn.wasPressed()) {
    auto& keys = ZOOM_MAC_MUTE_ALL;
    
    doKeypress(keys, sizeof(keys)/sizeof(keys[0]));
  }
}

void doKeypress(KeyboardKeycode keys[], int size){
  for (int i=0; i<size; ++i){
    NKROKeyboard.add(keys[i]);
  }
  NKROKeyboard.send();
  NKROKeyboard.releaseAll();
  NKROKeyboard.println();

  delay(100);
  Keyboard.write(KEY_RETURN);
}

// See key layouts here: https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h
