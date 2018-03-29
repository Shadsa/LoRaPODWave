#ifndef GLOBALDEF
#include <WiFi.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SSD1306.h"
#endif

//chaque page doit finir par une ligne vide, protocol http 1.1 oblige
String mainPage ="HTTP/1.1 200 OK\nContent-type:text/html\nAccess-Control-Allow-Origin:*\n<h1> Acceuil LoRaWave Station </h1>\n<p> Bienvenu sur la station LoRa </p>\n";
String PostDataPage ="HTTP/1.1 200 OK\nContent-type:text/html\nAccess-Control-Allow-Origin:*\n<h1> POST Page </h1>\n";
String Header ="HTTP/1.1 200 OK\nContent-type:text/html\nAccess-Control-Allow-Origin:*\n\n";
String GetDataPage; //JSON a generer dans une fonction
String GetMetaPage;//Meta a generer dans une fonction
String UpdatePage ="HTTP/1.1 200 OK\nContent-type:text/html\nAccess-Control-Allow-Origin:*\n<h1> Update Page </h1>\n";

void generateMeta(String meta){
    GetMetaPage = meta;
}
///////////////////////
//   JSON Parser   ///
/////////////////////
void generateData(String data[], int tabsize){
    String json = Header+"{\"title\" : \"DataCollection\", \"collection\" : [";
    int i=0;
    while(data[i]!="null" && i<tabsize){
        if(i!=0){
            json+=" , ";
        }
        json = json+"{\"id\" : \""+i+"\",\"value\" : \""+data[i]+"\"}";
        i++;
    }
    json+= "]}\n";
    GetDataPage = json;
}

void generateData(int data[],String data2[], int tabsize){
    String json = Header+"{\"title\" : \"ResultCollection\", \"collection\" : [";
    int i=0;
    while(i<tabsize){
        if(i!=0){
            json+=" , ";
        }
        json = json+"{\"id\" : \""+i+"\",\"value\" : \""+data2[i]+"\",\"num\" : \""+data[i]+"\"}";
        i++;
    }
    json+= "]}\n";
    GetDataPage = json;
}

void generateMeta(String data[][2], int tabsize){
    String json = Header+"{\"title\" : \"MetaCollection\", \"collection\" : [";
    int i=0;
    while(data[i][1]!="null" && i<tabsize){
        if(i!=0){
            json+=" , ";
        }
        json = json+"{\"title\" : \""+data[i][0]+"\",\"information\" : \""+data[i][1]+"\"}";
        i++;
    }
    json+= "]}\n";
    GetMetaPage = json;
}
