#ifndef envelopeGenerator_h
#define envelopeGenerator_h
#include "Arduino.h"

class envelopeGenerator
{
  public:
    envelopeGenerator();
    envelopeGenerator(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints, byte isOneShot);
    void initEnvelope(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints, byte isOneShot); 
    unsigned short int getEnvelope(unsigned short int tickCounter);
	unsigned short int getEnvelope();
    float getEnvelopePercent(unsigned short int tickCounter, unsigned short int divident);
    void nextFrame(unsigned short int tick);
    void prevFrame(unsigned short int tick);
    
    float** envelopePoints;
    byte numberOfEnvelopPoints;
    unsigned short int envelopeBandwidth;
    unsigned short int envelopeBandwidthOneShot;
    unsigned long frameCounter;
	  byte oneShot;
	  unsigned short int increment=1;
    
    private:
    unsigned short int _counter, _envelopeIndex, _envelopeCounter;
    float _blockGradient;
};

#endif
