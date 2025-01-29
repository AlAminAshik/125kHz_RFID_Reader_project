// The Arduino framework is used to interact with the hardware rfid 6300 module.

#include <Arduino.h>
#include <rdm6300.h>
#include <spi.h>
#include <wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, OLED_RESET);

#define RDM6300_RX_PIN 16                        //rfid module to arduino pin 2(Rx)
Rdm6300 rdm6300;

int value = 0;

void setup(){
  Serial.begin(9600);
  rdm6300.begin(RDM6300_RX_PIN);                     //serial start for module
  delay(1000);
  Serial.println("Place RFID tag near the rdm6300...");

  if(!display.begin(0x3c, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.println("Power Up");
  display.display(); 
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
		display.clearDisplay();
    display.setTextSize(2);
		display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);   //set the cursor to the first column and the first row
    display.println("RFID Tag:");
    display.setCursor(0,20);  //set the cursor to the first column and the second row
    display.print(value);
    display.display();
    delay(5000);
  }
  else{
    display.clearDisplay();
		display.setTextSize(2);
  	display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);   //set the cursor to the first column and the first row
    display.println("Place RFID.....");
    display.display();
  }                               
  // rdm6300.end();                                   //IMPORTANT- removes multiple read
  // rdm6300.begin(RDM6300_RX_PIN);                   //IMPORTANT- removes multiple read
}

void loop() {
 readTags();                                     //check tag repeatedly
 delay(50);                                    //delay for 1 second
}