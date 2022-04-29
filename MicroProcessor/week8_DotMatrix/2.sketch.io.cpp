#include "SevSeg.h"
#include "RTClib.h"

SevSeg sevseg;
RTC_DS1307 rtc;

int LATCH = 10;
int DATA = 11;
int CLK = 13;
int data[8] = {0xff, 0x81, 0xa5, 0x81, 0xbd, 0xbd, 0x81, 0xff};

void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
}

void display(int addr, int data){
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, addr); //address
  shiftOut(DATA, CLK, MSBFIRST, data); //data
  digitalWrite(LATCH, HIGH);
}

int s = 0;
bool turn = true;


void loop() {

  for(int i = 1 ; i < 9 ; i++){
    display(i, data[i-1] << (1 * s) | data[i - 1] >> ( 8 - s));
  }
  s++;

  if(s == 9) {
    s = 0;
    turn ^= true;
  }
  delay(300);
 

//   for(int i = 1 ; i < 9 ; i++){
//     for(int j = 0 ; j < 9 ; j ++){
//         display(j, 0);
//         display(i+j, data[i-1]);
//         delay(300);
//     }
   
//   }
}
