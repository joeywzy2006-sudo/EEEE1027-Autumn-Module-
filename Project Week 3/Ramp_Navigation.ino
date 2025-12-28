#include <LiquidCrystal.h>
const int enA = 11;
const int in1 = 13;
const int in2 = 12;
const int in3 = 2;
const int in4 = 1;
const int enB = 3;

// --- Initialize lcd ---
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

// --- Initialize MPU6050 (gyro) --- 
#include <Wire.h>
#include <MPU6050_light.h>
MPU6050 mpu(Wire);
unsigned long timer = 0;
float angle_y;
float angle_x;
float angle_max;

int climb_count = 0; // climb counter

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  lcd.begin(16, 2); 
  lcd.setCursor(0, 0);
  lcd.print("pitch: 00.00");
  lcd.setCursor(0, 1);
  lcd.print("yaw: 00.00");

  Wire.begin();
	mpu.begin();
  mpu.calcOffsets(true, true);
	mpu.setFilterGyroCoef(1.0);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // --- Angle data ---
  mpu.update();
	if ((millis() - timer) > 100) 
	{
		timer = millis();
		angle_y = mpu.getAngleY();
    angle_x = mpu.getAngleX();
		delay(100);
	}
  forward();

  // --- Climb algorithm ---
  if (mpu.getAngleY() > 5 && climb_count == 0)
  {
    climb_count = 1;
  }

  if(mpu.getAngleY() > angle_max)
  {
    angle_max = mpu.getAngleY();
  }

  if (mpu.getAngleY() < 2 && climb_count == 1)
  {
    delay(50);
    stop();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("pitch: ");
    lcd.setCursor(7, 0);
    lcd.print(angle_max);
    delay(4000);
    turn360_2();
    climb_count = 2;
  }

  if (mpu.getAngleY() < 2 && climb_count == 2)
  {
    forward();
    delay(1000);
    stop();
    while(1)
    {}
  }

  // --- LCD output ---
  lcd.setCursor(7, 0); 
  lcd.print(angle_y);
  lcd.setCursor(5, 1);
  lcd.print(angle_x);
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

  analogWrite(enA, 105);
  analogWrite(enB, 105);
}

// ============================
// Turn Left Functions
// ============================
void turnRight(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enA, 105);
  analogWrite(enB, 105);
}

// ============================
// Turn 360 Functions
// ============================
void turn360_2() {

  mpu.update();
  unsigned long previous_time = millis();
  float total_turned = 0;
  turnLeft(); 

  while (total_turned < 360) {
    mpu.update();
    unsigned long current_time = millis();
    float dt = (current_time - previous_time) / 1000.0;
    previous_time = current_time;

    mpu.update();
    float rotation_speed = mpu.getGyroX();

    float angleX = abs(rotation_speed * dt);

    total_turned += angleX;
    lcd.setCursor(0, 1);
    lcd.print("yaw: ");
    lcd.setCursor(5, 1);
    lcd.print(total_turned);
  }

  stop();
  delay(1000);
}