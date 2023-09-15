#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TridentTD_LineNotify.h>


#define Relay1 D1
#define Relay2 D2
#define Relay3 D3
#define Relay4 D4

#define LINE_TOKEN "AS5a5nCsKi7jkCmAjrBa4gpdmRtAqCcizVDgv5UnwvD"
char auth[] = "seoKTL5I1SwHUA4aOLShmjtsnjruzXM6";   
char ssid[] = "PMS"; 
char pass[] = "12345678";     

WidgetLED LED_1(V2);
WidgetLED LED_2(V4);
WidgetLED LED_3(V6);
WidgetLED LED_4(V8);


void setup()
{
  Serial.begin(9600);
  //OUTPUT
  pinMode(Relay1,OUTPUT); 
  pinMode(Relay2,OUTPUT); 
  pinMode(Relay3,OUTPUT); 
  pinMode(Relay4,OUTPUT); 

  digitalWrite(Relay1, LOW); 
  digitalWrite(Relay2, LOW); 
  digitalWrite(Relay3, LOW); 
  digitalWrite(Relay4, LOW); 
  Blynk.begin(auth, ssid, pass);
  LINE.setToken(LINE_TOKEN);
}
void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay1, HIGH); 
        LED_1.on();
        LINE.notify("รีเลย์ 1 ทำงาน"); 
    } else {
        digitalWrite(Relay1, LOW); 
        LED_1.off();
        LINE.notify("รีเลย์ 1 หยุดทำงาน"); 
    }
}
BLYNK_WRITE(V3){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay2, HIGH); 
        LED_2.on();
         LINE.notify("รีเลย์ 2 ทำงาน"); 
    } else {
        digitalWrite(Relay2, LOW); 
        LED_2.off();
         LINE.notify("รีเลย์ 2 หยุดทำงาน"); 
    }
}
BLYNK_WRITE(V5){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay3, HIGH); 
        LED_3.on();
         LINE.notify("รีเลย์ 3 ทำงาน"); 
    } else {
        digitalWrite(Relay3, LOW); 
        LED_3.off();
         LINE.notify("รีเลย์ 3 หยุดทำงาน"); 
    }
}
BLYNK_WRITE(V7){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay4, HIGH); 
        LED_4.on();
        LINE.notify("รีเลย์ 4 ทำงาน"); 
    } else {
        digitalWrite(Relay4, LOW); 
        LED_4.off();
        LINE.notify("รีเลย์ 4 หยุดทำงาน"); 

    }
}
