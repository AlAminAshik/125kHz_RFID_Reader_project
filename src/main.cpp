// The Arduino framework is used to interact with the hardware rfid 6300 module.

#include <Arduino.h>
#include <rdm6300.h>
#define RDM6300_RX_PIN 2                        //rfid module to arduino pin 2(Rx)
Rdm6300 rdm6300;

int value = 0;

void setup(){
  Serial.begin(9600);
  rdm6300.begin(RDM6300_RX_PIN);                     //serial start for module
  Serial.println("\nPlace RFID tag near the rdm6300...");  
}

//Reading the RFID card
void readTags() {
  if (rdm6300.get_new_tag_id()){                   //rfid card availability check
  delay(10);                                       //wait for read card
  value = rdm6300.get_tag_id();                    //get rfid tag
  Serial.println(value);                           // print rfid tag
  }                               
  rdm6300.end();                                   //IMPORTANT- removes multiple read
  rdm6300.begin(RDM6300_RX_PIN);                   //IMPORTANT- removes multiple read
}

void loop() {
 readTags();                                     //check tag repeatedly
 delay(100);
}