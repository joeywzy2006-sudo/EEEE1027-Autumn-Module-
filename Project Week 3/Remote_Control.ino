#include <SoftwareSerial.h>

const int enA = 11;
const int in1 = 13;
const int in2 = 12;
const int in3 = 2;
const int in4 = 1;
const int enB = 3;

// Create software serial object to communicate with HC-05
SoftwareSerial mySerial(A4, A5); //HC-05 Tx & Rx is connected to Arduino

void setup() {
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(enB, OUTPUT);

    mySerial.begin(9600); 
}

void loop() {
    char command = mySerial.read(); // Read command from serial

    switch(command) {
        case 'F':   // Move forward
            forward();
            break;

        case 'B':   // Move backward
            backward();
            break;

        case 'R':   // Turn right
            turnRight();
            break;

        case 'L':   // Turn left
            turnLeft();
            break;

        case 'S':   // Stop all motors
            stop();
            break;
        
        case 'G':   // Forward left
            forwardLeft();
            break;

        case 'H':   // Forward right
            forwardRight();
            break;

        case 'I':   // Backward left
            backwardLeft();
            break;

        case 'J':   // Backward right
            backwardRight();
            break;
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

  analogWrite(enA, 250);
  analogWrite(enB, 250);
}

// ============================
// Move Backward Functions
// ============================
void backward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 250);
  analogWrite(enB, 250);
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

// ============================
// Forward Left Functions
// ============================
void forwardLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 50);
  analogWrite(enB, 250);
}

// ============================
// Forward Left Functions
// ============================
void forwardRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  analogWrite(enA, 250);
  analogWrite(enB, 50);
}

// ============================
// Backward Left Functions
// ============================
void backwardLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 50);
  analogWrite(enB, 250);
}

// ============================
// Backward Left Functions
// ============================
void backwardRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 250);
  analogWrite(enB, 50);
}