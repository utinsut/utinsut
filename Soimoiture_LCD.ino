#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
//LiquidCrystal_I2C lcd(0x27, 16, 2);
const int sensor_pin = A0; /* Soil moisture sensor O/P pin */

void setup() {
  Serial.begin(9600); /* Define baud rate for serial communication */
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = (100 - ((sensor_analog / 1023.00) * 100));
  Serial.print("Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");

  lcd.setCursor(0, 0);
  lcd.print("Soilmoi =  ");
  lcd.setCursor(11, 0);
  lcd.print(moisture_percentage);
  //lcd.setCursor(16, 0);
  //lcd.print(" ");
  lcd.setCursor(16, 0);
  lcd.print("%\n\n");
  lcd.setCursor(17, 0);
  lcd.print(" ");
  lcd.setCursor(18, 0);
  lcd.print(" ");

  delay(2000);
}