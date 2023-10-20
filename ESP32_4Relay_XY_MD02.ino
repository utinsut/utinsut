/*
Example of using XY-MD02 With ESP32 and Relay 4 Ch
กำหนดเงื่อนไขถ้าหากอุณหภูมิมากกว่าหรือเท่ากับ35 องศาเซลเซียส ให้ขา 32 ส่งสัญญาณออกไปเป็น HIGH เป็นผลให้รีเลย์ 1 ทำงาน 
================================================================

*/

#include <ModbusMaster.h>
#include <SimpleTimer.h>

#define MAX485_DE 5
#define MAX485_RE_NEG 18

SimpleTimer timer;
ModbusMaster node;

float temp;              //สร้างตัวแปรวัดอุณหภูมิ
float humid;             //สร้างตัวแปรวัดความชื้นในอากาศ
 
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

///////////////////////////////////////////////////////////////////////////////////////////////////
void ReadSensorMD02(){
  
uint8_t result;
 
Serial.println("XY-MD02 Modbus Sensor Reading...");
result = node.readInputRegisters(1, 2);
if (result == node.ku8MBSuccess)
{
Serial.print("Temperature: ");
temp = node.getResponseBuffer(0)/10.0f;
Serial.print(temp);

Serial.print("  Humidity: ");
humid = node.getResponseBuffer(1)/10.0f;
Serial.println(humid);

Serial.println();
 
}  
  } 
////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
pinMode(MAX485_RE_NEG, OUTPUT);
pinMode(MAX485_DE, OUTPUT);
pinMode(32, OUTPUT);       //รีเลย์ตัวแรกต่อเข้าขา 32 ให้กำหนดเป็น output
// Init in receive mode
digitalWrite(MAX485_RE_NEG, 0);
digitalWrite(MAX485_DE, 0);
digitalWrite(32, LOW);     //กำหนดให้ขา 32 แสดงผลเป็น LOW

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

timer.setInterval(5000L, ReadSensorMD02);
 
}
///////////////////////////////////////////////////// 
void loop()
{
timer.run();
if(temp>=35){ digitalWrite(32, HIGH); } //กำหนดให้ Temp>=35 ขา 32 เป็น HIGHT
else{ digitalWrite(32, LOW);} //หากเป็นค่าอื่นนอกจากนี้ให้ขา 32 เป็น LOW
}
/////////////////////////////////////////////////////
