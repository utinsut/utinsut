/*
Example of using XY-MD02 Modbus Sensor With ESP32 and LCD LiquidCrystal_I2C lcd(0x27, 20, 4)

================================================================
*/

#include <ModbusMaster.h>
#include <SimpleTimer.h>

#define MAX485_DE 5
#define MAX485_RE_NEG 18

//==========LCD I2C LCD2004===========//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      //https://github.com/bugkuska/esp32/raw/main/basic/lcd/LiquidCrystal_i2c.zip
LiquidCrystal_I2C lcd(0x27, 20, 4);

SimpleTimer timer;  
ModbusMaster node;

float temp;   //สร้างตัวแปรวัดอุณหภูมิ
float humid;  //สร้างตัวแปรวัดความชื้นในอากาศ

void preTransmission() 
{
  digitalWrite(MAX485_RE_NEG, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission() 
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

///////////////////////////////////////////////////////////////////
void ReadSensorMD02(){

  uint8_t result;

  Serial.println("XY-MD02 Modbus Sensor Reading..."); //ให้แสดงผลออกทาง Serial.print แล้วให้ขึ้นบรรทัดใหม่
  result = node.readInputRegisters(1, 2);
  if (result == node.ku8MBSuccess) 
  {
    Serial.print("Temperature: ");  //ให้แสดงผลตัวอักษรออกทาง Serial.print 
    temp = node.getResponseBuffer(0) / 10.0f;
    Serial.print(temp);      //ให้แสดงค่าตัวแปรTemperature ออกทาง Serial.print 
    Serial.print(F("°C"));  // หน่วยของอุณหภูมิ

    Serial.print("  Humidity: ");  //ให้แสดงผลตัวอักษรออกทาง Serial.print 
    humid = node.getResponseBuffer(1) / 10.0f;
    Serial.print(humid);           //ให้แสดงค่าตัวแปร Humidity ออกทาง Serial.print 
    Serial.println(F("%"));     // หน่วยของ Humidity 

//ปริ้นท์ค่าอุณหภูมิ แสดงบน LCD แถวแรก
    lcd.setCursor(1, 0);
    lcd.print("TEMP =  "); // ตัวอักษรที่แสดงบนจอ LCD
    lcd.print(temp);       //ค่าตัวแปร temp ที่จะแสดงผลออกทางจอ LCD
    lcd.setCursor(16, 0);
    lcd.print("C ");        // หน่วยของอุณหภูมิ
  
//ปริ้นท์ค่าความชื้นในอากาศ แสดงบน LCD แถวสอง
    lcd.setCursor(1, 1);
    lcd.print("HUMI =  ");   // ตัวอักษรที่แสดงบนจอ LCD
    lcd.print(humid);       //ค่าตัวแปร humid ที่จะแสดงผลออกทางจอ LCD
    lcd.setCursor(16, 1);
    lcd.print("%");         // หน่วยของความชื้นในอากาศ             
  
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() 
{

  lcd.begin();      // initialize LCD2004
  lcd.backlight();  // turn on LCD backlight

  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  //pinMode(32, OUTPUT);       //รีเลย์ตัวแรกต่อเข้าขา 32 ให้กำหนดเป็น output
  //Init in receive mode
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
  //digitalWrite(32, LOW);     //กำหนดให้ขา 32 แสดงผลเป็น LOW

  Serial.println("start init serial 0");

  Serial.begin(9600);
  Serial2.begin(9600);

  while (!Serial) {
    Serial.println("loop for init serial 0");
  }

  while (!Serial2) {
    Serial.println("loop for init serial2 For modbus");
  }

  node.begin(1, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  timer.setInterval(5000L, ReadSensorMD02);    //ให้อ่านค่า MD02 ทุกๆ 5 วินาที
}
/////////////////////////////////////////////////////
void loop() {
  timer.run();
  //if(temp>=35){ digitalWrite(32, HIGH); } //กำหนดให้ Temp>=35 ขา 32 เป็น HIGHT
  //else{ digitalWrite(32, LOW);}           //หากเป็นค่าอื่นนอกจากนี้ให้ขา 32 เป็น LOW
}
/////////////////////////////////////////////////////
