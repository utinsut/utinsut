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
  int moistureLevel = analogRead(moistureSensorPin); //ให้อ่านการวัดค่าเป็นอนาล็อก
  
  // Convert the analog value to a percentage (0-100%)
  int moisturePercentage = map(moistureLevel, 0, 1023, 0, 100); //ทำการแปลงค่า analog เป็นเปอร์เซ็นต์

  // Display moisture level on the LCD กำหนดให้แสดงค่าออกมาทาง LCD
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Moisture   :");
  lcd.setCursor(16, 0);
  lcd.print(moisturePercentage);
  lcd.print("%");
  lcd.setCursor(2, 1);
  lcd.print("Value>= 81 :  ON ");

  // Check moisture level and control the relay
  if (moisturePercentage <= 81) {  //ถ้ามีค่าความชื้น น้อยกว่าหรือเท่ากับ 81 ให้รีเลย์ OFF
    digitalWrite(relayPin, HIGH);  // Turn the relay on
    lcd.setCursor(2, 2);
    lcd.print("Relay 1    :  OFF ");

  }                               //else if (moisturePercentage >= 80) {
  else {                          //ถ้าคำสั่งนอกเหนือจากบรรทัดที่ 32 ก็ให้รีเลย์ทำการ ON หรือรดน้ำต้นไม้
    digitalWrite(relayPin, LOW);  // Turn the relay off
    lcd.setCursor(2, 2);
    lcd.print("Relay 1    :  ON   ");
  }
  lcd.setCursor(5, 3);
  lcd.print("Smart Farm");
  lcd.setCursor(21, 3);
  lcd.print("");

  delay(2000);  // Delay for 1 second before taking the next reading
}
