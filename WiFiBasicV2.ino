/*
  การเชื่อมต่อ WiFi ด้วย ESP32 หากเชื่อมต่อไม่ได้ ไฟในบอร์ดจะกระพริบถี่ๆ
  หากเชื่อมต่อได้ ไฟในบอร์ดจะกระพริบช้าๆ 
*/

#include <WiFi.h>
#define led 2            //ESP32 LED_BUILTIN 

const char* ssid = "UTIN"; //ชื่อของไวไฟ
const char* password = "UT00816701279"; //รหัสผ่านของไวไฟ

bool WiFiConnect = false;

void setup() {
  Serial.begin(115200); 
  
  pinMode(led, OUTPUT);
  
}

void loop() {

  /* เชื่อมต่อ WiFi เมื่อสถานะ WiFi Disconnected */
  static unsigned long WiFiReconnectTimer;
  if ((WiFi.status() != WL_CONNECTED)) {  
    if ((millis() - WiFiReconnectTimer) > 5000) {
      WiFiReconnectTimer = millis();
      WiFi.begin(ssid, password);
      WiFiConnect = false;
      Serial.print("Connecting to "); Serial.println(ssid);      
    }
  }else {
    WiFiConnect = true;
  } // จบ  WiFi Connect
  

  if (WiFiConnect){
    /* LED กระพริบ */
    static unsigned long interval = millis();
    if (interval < millis()) {
      static int ledstat = 1;
      interval = millis() + 1000;
      ledstat = !ledstat;
      digitalWrite(led, ledstat);                                
    }
  }
  else {
    static unsigned long interval = millis();
    if (interval < millis()) {
      static int ledstat = 1;
      interval = millis() + 100;
      ledstat = !ledstat;
      digitalWrite(led, ledstat);                                
    }
  } // จบโค้ดการเชื่อต่อไวไฟ LED กระพริบ
}
