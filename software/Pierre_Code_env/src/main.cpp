#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <memory>
#include <Face.h> //esp32_eyes

#include <pin_definition.h>


bool wifi_connected;


void setup() {
  Serial.begin(115200);
  
//  highlevel set up for I2C  //
  while(!Wire.begin(I2C_SDA,I2C_SCL)){
    Serial.println("Cannot start I2C communication.. trying again....");
    delay(300);
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
}

void loop() {


}
