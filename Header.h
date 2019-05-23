#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <Hash.h>
#include <SoftwareSerial.h>
#include <FS.h>
#include <ESP8266mDNS.h>    
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>

// Reference to the inbuilt LED. Remember that its active Low.
#define LED D4  

// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS D1 

/* Default IPv4 configurations.*/
IPAddress local_IP(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

typedef signed short qint16;
typedef struct {
  int     lcnt;   // Sequential log count
  String ltime;   // Time record of when reading was taken
  qint16 temp;    // Temperature values, short unsigned 16-bit integer to reduce memory requirement, saved as x10 more to preserve 0.1 resolution
} record_type;

const char* filename = "/datalog.txt";

#endif //PROTOCOL_H
