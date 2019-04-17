//www.elegoo.com
//2016.12.08
#include "SR04.h"
#include <SoftwareSerial.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define LED 4

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
SoftwareSerial SIM900(7, 8); 

long a;
int i=0;
bool msgsent = false;

void setup() {
  //let the gsm connect to the network
    SIM900.begin(19200);
    delay(20000);

    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    
    SIM900.print("AT+CMGF=1\r"); 
    delay(100);

    SIM900.print("AT+CNMI=2,2,0,0,0\r");
}


bool sendSMS() {
  //Set the phone number to send the message
  SIM900.println("AT+CMGS = \"+33630114200\""); 
  delay(100);
  
  //Set the message content
  SIM900.println("Ce projet mérite un 20 !"); 
  delay(100);

  // End AT command with a ^Z, ASCII code 26
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  // Wait to give module time to send SMS
  delay(5000); 
  return true;
}

char receivesms(){
  return SIM900.read();
}

void loop() {
  //Take the disctance from the sensor and display it
    a=sr04.Distance();
    Serial.print(a);
    Serial.println(" cm");

    
    char incoming_char=0;
    while(a < 15){
      //Make the LED flash
      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);
      delay(500);

      //i contain the number of second
      i++;
      incoming_char=0;
      a=sr04.Distance();
      Serial.print(i);
      Serial.println(" seconde");
      
      //If we wait more than 5 sec with an obstacle we send a SMS
      if(i >= 5 && msgsent == false){
        //Switch on the LED
        digitalWrite(LED, HIGH);
        //Send a sms
        msgsent = sendSMS();
        if(msgsent == true)
          Serial.println("Message envoyé !");
         digitalWrite(LED, LOW);
      }
    }
    i=0;
    digitalWrite(LED, LOW);
    delay(1000);
}
