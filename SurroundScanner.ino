//depth

#define PIEZO_PIN 9
const int trigger = 6;
const int echo = 7;

float previous_distance = 0.0;
const float change_threshold = 10.0; // Inches — adjust as needed

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop() {
  float current_distance = getDistance(trigger, echo);

  if (current_distance > 2 && current_distance < 100) { // Valid range
    float depth_change = abs(current_distance - previous_distance);

    if (depth_change > change_threshold) {
      tone(PIEZO_PIN, 475);
      delay(200);
      noTone(PIEZO_PIN);
      delay(100); // Small cooldown to avoid repeated buzzing
    }

    previous_distance = current_distance; // Update for next loop
  }

  Serial.print("Depth Distance: ");
  Serial.print(current_distance);
  Serial.println(" in");

  delay(50);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 38000); // Timeout for no object
  return duration * 0.0135; // Convert to inches
}

//distance

#define PIEZO_PIN 9
const int trigger = 6;
const int echo = 7;

float inch_maxthreshold = 60;
float inch_secondmax = 50;
float inch_medium = 40;
float inch_secondmin = 30;
float inch_min = 20;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
}

void loop() {
  float dist_inches = getDistance(trigger, echo);

  if (dist_inches > 2 && dist_inches < inch_min) {
    tone(PIEZO_PIN, 1800);
    delay(50);
    noTone(PIEZO_PIN);
  } else if (dist_inches >= inch_min && dist_inches < inch_secondmin) {
    tone(PIEZO_PIN, 1675);
    delay(125);
    noTone(PIEZO_PIN);
  } else if (dist_inches >= inch_secondmin && dist_inches < inch_medium) {
    tone(PIEZO_PIN, 1550);
    delay(150);
    noTone(PIEZO_PIN);
  } else if (dist_inches >= inch_medium && dist_inches < inch_secondmax) {
    tone(PIEZO_PIN, 1475);
    delay(175);
    noTone(PIEZO_PIN);
  } else if (dist_inches >= inch_secondmax && dist_inches < inch_maxthreshold) {
    tone(PIEZO_PIN, 1400);
    delay(225);
    noTone(PIEZO_PIN);
  }

  Serial.print("Forward Distance: ");
  Serial.print(dist_inches);
  Serial.println(" in");

  delay(50);
}

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 38000);
  return duration * 0.0135;
}
