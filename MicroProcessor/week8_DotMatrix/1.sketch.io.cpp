#include "SevSeg.h"
#include "RTClib.h"

SevSeg sevseg;
RTC_DS1307 rtc;

long timer;
int temp = 0;
byte select_pin[4] = {2, 3, 4, 5};
byte data_pin[8] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
  byte numDigits = 4;
  bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_ANODE; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]

  sevseg.begin(hardwareConfig, numDigits, select_pin, data_pin, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);

  timer = millis();

}

void loop() {

  DateTime now = rtc.now();

  if(now.second() % 2 == 0){
    sevseg.setNumber(now.hour()*100 + now.minute(), -1);
  }
  else{
    sevseg.blank();
  }

  sevseg.refreshDisplay();

}

