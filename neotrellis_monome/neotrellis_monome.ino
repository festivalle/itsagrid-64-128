#include "Adafruit_NeoTrellisM4.h"
#include "MonomeSerialDevice.h"

// Monome setup
#define MONOMEDEVICECOUNT 1

MonomeSerial monomeDevices;
//monomeDevices->isMonome = true;
//monomeDevices->setupAsGrid(8, 16);
//elapsedMillis monomeRefresh;


// The NeoTrellisM4 object is a keypad and neopixel strip subclass
// that does things like auto-update the NeoPixels and stuff!
Adafruit_NeoTrellisM4 trellis = Adafruit_NeoTrellisM4();

boolean *lit_keys;

void setup(){
  Serial.begin(115200);
    
  trellis.begin();
  trellis.setBrightness(80);

  Serial.println("--NeoTrellis Monome--");

  lit_keys = new boolean[trellis.num_keys()];
  
  for (int i=0; i<trellis.num_keys(); i++) {
    lit_keys[i] = false;
  }
}
  
void loop() {
  // put your main code here, to run repeatedly:
  trellis.tick();

  while(trellis.available()){
    keypadEvent e = trellis.read();
    Serial.print((int)e.bit.KEY);
    if (e.bit.EVENT == KEY_JUST_PRESSED) {
      Serial.println(" pressed");
      // press stuff
       monomeDevices.sendGridKey(x, y, 1);
       
      trellis.setPixelColor(e.bit.KEY, 0xFFFFFF);
    }
    else if (e.bit.EVENT == KEY_JUST_RELEASED) {
      Serial.println(" released");
      // release stuff
       monomeDevices.sendGridKey(x, y, 0);
       
      trellis.setPixelColor(e.bit.KEY, 0x0);
    }
  }
  
  delay(10);
}
