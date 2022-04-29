const int BLED = 9;
const int GLED = 10;
const int RLED = 11;
const int BUTTON = 2;

boolean lastButton = HIGH;
boolean currentButton = LOW;
int ledMode = 0;

int LED = 8;
int BTN = 2;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

}

void setMode(int mode) {
  if (mode == 1) { // RED LED ON
    digitalWrite(RLED, HIGH);
    digitalWrite(BLED, LOW);
    digitalWrite(GLED, LOW);
  } else if (mode == 2) { // BLUE LED ON
    digitalWrite(RLED, LOW);
    digitalWrite(BLED, HIGH);
    digitalWrite(GLED, LOW);
  } else if (mode == 3) { // GREEN LED ON
    digitalWrite(RLED, LOW);
    digitalWrite(BLED, LOW);
    digitalWrite(GLED, HIGH);
  } else { // ALL LED OFF
    digitalWrite(RLED, LOW);
    digitalWrite(BLED, LOW);
    digitalWrite(GLED, LOW);
  }
}

void loop() {

  currentButton = digitalRead(BTN);

  if (lastButton == HIGH && currentButton == LOW) {
    ledMode++;
  }
  lastButton = currentButton;
  delay(50);
  Serial.println(ledMode);
  if (ledMode == 4 ) ledMode = 0;
  setMode(ledMode);
}
