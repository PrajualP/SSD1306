#include <Wire.h>
#include <string.h>
#include "C:/Users/DELL/Documents/Arduino/ssd1306/font8x8_basic.h"
#define DEVICE_I2C_ADDRESS 0x3C
#define DS3231_I2C_ADDRESS 0x68
char daysofweek[8][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
uint8_t secs=0,mins=0,hours=0;
uint8_t days=0;//0 for monday , 6 for sunday
uint8_t amorpm=0;//0 for am , 1 for pm
uint8_t date_val,month_val,Year;

void setup() {
  // put your setup code here, to run once:
//  Wire.begin();
  Wire.begin();
  Serial.begin(9600);
  while (!Serial); 
  ssd1306_init();
  clear_display();
//  display_text();
//  scroll_text_horizontal();
//  brightness_control();
//  zoom_in();
  display_image();
//    display_time();
    
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
//    delay(100);
}

/*

void display_text(){
  char text[84]="Hello World!\nMulitine is OK!\nAnother line\nHello world!\nMulitine is OK!\nAnother line";
  uint8_t text_len = 83;
  uint8_t cur_page = 0;
  Wire.beginTransmission(DEVICE_I2C_ADDRESS);
  Wire.write(0x00); //Stream
  Wire.write(0x00); // reset column
  Wire.write(0x10);
  Wire.write(0xB0|cur_page);
  Wire.endTransmission(false);

  for (uint8_t i = 0; i < text_len; i++) {
      if (text[i] == '\n') {
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x00); //Command Stream
        Wire.write(0x00); // reset column
        Wire.write(0x10);
        Wire.write(0xB0|++cur_page);
        Wire.endTransmission(false);
       }
       else{
            Wire.beginTransmission(DEVICE_I2C_ADDRESS);
            Wire.write(0x40); //DAta Stream
            Wire.write(font8x8_basic_tr[(uint8_t)text[i]],8);
            Wire.endTransmission(false);
        }
  }
  
}

void scroll_text_horizontal(){
    Wire.beginTransmission(DEVICE_I2C_ADDRESS);
    Wire.write(0x00); //Command Stream
    Wire.write(0x26); //Right Scroll
    Wire.write(0x00); //Dummy
    Wire.write(0x01); //Page 1 start
    Wire.write(0x00); //5 frames
    Wire.write(0x05); // Page 5 End
    Wire.write(0x00); //Dummy
    Wire.write(0xFF); //Dummy

//    Wire.write(0x40);
    
//    Wire.write(0xA3);
//    Wire.write(0x00);
//    Wire.write(0x40);
    
    Wire.write(0x2F); //Execute Command
    

    
    Wire.endTransmission(false);
 }

void brightness_control(){
  uint8_t contrast = 0;
  uint8_t direction_val = 1;
  while(true){
    Wire.beginTransmission(DEVICE_I2C_ADDRESS);
    Wire.write(0x00); //Command Stream
    Wire.write(0x81);
    Wire.write(contrast);
    Wire.endTransmission(false);
    delay(10);
    contrast += direction_val;
    if (contrast == 0xFF) { direction_val = -1; }
    if (contrast == 0x0) { direction_val = 1; }
    }
    
}

void zoom_in(){
    Wire.beginTransmission(DEVICE_I2C_ADDRESS);
    Wire.write(0x00); //Command Stream
    Wire.write(0xD6);
    Wire.write(0x01);
    Wire.endTransmission(false);
    delay(10);
}

*/

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
        Wire.write(try0[(128*page)+cols]);
        Wire.endTransmission(false);
        }
      
    }

}


