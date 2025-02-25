// Khai báo chân LED
const int redLed = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int whiteLed = 5;
const int irSensorPin = 9;
const int resetButtonPin = 6;
enum TrafficLightState { RED, YELLOW, GREEN };
TrafficLightState currentState = GREEN;
unsigned long previousMillis = 0;
const long intervalRed = 7500;    // Thời gian đèn đỏ
const long intervalYellow = 2500; // Thời gian đèn vàng
const long intervalGreen = 5000;  // Thời gian đèn xanh
bool resetFlag = false;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(irSensorPin, INPUT);
  pinMode(resetButtonPin, INPUT_PULLUP);
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();
  int irValue = digitalRead(irSensorPin);
  int buttonState = digitalRead(resetButtonPin);
  if (buttonState == LOW) {
    resetToGreen();
    resetFlag = true; 
    delay(200); 
    while (digitalRead(resetButtonPin) == LOW); 
  }
  if (resetFlag) {
    resetFlag = false; 
    return;
  }
  switch (currentState) {
    case GREEN:
      if (currentMillis - previousMillis >= intervalGreen) {
        previousMillis = currentMillis;
        currentState = YELLOW; 
        digitalWrite(greenLed, LOW);
        digitalWrite(yellowLed, HIGH);
      }
      break;
    case YELLOW:
      if (currentMillis - previousMillis >= intervalYellow) {
        previousMillis = currentMillis;
        currentState = RED; 
        digitalWrite(yellowLed, LOW);
        digitalWrite(redLed, HIGH);
      }
      break;
    case RED:
      if (currentMillis - previousMillis >= intervalRed) {
        previousMillis = currentMillis;
        currentState = GREEN; 
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
      }
      if (irValue == LOW) { 
        chup();
      }
      break;
  }
}
void chup() {
  digitalWrite(whiteLed, HIGH);
  delay(100);
  digitalWrite(whiteLed, LOW);
  digitalWrite(10,HIGH);//gửi tín hiệu đến rasberrypi
  digitalWrite(11,HIGH);
}

void resetToGreen() {
  currentState = GREEN; 
  digitalWrite(redLed, LOW); 
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH); 
  previousMillis = millis(); 
  Serial.println("ve xanh");
}
