#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Initialize the LCD with the I2C address

const int moistureSensorPin = A0; // Analog pin for soil moisture sensor
const int relayPin = 7;           // Digital pin for relay control

void setup() {
  //lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight

  pinMode(relayPin, OUTPUT);       // Set the relay pin as an output
  digitalWrite(relayPin, LOW);    // Ensure the relay is initially off
}

void loop() {
  // Read the soil moisture level from the sensor
  int moistureLevel = analogRead(moistureSensorPin);
  
  // Convert the analog value to a percentage (0-100%)
  int moisturePercentage = map(moistureLevel, 0, 1023, 0, 100);

  // Display moisture level on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture  :");
  lcd.setCursor(13, 0);
  lcd.print(moisturePercentage);
  lcd.print("%");

  // Check moisture level and control the relay
  if (moisturePercentage < 60) {
    digitalWrite(relayPin, LOW); // Turn the relay on
    lcd.setCursor(0, 1);
    lcd.print("Relay     : OFF ");

  } else if (moisturePercentage >= 75) {
    digitalWrite(relayPin, HIGH);  // Turn the relay off
    lcd.setCursor(0, 1);
    lcd.print("Relay     :  ON");
  }
  lcd.setCursor(2, 3);
  lcd.print("Smart Farm By IOT");

  delay(1000); // Delay for 1 second before taking the next reading
}
