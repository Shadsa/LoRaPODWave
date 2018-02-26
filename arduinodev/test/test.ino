/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h" 
#include "images.h"


// Pin definetion of WIFI LoRa 32
// HelTec AutoMation 2017 support@heltec.cn 
#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     14   // GPIO14 -- SX127x's RESET
#define DI00    26   // GPIO26 -- SX127x's IRQ(Interrupt Request)

#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define PABOOST true
#define MAXVALUE 20

unsigned int counter = 0;

SSD1306 display(0x3c, 4, 15);
String rssi = "RSSI --";
String packSize = "--";
String packet ;

const char* ssid     = "OnePwet 5";
const char* password = "1234567890";
const char* valueTable[MAXVALUE];

WiFiServer server(80);

void logo(){
  display.clear();
  display.drawXbm(0,5,logo_width,logo_height,logo_bits);
  display.display();
}

void loraDataSend(){
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  
  display.drawString(0, 0, "Sending packet: ");
  display.drawString(90, 0, String(counter));
  display.display();

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}

void loraDataReceived(){
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0 , 15 , "Received "+ packSize + " bytes");
  display.drawStringMaxWidth(0 , 26 , 128, packet);
  display.drawString(0, 0, rssi);  
  display.display();
}

void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { packet += (char) LoRa.read(); }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  loraDataReceived();
}

void LoRaSetup()
{
  pinMode(16,OUTPUT);
  pinMode(25,OUTPUT);
  
  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50); 
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();
  display.flipScreenVertically();  
  display.setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  display.clear();
  
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI00);
  
  if (!LoRa.begin(BAND,PABOOST))
  {
    display.drawString(0, 0, "Starting LoRa failed!");
    display.display();
    while (1);
  }
  display.drawString(0, 0, "LoRa Initial success!");
  display.display();
  delay(1000);
  //ONLY LORA RECEIVER ?
  LoRa.onReceive(cbk);
  LoRa.receive(); //=> take it away, block the code
}

void setup()
{
    Serial.begin(115200);
    pinMode(5, OUTPUT);      // set the LED pin mode

    delay(10);
    WiFi.mode(WIFI_AP);
       
    Serial.println(WiFi.softAP(ssid));       
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    WiFi.printDiag(Serial);
    
    server.begin();
    LoRaSetup();

    //Test setup for value array
    for(int i=0;i<MAXVALUE;i++){
      valueTable[i] = "test";
    }
}

int value = 0;

void loop(){
 WiFiClient client = server.available();
 char c;
  if (client) {
    String currentLine = "";
    if (client.connected()) {
      Serial.println("Connected to client");
      char c;
      do{
        c = client.read();
        if(c!='\r'){
          currentLine+=c;
        }        
        Serial.write(c);
      }while(c != '\n');
      Serial.println(currentLine);
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type:text/html");
      client.println();  
       

    }
    //Yolo
    // close the connection:
   // client.stop();
  }

  // Parse the LoRa income and display

  //Send LoRa Output.
}
