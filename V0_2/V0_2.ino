#define BLYNK_TEMPLATE_ID "TMPLh3CqIuy1"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KUn9tM5yyGWXFyrqVA6eIBROV5GmVLi6"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

//#include "soc/rtc_wdt.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#include "io_define.h"

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Hansama_6668";
char pass[] = "10072000";

BlynkTimer BLTimer;

#include <OneWire.h>
#include <DallasTemperature.h>


// GPIO where the DS18B20 is connected to
const int oneWireBus_0 = 16;   
const int oneWireBus_1 = 17;   
const int oneWireBus_2 = 18;   
const int oneWireBus_3 = 19;   

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire_0(oneWireBus_0);
OneWire oneWire_1(oneWireBus_1);
OneWire oneWire_2(oneWireBus_2);
OneWire oneWire_3(oneWireBus_3);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors_0(&oneWire_0);
DallasTemperature sensors_1(&oneWire_1);
DallasTemperature sensors_2(&oneWire_2);
DallasTemperature sensors_3(&oneWire_3);

float t0, t1, t2, t3;
int   h0, h1, h2, h3;

void myTimerEvent()
{
       h0 = map(analogRead(G33),0,4095,100,0);
       h1 = map(analogRead(G32),0,4095,100,0);
       h2 = map(analogRead(G35),0,4095,100,0);
       h3 = map(analogRead(G34),0,4095,100,0);

       Serial.println();
       if(h0 < 60){digitalWrite(G14, HIGH); Serial.println("pump_0: ON");} //Blynk.virtualWrite(V8,  1);}
       else       {digitalWrite(G14, LOW);  Serial.println("pump_0: OFF");}  //Blynk.virtualWrite(V8,  0);}
       if(h1 < 60){digitalWrite(G27, HIGH); Serial.println("pump_1: ON");} //Blynk.virtualWrite(V9,  1);}
       else       {digitalWrite(G27, LOW);  Serial.println("pump_1: OFF");}  //Blynk.virtualWrite(V9,  0);}
       if(h2 < 60){digitalWrite(G26, HIGH); Serial.println("pump_2: ON");} //Blynk.virtualWrite(V10, 1);}
       else       {digitalWrite(G26, LOW);  Serial.println("pump_2: OFF");}  //Blynk.virtualWrite(V10, 0);}
       if(h3 < 60){digitalWrite(G25, HIGH); Serial.println("pump_3: ON");} //Blynk.virtualWrite(V11, 1);}
       else       {digitalWrite(G25, LOW);  Serial.println("pump_3: OFF");}  //Blynk.virtualWrite(V11, 0);} 

       if(digitalRead(G23) == LOW)
       {
        digitalWrite(G4,  LOW);
        Blynk.virtualWrite(V12, 1);
       }
       else
       {
        digitalWrite(G4,  HIGH);
        Blynk.virtualWrite(V12, 0);
       }
       
        Blynk.virtualWrite(V0, h0);
        Blynk.virtualWrite(V1, h1);
        Blynk.virtualWrite(V2, h2);
        Blynk.virtualWrite(V3, h3);
      
        Blynk.virtualWrite(V4, t0);
        Blynk.virtualWrite(V5, t1);
        Blynk.virtualWrite(V6, t2);
        Blynk.virtualWrite(V7, t3);

  
        Serial.println();
        Serial.print("ADC33: "); Serial.print( h0); Serial.println(" %"); 
        Serial.print("ADC32: "); Serial.print( h1); Serial.println(" %"); 
        Serial.print("ADC35: "); Serial.print( h2); Serial.println(" %"); 
        Serial.print("ADC34: "); Serial.print( h3); Serial.println(" %"); 
        Serial.println();
}

void PIN_INIT()
{ 

  pinMode(G33, INPUT_PULLUP);
  pinMode(G32, INPUT_PULLUP);
  pinMode(G35, INPUT_PULLUP);
  pinMode(G34, INPUT_PULLUP);
  
  pinMode(G16, INPUT_PULLUP);
  pinMode(G17, INPUT_PULLUP);
  pinMode(G18, INPUT_PULLUP);
  pinMode(G19, INPUT_PULLUP);
  
  pinMode(G23, INPUT_PULLUP);
  
  pinMode(G4, OUTPUT);

  pinMode(G14, OUTPUT);
  pinMode(G27, OUTPUT);
  pinMode(G26, OUTPUT);
  pinMode(G25, OUTPUT);

}

void setup(void)
{
  Serial.begin(115200);
  
 //rtc_wdt_protect_off();
  //rtc_wdt_disable();

 
  Serial.println("Booting Sketch...");
  
  Blynk.begin(auth, ssid, pass);

  Serial.println("-> ok");
  
  BLTimer.setInterval(2000L, myTimerEvent);

  PIN_INIT();
  sensors_0.begin();
  sensors_1.begin();
  sensors_2.begin();
  sensors_3.begin();
 
   
}

void loop(void)
{ 
  unsigned long T0 = millis();
  int step = 0;
  
  
  while(1)
  {
    Blynk.run();
    BLTimer.run();

    if((millis() - T0) > 1000)
    {
       T0 = millis();

       if(step == 0) { sensors_0.requestTemperatures(); t0 = sensors_0.getTempCByIndex(0);}
       if(step == 1) { sensors_1.requestTemperatures(); t1 = sensors_1.getTempCByIndex(0);}
       if(step == 2) { sensors_2.requestTemperatures(); t2 = sensors_2.getTempCByIndex(0);}
       if(step == 3) { sensors_3.requestTemperatures(); t3 = sensors_3.getTempCByIndex(0);}

       step++;
       
       if(step == 4)
       {
         step = 0;       
       } 
         
       Serial.println();
       Serial.print("T0: "); Serial.print(t0); Serial.println("ºC");
       Serial.print("T1: "); Serial.print(t1); Serial.println("ºC");
       Serial.print("T2: "); Serial.print(t2); Serial.println("ºC");
       Serial.print("T3: "); Serial.print(t3); Serial.println("ºC");
       Serial.println();

    }

    
  }
}
