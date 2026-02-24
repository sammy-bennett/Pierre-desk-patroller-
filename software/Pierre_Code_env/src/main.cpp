#include <Arduino.h>
#include <Wire.h>
#include <memory>
#include <Face.h> //esp32_eyes

#include <pin_definition.h>



void setup() {
  Serial.begin(115200);
  
  while(!Wire.begin(I2C_SDA,I2C_SCL)){
    Serial.println("Cannot start I2C communication.. trying again....");
    delay(500);
  }

}

void loop() {


}


