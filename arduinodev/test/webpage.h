#ifndef GLOBALDEF
#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h"
#endif

//chaque page doit finir par une ligne vide, protocol http 1.1 oblige
String mainPage ="HTTP/1.1 200 OK\nContent-type:text/html\n<h1> Acceuil LoRaWave Station </h1>\n<p> Bienvenu sur la station LoRa </p>\n";
String PostDataPage ="HTTP/1.1 200 OK\nContent-type:text/html\n<h1> POST Page </h1>\n";
String GetDataPage; //JSON a generer dans une fonction
String GetMetaPage;//Meta a generer dans une fonction
String UpdatePage ="HTTP/1.1 200 OK\nContent-type:text/html\n<h1> Update Page </h1>\n";

void generateMeta(String meta){
    GetMetaPage = meta;
}

void generateData(String data[], int tabsize){
    String json = "{\"title\" : \"DataCollection\", \"collection\" : [{";
    int i=0;
    while(data[i]!="null" && i<tabsize){
        if(i!=0){
            json+=" , ";
        }
        json = json+"\""+i+"\" : \""+data[i]+"\"";
        i++;
    }
    json+= "}]}";
    GetDataPage = json;
}
