#define TRIG_PIN 10
#define ECHO_PIN 11

// LED pins
int leds[] = {3, 5, 6, 9};

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }
}

void warningYellow() {
  Serial.println("Warning: water level within 30 cm!");
}

void warningRed() {
  Serial.println("Warning: water level within 20 cm!");
}

void defaultMessage() {
  Serial.println("Water at acceptable levels.");
}

void loop() {
  long duration;
  int distance;

  // Send ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // convert to cm
  // LED turn on code
  int ledOnIndex = -1;

  if (distance > 0 && distance < 20) { // red
    ledOnIndex = 3;
    warningRed();
  } else if (distance < 30) { // yellow
    ledOnIndex = 2;
    warningYellow();
  } else if (distance < 50) { // green
    ledOnIndex = 1;
    defaultMessage();
  } else { // blue
    ledOnIndex = 0;
    defaultMessage();
  }

  // adjust LED values based on which one should be on/off
  for (int i = 0; i < 4; i++) {
    if (i==ledOnIndex) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }

  delay(100);
}