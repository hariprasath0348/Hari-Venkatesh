#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <MPU6050.h>

 

// LCD

 

LiquidCrystal_I2C lcd(0x27, 16, 2);

 

void setup() {

  Wire.begin(21,22);

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0,0);

  lcd.print("LCD OK");

  lcd.setCursor(0,1);

  lcd.print("ESP32 READY");

}

 

void loop() {}

 

// MPU6050

MPU6050 mpu;

 

// Pins

int soilPin = 35;

int vibPin  = 27;

int buzzer  = 26;

 

// Thresholds (can tune)

int soilThreshold = 2000;   // lower = more wet

int vibThreshold  = 1;      // digital output

 

void setup() {

  Serial.begin(115200);

 

  pinMode(vibPin, INPUT);

  pinMode(26, OUTPUT);

  digitalWrite(26, LOW);

 

  // LCD init

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0,0);

  lcd.print("Landslide Sys");

  lcd.setCursor(0,1);

  lcd.print("Initializing");

  delay(2000);

  lcd.clear();

 

  // MPU init

  Wire.begin(21, 22);

  mpu.initialize();

 

  if (mpu.testConnection()) {

    Serial.println("MPU6050 Connected");

  } else {

    Serial.println("MPU6050 NOT Connected");

    lcd.print("MPU Error");

  }

 

  delay(1000);

}

 

void loop() {

  // Read sensors

  int soilValue = analogRead(soilPin);

  int vibValue  = digitalRead(vibPin);

 

  int16_t ax, ay, az;

  mpu.getAcceleration(&ax, &ay, &az);

 

  // Convert accel to tilt indicator (simple)

  int tilt = abs(ax) + abs(ay);

 

  // Serial output (for judges)

  Serial.print("Soil: ");

  Serial.print(soilValue);

  Serial.print(" | Vib: ");

  Serial.print(vibValue);

  Serial.print(" | Tilt: ");

  Serial.println(tilt);

 

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <MPU6050.h>

 

/* -------- LCD OBJECT (GLOBAL) -------- */

LiquidCrystal_I2C lcd(0x27, 16, 2);

 

/* -------- MPU OBJECT -------- */

MPU6050 mpu;

 

/* -------- PINS -------- */

int soilPin = 35;

int vibPin  = 27;

int buzzer  = 26;

 

/* -------- THRESHOLDS -------- */

int soilThreshold = 2200;

 

void setup() {

  Serial.begin(115200);

 

  pinMode(vibPin, INPUT);

  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

 

  /* -------- I2C INIT (ESP32) -------- */

  Wire.begin(21, 22);

 

  /* -------- LCD INIT -------- */

  lcd.init();

  lcd.backlight();

  lcd.setCursor(0, 0);

  lcd.print("Landslide Sys");

  lcd.setCursor(0, 1);

  lcd.print("Starting...");

  delay(2000);

  lcd.clear();

 

  /* -------- MPU INIT -------- */

  mpu.initialize();

 

  if (mpu.testConnection()) {

    Serial.println("MPU OK");

    lcd.print("MPU OK");

  } else {

    Serial.println("MPU FAIL");

    lcd.print("MPU ERROR");

  }

 

  delay(1500);

  lcd.clear();

}

 

void loop() {

  int soilValue = analogRead(soilPin);

  int vibValue  = digitalRead(vibPin);

 

  int16_t ax, ay, az;

  mpu.getAcceleration(&ax, &ay, &az);

 

  int tilt = abs(ax) + abs(ay);

 

  /* -------- SERIAL MONITOR -------- */

  Serial.print("Soil: ");

  Serial.print(soilValue);

  Serial.print(" | Vib: ");

  Serial.print(vibValue);

  Serial.print(" | Tilt: ");

  Serial.println(tilt);

 

  /* -------- LCD DISPLAY -------- */

  lcd.setCursor(0, 0);

  lcd.print("Soil:");

  lcd.print(soilValue);

  lcd.print("   ");

 

  lcd.setCursor(0, 1);

 

  if (soilValue < soilThreshold || vibValue == 1 || tilt > 30000) {

    lcd.print("DANGER !!!     ");

    digitalWrite(buzzer, HIGH);

  } else {

    lcd.print("Status: SAFE   ");

    digitalWrite(buzzer, LOW);

  }

 

  delay(1000);

}

 

  // Logic

  if (soilValue < soilThreshold || vibValue == 1 || tilt > 30000) {

    lcd.print("DANGER !!!     ");

    digitalWrite(26, HIGH);

  } else {

    lcd.print("Status: SAFE ");

    digitalWrite(26, LOW);

  }

 

  delay(1000);

}