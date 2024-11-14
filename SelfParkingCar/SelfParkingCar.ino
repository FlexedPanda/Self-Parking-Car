// Front Sensor Pins
#define trigPin1 13
#define echoPin1 12

// Right Sensor Pins
#define trigPin2 11
#define echoPin2 10

// Back Sensor Pins
#define trigPin3 2
#define echoPin3 6

// Left Motor Pins
#define enA 9
#define in1 8
#define in2 7

// Right Motor Pins
#define enB 3
#define in3 5
#define in4 4

// Parking Space Check
#define space 30

// Main Setup Function
void setup() {
  // Sensor Pin Setup
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Motor Pin Setup
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Serial Monitor Setup
  Serial.begin(9600);
}

// Main Loop Function
void loop() {
  // Front Sensor Reading
  int front = dist(trigPin1, echoPin1);
  Serial.print("front distance: ");
  Serial.println(front);

  // Right Sensor Reading
  int right = dist(trigPin2, echoPin2);
  Serial.print("right distance: ");
  Serial.println(right);

  // Back Sensor Reading
  int back = dist(trigPin3, echoPin3);
  Serial.print("back distance: ");
  Serial.println(back);

  // Parking Decision Making
  delay(1000);
  if (right > space) {
    park();
  } else if (front > 10 && back > 10) {
    move();
  } else {
    stop();
  }
}

// Distance Measure Function
int dist(int trigPin, int echoPin) {
  // Ultrasonic Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measuring Distance
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration / 2 / 29.1;
  return distance;
}

// Stop Function
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// Move Function
void move() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, 120);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 120);
}

// Park Function
void park() {
  // Stopping Ahead of the Space 
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(1000);

  // Moving Back to the Space
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 150);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 150);

  delay(1000);

  // Stopping infront of the Space
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(1000);

  // Turning Left along the Space
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 110);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 110);

  delay(1000);

  // Parking inside the Space
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, 150);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 150);

  delay(1000);

  // Stopping inside the Space
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  exit(0);
}
