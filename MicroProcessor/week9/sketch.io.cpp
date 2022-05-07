#include <MD_MAX72xx.h>
#include <MD_Parola.h>
#include <SPI.h>

#define MAX_DEVICES 4

int LATCH = 10;
int DATA = 11;
int CLK = 13;

MD_MAX72XX mx = MD_MAX72XX(MD_MAX72XX::PAROLA_HW, DATA, CLK, LATCH, MAX_DEVICES);
MD_Parola p = MD_Parola(MD_MAX72XX::PAROLA_HW, LATCH, MAX_DEVICES);


void setup() {
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);

  pinMode(A1, INPUT);

  //mx.begin(); // mx 객체 사용
  p.begin(); // p 객체 사용

  Serial.begin(9600);
  Serial.println("Start");
}

void display(int addr, int data){
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLK, MSBFIRST, addr);
  shiftOut(DATA, CLK, LSBFIRST, data);
  digitalWrite(LATCH, HIGH);
}

int s = 0;
char str[][10] = {"Hello", "World" };
textEffect_t texteffect[] = { PA_WIPE, PA_WIPE_CURSOR, PA_OPENING_CURSOR, PA_CLOSING_CURSOR, PA_BLINDS, PA_MESH, PA_OPENING, PA_CLOSING, PA_SCAN_VERT, PA_DISSOLVE, PA_RANDOM, PA_PRINT, PA_SCROLL_RIGHT, PA_SCROLL_LEFT, PA_GROW_UP, PA_GROW_DOWN, PA_SCROLL_UP, PA_SCROLL_DOWN, PA_SCROLL_UP_RIGHT, PA_SCROLL_UP_LEFT, PA_SCROLL_DOWN_RIGHT, PA_SCROLL_DOWN_LEFT, };
char input[10];


void loop() {
  int aValue = analogRead(A1);
  int convertValue = map(aValue, 0, 1023, 0, 100);

  p.print((String) convertValue + "%");
  // if(p.displayAnimate()){ // 애니메이션 출력 종료를 대기
  //   p.displayScroll(input, PA_CENTER, texteffect[0], 100);
  // }


  // if(Serial.available()){
  //   //int input = Serial.read();
  //   String strInput = Serial.readStringUntil('\n');
  //   //char* input = strInput.c_str();
  //   strInput.toCharArray(input, strInput.length());

  //   //p.print(input); // 입력 값을 출력
  //   //Serial.println(input - '0');
  //   if(p.displayAnimate()){ // 애니메이션 출력 종료를 대기
  //     p.displayScroll(input, PA_CENTER, texteffect[0], 100);
  //   }
  // }

  /*
  // mx.setPoint(0, 0, true); // 특정 점을 켬
  // mx.setRow(0, 0, 0, 0xff); // 특정 행을 켬

  // p.setTextAlignment(PA_CENTER); // 출력 위치 중앙
  // p.print("Hello!"); //문자열 출력

  if(p.displayAnimate()){ // 애니메이션 출력 종료를 대기

    if(s < sizeof(texteffect)){
      s++;
    }else{
      s = 0;
    }
    p.displayText(str[s%2], PA_CENTER, 100, 1000,texteffect[s]); // 출력 시 효과 지정
    //p.displayScroll(str[s%2], PA_CENTER, texteffect[s], 100);
  }
  */
}
