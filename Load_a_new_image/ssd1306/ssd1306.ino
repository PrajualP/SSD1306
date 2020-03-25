#include <Wire.h>
#include <string.h>
#include "Timer.h"
#include "C:/Users/DELL/Documents/Arduino/ssd1306/font8x8_basic.h"
#define DEVICE_I2C_ADDRESS 0x3C
int change_image=0;
Timer t;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); 
  ssd1306_init();
  clear_display();
  display_image();
  t.every(5000, timer_callback);
}
void ssd1306_init(){
  Wire.beginTransmission(DEVICE_I2C_ADDRESS); 
  Wire.write(0x00); //CMD Stream
  Wire.write(0x8D); //Enabling Charge Pump
  Wire.write(0x14); //Data Byte
  Wire.write(0xA1); //127 mapped to SEG0
  Wire.write(0xC8); //Remapped Mode
  Wire.write(0xA6); //0is on 1 is off[Background is white and Letters in Black]
  Wire.write(0x2E); //Deactivate Scroll
  Wire.write(0xAF); // Display on mode
  Wire.endTransmission(false); // end transmission 
  delay(100); 
}

void clear_display(){
    
    uint8_t zero[8]={0x00};
    for(uint8_t i=0;i<8;i++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x80); // Single Command
      Wire.write(0xB0|i);
      Wire.endTransmission(false);
      for(uint8_t j=0;j<128;j++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(zero,8);
        Wire.endTransmission(false);
        }
      
    }
}


void display_image(){
    uint8_t cur_page = 0;
    uint8_t page=0,cols=0;
    for( page=0;page<8;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x10);
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<128;cols++){
            Wire.beginTransmission(DEVICE_I2C_ADDRESS);
            Wire.write(0x40); //Data Stream
            if(change_image == 1){
               Wire.write(try0[(128*page)+cols]);
             }
             else{
                Wire.write(Heart[(128*page)+cols]);
             }
            Wire.endTransmission(false);
       }
      
    }

}

void timer_callback(){
/*Byte Constraint in Arduino Uno but will work in other chipsets(Remove the below commented Line to experience change in Image)*/
// change_image=change_image?0:1;
  clear_display();
  display_image();
}

void loop() {
  t.update();
}