void display_time(){

  uint8_t secs_arr[2],mins_arr[2],hours_arr[2];

  for(int i=0;i<2;i++){
    if(i==0){
      secs_arr[i]=secs/10;
      mins_arr[i]=mins/10;
      hours_arr[i]=hours/10;
    }
    else{
      secs_arr[i]=secs%10;
      mins_arr[i]=mins%10;
      hours_arr[i]=hours%10;
     }
    
   }

  //Display Part
 uint8_t page=0,cols=0;
 /*
  ///////////////////////////////////Day///////////////////////////////////////
 
  for( page=2;page<8;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x10);
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<16;cols++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(day_bytes[days][(16*(page-2))+cols]);
        Wire.endTransmission(false);
      }
  }


  /////////////////////////////////Hours////////////////////////////////////////
  page=0;
  cols=0;
  for(int index=0;index<2;index++){
    for( page=2;page<8;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x10|(index+1));
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<16;cols++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(font18[hours_arr[index]][(16*(page-2))+cols]);
        Wire.endTransmission(false);
      }
    }  
  }

  ////////////////////////////////////////COLON///////////////////////////////////////////
  page=0;
  cols=0;
  for( page=2;page<8;page++){
    Wire.beginTransmission(DEVICE_I2C_ADDRESS);
    Wire.write(0x00); //Stream
    Wire.write(0x00); // reset column
    Wire.write(0x13);
    Wire.write(0xB0|page);
    Wire.endTransmission(false);
    for(cols=0;cols<16;cols++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x40); //Data Stream
      Wire.write(colon[(16*(page-2))+cols]);
      Wire.endTransmission(false);
    }
  }


  /////////////////////////////////////Minutes///////////////////////////////////////////////////
  page=0;
  cols=0;
  for(int index=0;index<2;index++){
    for( page=2;page<8;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x10|(4+index));
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<16;cols++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(font18[mins_arr[index]][(16*(page-2))+cols]);
        Wire.endTransmission(false);
      }
    }  
  } 

  
  
  ///////////////////////////////////////////////AMPM///////////////////////////////////
  page=0;
  cols=0;
  for( page=5;page<8;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x16);
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<32;cols++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(ampm[amorpm][(16*(page-5))+cols]);
        Wire.endTransmission(false);
      }
    }  

*/
  //////////////////////////////////////////////Seconds//////////////////////////////////////////////////
  page=0;
  cols=0;
  for(int index=0;index<2;index++){
    for( page=2;page<5;page++){
      Wire.beginTransmission(DEVICE_I2C_ADDRESS);
      Wire.write(0x00); //Stream
      Wire.write(0x00); // reset column
      Wire.write(0x10|(6+index));
      Wire.write(0xB0|page);
      Wire.endTransmission(false);
      for(cols=0;cols<16;cols++){
        Wire.beginTransmission(DEVICE_I2C_ADDRESS);
        Wire.write(0x40); //Data Stream
        Wire.write(fontsec[secs_arr[index]][(16*(page-2))+cols]);
        Wire.endTransmission(false);
      }
    }  
  }
    
  
}


/***************************************Display Time****************************************************************/

  uint8_t *read_register(uint8_t register_code, uint8_t no_of_bytes) {
    static uint8_t ret[7] = {0x00};
    Wire.beginTransmission(DS3231_I2C_ADDRESS); // start transmission to device
    Wire.write(register_code); // sends register address to read from
    Wire.endTransmission(false); // end transmission
  
    Wire.requestFrom(DS3231_I2C_ADDRESS, (uint8_t)no_of_bytes);// send data n-bytes read
    for (int i = 0; i < no_of_bytes; i++) {
      ret[i] = Wire.read(); // receive DATA
    }
  //  for (int i = 0; i < no_of_bytes; i++) {
  //    Serial.println(ret[i]);
  //  }
    return ret;
  }

void watch_display(){
  uint8_t *temp;
  temp= read_register(0x00, 7);
  Serial.println("*****************************");
  secs =(*temp&0x0F)+(((*temp&0x70)>>4)*10);
  temp++;
  mins =(*temp&0x0F)+(((*temp&0x70)>>4)*10);
  temp++;

//  Serial.print("Real Value: ");
//  Serial.println(*temp);
  
//  if((*temp&40)>>6){
//      Serial.println("12 hrs clock");
      Serial.print("Time: ");
      hours=((*temp&0x10)>>4)*10+(*temp&0x0F);
      Serial.print(hours);   
      Serial.print(":");
      
//  }
//  else{
//    Serial.print("24 hrs clock");
//    Serial.print("Time: ");
//    hours=((*temp&0x20)>>5)*20+((*temp&0x10)>>4)*10+(*temp&0x0F);
//    Serial.print(hours);   
//      Serial.print(":");
//  }
//  
  Serial.print(mins);
  Serial.print(":");
  Serial.print(secs);
  if((*temp&0x20)>>5){
    Serial.println("PM");
    amorpm=1;
  }
   else{
    Serial.println("AM");
    amorpm=0;
    }
  
  //Day
  temp++;
  days=(*temp);
  Serial.print("Day:");
  char today[10];
  strcpy(today,daysofweek[days-1]);
  Serial.println(today);
  
  //Date
  temp++;
  Serial.print("Date:");
  date_val=((*temp&0x30)>>4)*10+(*temp&0x0F);
  Serial.println(date_val);

  //Month
  temp++;
  Serial.print("Month:");
  month_val=((*temp&0x10)>>4)*10+(*temp&0x0F);
  Serial.println(month_val);

   //Year
  temp++;
  Serial.print("Year:");
  Year=(((*temp&0xF0)>>4)*10)+(*temp&0x0F);
  Serial.println(2000+Year);
  
  Serial.println("*****************************"); 
}



/***************************************End of Display Time****************************************************************/



void loop() {
//  clear_display();
//  watch_display();
//  display_time();
//    delay(1000);
}
