#ifndef envelopeGenerator_h
#define envelopeGenerator_h
#include "Arduino.h"

class envelopeGenerator
{
  public:
    envelopeGenerator();
    void initEnvelope(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints); 
    unsigned short int getEnvelope(unsigned short int tickCounter);
    void nextFrame(unsigned short int tick);
    void prevFrame(unsigned short int tick);
    
    float** envelopePoints;
    byte numberOfEnvelopPoints;
    unsigned short int envelopeBandwidth;
    unsigned long frameCounter;
    
    private:
    unsigned short int _counter, _envelopeIndex, _envelopeCounter;
    float _blockGradient;
};

#endif
