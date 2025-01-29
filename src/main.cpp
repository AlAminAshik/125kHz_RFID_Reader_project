// The Arduino framework is used to interact with the hardware rfid 6300 module.

#include <Arduino.h>
#include <rdm6300.h>
#include <spi.h>
#include <wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define RDM6300_RX_PIN 2                        //rfid module to arduino pin 2(Rx)
Rdm6300 rdm6300;

int value = 0;

void setup(){
  Serial.begin(9600);
  rdm6300.begin(RDM6300_RX_PIN);                     //serial start for module
  Serial.println("Place RFID tag near the rdm6300...");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

//Reading the RFID card
void readTags() {
  value = 0;
  if (rdm6300.get_new_tag_id()){                   //rfid card availability check
  delay(10);                                       //wait for read card
  value = rdm6300.get_tag_id();                    //get rfid tag
  Serial.println(value);                           // print rfid tag
  }

  if (value != 0){
    display.setTextSize(2);
    display.setCursor(0,0);   //set the cursor to the first column and the first row
    display.println("RFID Tag:");
    //display.setCursor(0,20);  //set the cursor to the first column and the second row
    display.print(value);
    display.display();
    delay(3000);
  }
  else{
    display.clearDisplay();
    display.setCursor(0,0);   //set the cursor to the first column and the first row
    display.println("Place RFID Tag!");
    display.display();
  }                               
  // rdm6300.end();                                   //IMPORTANT- removes multiple read
  // rdm6300.begin(RDM6300_RX_PIN);                   //IMPORTANT- removes multiple read
}

void loop() {
 readTags();                                     //check tag repeatedly
 delay(500);                                    //delay for 1 second
}