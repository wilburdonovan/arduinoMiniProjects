
int ledPin = 8;
int sensePin = 0;
int lightCal;

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  lightCal = analogRead(sensePin)- 50;
  Serial.println(lightCal);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val= analogRead(sensePin);
  Serial.println(val);

  if (val < lightCal) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
  
  
}
