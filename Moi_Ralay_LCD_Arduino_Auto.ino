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
  lcd.print("Moisture  :");
  lcd.setCursor(15, 0);
  lcd.print(moisturePercentage);
  lcd.print("%");

  // Check moisture level and control the relay ตรวจสอบนำค่าที่ได้รับไปควบคุมรีเลย์
  if (moisturePercentage < 73) { //ค่าน้อยกว่า 73 หมายถึงมีความชื้นมากหรือเปียก ให้ปิดการทำงานของรีเลย์
    digitalWrite(relayPin, LOW); // Turn the relay off
    lcd.setCursor(1, 1);
    lcd.print("Relay     : OFF ");

  } //else if (moisturePercentage >= 75) { //ค่ามากกว่าหรือเท่ากับ 75 หมายถึงมีความชื้นน้อยหรือดินแห้ง ให้เปิดการทำงานของรีเลย์

    else //หากมีนอกเหนือจากนี้ ให้เปิดการทำงานของรีเลย์
    digitalWrite(relayPin, HIGH);  // Turn the relay on
    lcd.setCursor(2, 1);
    lcd.print("Relay     :  ON");
  }
  lcd.setCursor(2, 3);
  lcd.print("Smart Farm By IOT"); //แถวที่ 4 ให้พิมพ์ข้อความนี้ Smart Farm By IOT

  delay(1000); // Delay for 1 second before taking the next reading หน่วงเวลาไว้ 1 วินาที ก่อนวนลูปไปอ่านคำสั่งต่อไป
}

