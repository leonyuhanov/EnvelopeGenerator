#include <ESP8266WiFi.h>
#include "EnvelopeGenerator.h"

envelopeGenerator envel_Object;
const byte numberOfPoints = 4;
unsigned short int points[numberOfPoints] = {0,100,50,100};
unsigned short int ticks[numberOfPoints] = {100, 100, 200, 50};


void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  envel_Object.initEnvelope(points, ticks, numberOfPoints);
}

void loop()
{   
  Serial.printf("\r\n%d", envel_Object.getEnvelope(envel_Object.frameCounter));
  envel_Object.nextFrame(1);
  delay(10);
}
