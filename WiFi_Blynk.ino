#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6AjPxdfea" //นำมาจาก Device Blynk 
#define BLYNK_TEMPLATE_NAME "MySmartFarm" //นำมาจาก Device Blynk 
#define BLYNK_AUTH_TOKEN "MQbNEUYlrD-t_wauSHMthTpSEgPYLmCk" //นำมาจาก Device Blynk 

#include <BlynkSimpleEsp32.h>

void setup()
{
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, "UTIN", "UT00816701279");
}

void loop()
{
  Blynk.run();
}