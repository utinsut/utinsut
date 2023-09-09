#include <Wire.h> // กำหนด library ของ LCD
#include <LiquidCrystal_I2C.h>  //https://github.com/bugkuska/esp32/raw/main/basic/lcd/LiquidCrystal_i2c.zip
LiquidCrystal_I2C lcd(0x27, 20, 4); //LCD ขนาด 4 แถว 20 คอลัมม์
const int sensor = 34; //ประกาศกำหนดรับสัญญาณ sensor ขา 34
//dht11,dht22 
#include <DHT.h>  //https://github.com/adafruit/DHT-sensor-library
#define DHTPIN 18 //ประกาศกำหนดรับสัญญาณ DHT PIN 18
//#define DHTTYPE DHT11
#define DHTTYPE DHT22 //กำหนดประเภทของ DHT 22
DHT dht(DHTPIN, DHTTYPE); //กำหนด ขาและชนิดของ DHT

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(sensor, INPUT);
  //Serial.begin(9600);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // or dht.readTemperature(true) for Fahrenheit

  Serial.print("Temperature:"); //แสดงค่าวัดอุณหภูมิ
  Serial.print(t); //ให้นำค่า t มาแสดงผลตัวเลข
  Serial.println(" C "); //หลังจากแสดงผลแล้วให้ขึ้นบรรทัดใหม่
  Serial.print("Humidity:"); //แสดงค่าวัดความชื้นในอากาศ
  Serial.print(h); //ให้นำค่า h มาแสดงผลตัวเลข
  Serial.println(" % "); //หลังจากแสดงผลแล้วให้ขึ้นบรรทัดใหม่
  //delay(1000);
  double val = mapf(analogRead(34), 0, 5605, 0, 25); 
  Serial.print("Voltmeter = ");
  Serial.print(val);
  Serial.println(" Volt"); //หลังจากแสดงผลแล้วให้ขึ้นบรรทัดใหม่
  delay(2000);

  //LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("TEMP =  ");
  lcd.print(t);
  lcd.print("  C ");

  lcd.setCursor(1, 1);
  lcd.print("HUMI =  ");
  lcd.print(h);
  lcd.print("  % ");

  lcd.setCursor(1, 3);
  lcd.print("Volt =  ");
  lcd.print(val);
  lcd.setCursor(16, 3);
  lcd.print("V.");
}
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
  return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}