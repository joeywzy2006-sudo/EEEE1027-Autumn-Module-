const int enA = 11;
const int in1 = 13;
const int in2 = 12;
const int in3 = 2;
const int in4 = 1;
const int enB = 3;

// --- Initialize ultrasonic sensor ---
#define trig A4 //analog input 1
#define echo A5 //analog input 2
float duration = 0;
float distance = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
}

void loop() {
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  duration = pulseIn(echo,HIGH);
  distance = (float)((duration *0.034) / 2);

  forward();
  if (distance <= 20){
    stop();
    delay(100);
    backward();
    delay(20);
    turnRight();
    delay(700);
  }
}

// ============================
// Move Forward Functions
// ============================
void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 110);
  analogWrite(enB, 110);
}

// ============================
// Move backward Functions
// ============================
void backward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 110);
  analogWrite(enB, 110);
}

// ============================
// Stop Functions
// ============================
void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

// ============================
// Turn Right Functions
// ============================
void turnLeft(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 130);
  analogWrite(enB, 130);
}

// ============================
// Turn Left Functions
// ============================
void turnRight(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 130);
  analogWrite(enB, 130);
}

