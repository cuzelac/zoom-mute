#include <HID-Project.h>
#include <HID-Settings.h>
#include <JC_Button.h>

const byte BUTTON_PIN = 7;
const byte SWITCH_PIN = 16;
const Button btn(BUTTON_PIN);

template <int N> struct KeyCombo {
  static const int size = N;
  KeyboardKeycode keys[N];
  int delay_ms;
};

const KeyCombo<3> ZOOM_MAC_MUTE_ALL = {
  {KEY_LEFT_GUI, KEY_LEFT_CTRL, KEY_M},
  100
};

const KeyCombo<2> ZOOM_WIN_MUTE_ALL = {
  {KEY_LEFT_ALT, KEY_M},
  0
};

void setup() {
  Serial.begin(9600);

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  btn.begin();
  NKROKeyboard.begin();
}

void loop() {
  btn.read();
  if (btn.wasPressed()) {
    auto switchState = digitalRead(SWITCH_PIN);

    switch(switchState) {
      case HIGH:
        doKeypress(ZOOM_MAC_MUTE_ALL);
        Serial.println("MAC");
        break;
      case LOW:
        doKeypress(ZOOM_WIN_MUTE_ALL);
        Serial.println("WIN");
        break;
      default:
        Serial.println("UNDEFINED SWITCH STATE");
        break;
    }
  }
}

template <int N> void doKeypress(KeyCombo<N> kc){
  for (int i=0; i<kc.size; ++i){
    NKROKeyboard.add(kc.keys[i]);
  }
  NKROKeyboard.send();
  NKROKeyboard.releaseAll();

  // If there's no delay, no need to send a newline
  if (0 != kc.delay_ms) {
    Serial.print("Delay: "); Serial.println(kc.delay_ms);
    delay(kc.delay_ms);
    NKROKeyboard.println();
  }
}

// See key layouts here: https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h
