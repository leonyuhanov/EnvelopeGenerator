# EnvelopeGenerator
Generates dynamic envelopes with N positive integer points

* void initEnvelope(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints)
  * Dynamic envelope generator
  * Pass "numberOfPoints" number of elemnts via the array of "unsigned short int points"
  * Pass "numberOfPoints" number of durationsPerPoint via the array of "unsigned short int ticks"
  * "points" an array of Envelope points, the output will wrap around from the last point to the 1st automaticly
  * "ticks" an array of time ticks PER point. This essentialy gives you a way to scale each point and the speed/gradient of the curve
  ```C++
  envelopeGenerator envelopeOne;
  const byte numberOfPoints = 4;
  unsigned short int frameCounter=0;
  unsigned short int points[numberOfPoints] = {0,10,20,5};
  unsigned short int ticks[numberOfPoints] = {30, 30, 30, 30};
  envelopeOne.initEnvelope(points, ticks, numberOfPoints);
  ```
* unsigned short int getEnvelope(unsigned short int frameCounter)
  * Generates your curve based on your point list and time blocks using "frameCounter" as the time index
  * "envelopeOne.envelopeBandwidth" can be used to limit your frame counter and keep it in bounds of your dynamic frame ticks
  ```C++
  while(true)
  {
   System.printf("\r\n%d", envelopeOne.getEnvelope(frameCounter));
   frameCounter = (frameCounter+1)%envelopeOne.envelopeBandwidth;
  }
  ```
  The above generates this:
 
  <img src="https://github.com/leonyuhanov/EnvelopeGenerator/blob/master/envelopOutput.jpg" width="300" />
