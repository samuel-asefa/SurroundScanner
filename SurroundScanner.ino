#define PIEZO_PIN 9  

const int trigger = 6;
const int echo = 7;
float distance;
float dist_inches;

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
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  distance = pulseIn(echo, HIGH, 38000); 
  distance = distance * 0.0135;         
  dist_inches = distance;

  if (dist_inches > 2 && dist_inches < inch_min) {
    tone(PIEZO_PIN, 1725);
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

  Serial.print("Distance: ");
  Serial.print(dist_inches);
  Serial.println(" in");

  delay(50);
}
