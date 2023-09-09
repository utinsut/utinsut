#define INPUT_1 35 จาก ESP32 
//#define INPUT_2 34
//#define INPUT_3 36
//#define INPUT_4 39

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);     
}
void loop() {
  float moisture_percentage1;
  int sensor_analog1;
  sensor_analog1 = analogRead(INPUT_1);
  Serial.print("Law Soil data 1:");
  Serial.println(sensor_analog1);
  moisture_percentage1 = (100 - ((sensor_analog1 / 4095.00) * 100));

  Serial.print("Moisture Percentage 1= ");
  Serial.print(moisture_percentage1); //คำสั่งให้พิมพ์แสดงผล
  Serial.print("%\n\n");//คำสั่งให้พิมพ์แสดงผล
  delay(1000);// รีเลย์การแสดงผลแต่ละค่า
}