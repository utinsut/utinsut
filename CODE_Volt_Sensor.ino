#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
//LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 20 chars and 4 line display


const int sensor = A1;
void setup() {
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.setCursor(0, 3);  //setCursor คอมลัมม์ 4, แถวสี่
  lcd.print("Voltmeter =   ");

  pinMode(sensor, INPUT);
  Serial.begin(9600);
}
void loop() {
  double val = mapf(analogRead(A1), 0, 1030, 0, 25);
  lcd.setCursor(12, 3);
  Serial.print("Voltmeter = ");
  Serial.print(val);
  Serial.println(" Volt");
  lcd.print(val);
  lcd.setCursor(17, 3);
  lcd.print("V.");
  lcd.print("    ");
  delay(2000);
}
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}