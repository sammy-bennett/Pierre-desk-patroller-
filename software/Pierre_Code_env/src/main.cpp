#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <memory>
#include <Face.h> //esp32_eyes

#include <pin_definition.h>


bool wifi_connected;


std::unique_ptr<Face> screen;


void setup() {
  Serial.begin(115200);
  
//  highlevel set up for I2C  //
  while(!Wire.begin(I2C_SDA,I2C_SCL)){
    Serial.println("Cannot start I2C communication.. trying again....");
    delay(200);
  }
  Serial.println("I2C initiated!");
  
  //  wifi set up //
  WiFi.mode(WIFI_STA); //standard mode, like a pc (optininal)
  Serial.println("connecting to wifi...");
  delay(500);
  
  unsigned long cur_time, start_time = millis();
  WiFi.begin(SSID,wifi_pw);
  //wait 5 seconds but only id its not connected
  while(WiFi.status() != WL_CONNECTED){
    cur_time = millis();
    if(cur_time - start_time >= 5000){ //5seconds 
      break;
    }
    delay(100);
  }

  wifi_connected = (WiFi.status() == WL_CONNECTED);
  if(wifi_connected){
    Serial.println("WIFI established!");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());}
  else 
    Serial.println("WIFI NOT established!.. timeout reached");

  //  Screen stuff!!  //
  screen = std::unique_ptr<Face>(new Face(128,64,40));
  screen->Behavior.SetEmotion(eEmotions::Normal, 1.0);
  screen->Behavior.SetEmotion(eEmotions::Glee, 0.8);
  screen->Behavior.SetEmotion(eEmotions::Surprised, 0.6);
  screen->Behavior.SetEmotion(eEmotions::Focused, 0.5);
  screen->Behavior.SetEmotion(eEmotions::Angry, 0.3);
  screen->Behavior.SetEmotion(eEmotions::Sad, 0.3);
  screen->Behavior.SetEmotion(eEmotions::Sleepy, 0.4);
  screen->Behavior.SetEmotion(eEmotions::Squint, 0.2);
  screen->Behavior.SetEmotion(eEmotions::Skeptic, 0.6);
  //timings
  screen->RandomBehavior = true;
  screen->Behavior.Timer.SetIntervalMillis(2500);
  screen->Blink.Timer.SetIntervalMillis(4000);
  screen->Look.Timer.SetIntervalMillis(2000);
}

void loop() {
  screen->Update();
  delay(20); //~50fps
}
