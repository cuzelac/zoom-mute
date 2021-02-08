#include <HID-Project.h>
#include <HID-Settings.h>
#include <JC_Button.h>

const byte BUTTON_PIN = 7;
const Button btn(BUTTON_PIN);

void setup() {
  Serial.begin(9600);
  
  btn.begin();
  Keyboard.begin();
}

void loop() {
  btn.read();
  if(btn.wasPressed()) {
    Serial.println("WRITE!");

    zoomMuteAllMac();
  }
}

// See key layouts here: https://github.com/NicoHood/HID/blob/master/src/KeyboardLayouts/ImprovedKeylayouts.h
void zoomMuteAllMac() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.write(KEY_M);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_GUI);

  delay(100);
  Keyboard.write(KEY_RETURN);
}
