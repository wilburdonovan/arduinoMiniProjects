#include <LiquidCrystal.h>

int usTrigPin = 10;
int usEchoPin = 11;

// initialize library with numbers of interface pins
LiquidCrystal lcd(12,9,5,4,3,2);


void setup() {
  // put your setup code here, to run once:
  pinMode(usTrigPin, OUTPUT);
  pinMode(usEchoPin, INPUT);
  Serial.begin(9600);

  // set up columns and rows for LCD
  lcd.begin(16,2);

  lcd.print("helloworld");
}

void loop() {
  // put your main code here, to run repeatedly:
  float duration;
  float distance;

  digitalWrite(usTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(usTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(usTrigPin, LOW);

  duration= pulseIn(usEchoPin, HIGH);
  distance= (duration/2) * 0.0334;

  lcd.clear();
  if (distance >= 400 || distance <= 2) {
    Serial.print("Distance = ");
    Serial.println("OUt of range");
    Serial.println(distance);
    Serial.println(duration);
    lcd.print("Out of range");

  } else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println ("cm");
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.println("cm");
    delay(500);
  }
  delay(500);
}
