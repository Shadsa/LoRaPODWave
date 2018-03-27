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
#ifndef GLOBALDEF
#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h"
#include "images.h"
#include "webpage.h"
#endif

// Pin definetion of WIFI LoRa 32
// HelTec AutoMation 2017 support@heltec.cn
#define SCK 5   // GPIO5  -- SX127x's SCK
#define MISO 19 // GPIO19 -- SX127x's MISO
#define MOSI 27 // GPIO27 -- SX127x's MOSI
#define SS 18   // GPIO18 -- SX127x's CS
#define RST 14  // GPIO14 -- SX127x's RESET
#define DI00 26 // GPIO26 -- SX127x's IRQ(Interrupt Request)

#define BAND 433E6 //you can set band here directly,e.g. 868E6,915E6
#define PABOOST true
#define MAXVALUE 20

unsigned int counter = 0;

SSD1306 display(0x3c, 4, 15);
String rssi = "RSSI --";
String packSize = "--";
String packet;

const char *ssid = "LoRaPOD Wave 1.0";
const char *password = "1234567890";
String metaTable[MAXVALUE][2]; //Title + contenu
String valueTable[MAXVALUE];   //Options
int resultTable[MAXVALUE];     //index of the options

WiFiServer server(80);
///////////////////////////////////////////////////////
//Primitive for Lora manipulation and Harddware stuff//
///////////////////////////////////////////////////////
void logo()
{
  display.clear();
  display.drawXbm(0, 5, logo_width, logo_height, logo_bits);
  display.display();
}

void loraDataSend()
{
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
  digitalWrite(25, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);            // wait for a second
  digitalWrite(25, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);            // wait for a second
}

void loraDataReceived()
{
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 15, "Received " + packSize + " bytes");
  display.drawStringMaxWidth(0, 26, 128, packet);
  display.drawString(0, 0, rssi);
  display.display();
}

void cbk(int packetSize)
{
  packet = "";
  packSize = String(packetSize, DEC);
  for (int i = 0; i < packetSize; i++)
  {
    packet += (char)LoRa.read();
  }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC);
  loraDataReceived();
}
/////////////////////////////////
//Setup for WIFI and LORA stuff//
/////////////////////////////////
void wifiSetup()
{
  WiFi.mode(WIFI_AP);
  Serial.println(WiFi.softAP(ssid));
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  WiFi.printDiag(Serial);

  server.begin();
}

void LoRaSetup()
{
  pinMode(16, OUTPUT);
  pinMode(25, OUTPUT);

  digitalWrite(16, LOW); // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  display.clear();

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI00);

  if (!LoRa.begin(BAND, PABOOST))
  {
    display.drawString(0, 0, "Starting LoRa failed!");
    display.display();
    while (1)
      ;
  }
  display.drawString(0, 0, "LoRa Initial success!");
  display.display();
  delay(1000);
  //ONLY LORA RECEIVER ?
  LoRa.onReceive(cbk);
  LoRa.receive();
}

////////////////////////////////////////////////
//Setup for Data struct and Data manipulation//
///////////////////////////////////////////////

void initTables()
{
  for (int i = 0; i < MAXVALUE; i++)
  {
    valueTable[i] = "null";
    resultTable[i] = 0;
    metaTable[i][0]="null";
    metaTable[i][1]="null";
  }
}

void initTablesTESTFUNCTION()
{
  for (int i = 0; i < MAXVALUE; i++)
  {
    valueTable[i] = "value"+i;
    resultTable[i] = 0;
    metaTable[i][0]="ceci est la question, est la même pour tous dans le cas de l'exemple du sondage, peux servir à autre chose";
    metaTable[i][1]="ceci est l'information lié à l'index"+i;
  }
}


void addValue(String value)
{
  int i=0;
  while(valueTable[i]!="null"){
    i++;
  }
  valueTable[i]=value;
}

void deleteValue(int index)
{
  //todo
}

void incrementResult(int index)
{
  resultTable[index] = resultTable[index] + 1;
}

void decrementResult(int index)
{
  resultTable[index] = resultTable[index] - 1;
}

////////////////////////////////////
//Initialisation and loop control//
///////////////////////////////////

void setup()
{
  Serial.begin(115200);
  pinMode(5, OUTPUT); // set the LED pin mode

  delay(10);
  wifiSetup();
  LoRaSetup();
  initTablesTESTFUNCTION();
}

void loop()
{
  WiFiClient client = server.available(); // listen for incoming clients
  if (client)
  {                                // if you get a client,
    Serial.println("New Client."); // print a message out the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        if (c == '\n')
        {
          // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            /*
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> to turn the LED on pin 5 on.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn the LED on pin 5 off.<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
           */
            //client.println(mainPage);
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }

        // Check differents roads of query
        if (currentLine.endsWith("GET /GetPODMeta"))
        {
          generateMeta(metaTable, MAXVALUE);
          client.print(GetMetaPage);
        }
        if (currentLine.endsWith("GET /GetPODData"))
        {
          generateData(valueTable, MAXVALUE);
          client.print(GetDataPage);
        }
        if (currentLine.endsWith("GET /GetPODResult"))
        {
          generateData(resultTable, MAXVALUE);
          client.print(GetDataPage);
        }

        if (currentLine.endsWith("GET /UpdatePODParameter"))
        {
        }

        //Loop handling the upvote and downvote
        for (int i = 0; i < MAXVALUE; i++)
        {
          if (currentLine.endsWith("GET /UP_"+valueTable[i]))
          {
            incrementResult(i);
            Serial.println("Increment result"+valueTable[i]);
            client.print(Header+"Vote pris en compte !");
          }else if(currentLine.endsWith("GET /DOWN_"+valueTable[i])){
            decrementResult(i);
            Serial.println("Decrement result"+valueTable[i]);
            client.print(Header+"Vote pris en compte !");
          }
        }
        

        //Loop handling the incoming parameters for UpdatePODParameter


      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");

    // Parse the LoRa income and display
    

    //Send LoRa Output.*/
  }
}
