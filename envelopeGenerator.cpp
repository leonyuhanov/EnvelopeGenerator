#include "envelopeGenerator.h"

envelopeGenerator::envelopeGenerator()
{
  frameCounter=0;
  oneShot=0;
}

envelopeGenerator::envelopeGenerator(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints, byte isOneShot)
{
  initEnvelope(points, ticks, numberOfPoints, isOneShot);
}

void envelopeGenerator::initEnvelope(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints, byte isOneShot)
{
  //Init Envelops in memory
  frameCounter = 0;
  oneShot = isOneShot;
  numberOfEnvelopPoints = numberOfPoints;
  envelopePoints = new float*[numberOfEnvelopPoints];
  for(_counter=0; _counter<numberOfEnvelopPoints; _counter++)
  {
    envelopePoints[_counter] = new float[3];
  }
  _envelopeIndex=0;
  envelopeBandwidth=0;
  envelopeBandwidthOneShot=0;
  
  //set up Envelope Points
  for(_counter=0; _counter<numberOfEnvelopPoints; _counter++)
  {
    envelopePoints[_counter][0] = points[_counter];
    if(_counter+1==numberOfEnvelopPoints)
    {
      envelopePoints[_counter][1] = points[0];
    }
    else
    {
      envelopePoints[_counter][1] = points[_counter+1];
    }
    envelopePoints[_counter][2] = ticks[_counter];
    envelopeBandwidth += ticks[_counter];
    if(_counter+1<numberOfEnvelopPoints)
    {
      envelopeBandwidthOneShot += ticks[_counter];
    }
  }
  //Reset the ticker to 0
  _envelopeIndex = 0;
}

void envelopeGenerator::reInitEnvelope(unsigned short int* points, unsigned short int* ticks, byte numberOfPoints, byte isOneShot)
{
  //Init Envelops in memory
  frameCounter = 0;
  oneShot = isOneShot;
  numberOfEnvelopPoints = numberOfPoints;
  //envelopePoints = new float*[numberOfEnvelopPoints];
  //for(_counter=0; _counter<numberOfEnvelopPoints; _counter++)
  //{
  //  envelopePoints[_counter] = new float[3];
  //}
  _envelopeIndex=0;
  envelopeBandwidth=0;
  envelopeBandwidthOneShot=0;
  
  //set up Envelope Points
  for(_counter=0; _counter<numberOfEnvelopPoints; _counter++)
  {
    envelopePoints[_counter][0] = points[_counter];
    if(_counter+1==numberOfEnvelopPoints)
    {
      envelopePoints[_counter][1] = points[0];
    }
    else
    {
      envelopePoints[_counter][1] = points[_counter+1];
    }
    envelopePoints[_counter][2] = ticks[_counter];
    envelopeBandwidth += ticks[_counter];
    if(_counter+1<numberOfEnvelopPoints)
    {
      envelopeBandwidthOneShot += ticks[_counter];
    }
  }
  //Reset the ticker to 0
  _envelopeIndex = 0;
}

unsigned short int envelopeGenerator::getEnvelope()
{
	unsigned short int returnValue=0;
	if(oneShot==0)
	{
		returnValue = getEnvelope(frameCounter);
		nextFrame(increment);
		return returnValue;
	}
	else
	{
		if(frameCounter+increment<envelopeBandwidthOneShot)
		{
			returnValue = getEnvelope(frameCounter);
			nextFrame(increment);
			return returnValue;
		}
		else
		{
			//frameCounter=0;
			return getEnvelope(frameCounter);
		}
	}
}

void envelopeGenerator::reset()
{
  frameCounter=0;
}

unsigned short int envelopeGenerator::getEnvelope(unsigned short int tickCounter)
{
  _envelopeCounter = envelopePoints[0][2];
  _counter=0;
  while(_counter<numberOfEnvelopPoints)
  {
    if(_counter==0 && tickCounter>=0 && tickCounter<_envelopeCounter)
    {
      _envelopeIndex = _counter;
      break;
    }
    else if(tickCounter>=envelopePoints[_counter][2] && tickCounter<_envelopeCounter)
    {
      _envelopeIndex = _counter++;
      break;
    }
    _counter++;
    _envelopeCounter += envelopePoints[_counter][2];
  }
  //grab gradient
  if(_envelopeIndex==0)
  {
    _blockGradient = ((envelopePoints[_envelopeIndex][1] - envelopePoints[_envelopeIndex][0]) / envelopePoints[_envelopeIndex][2])*tickCounter;
    if(_blockGradient<0)
    {
      return envelopePoints[_envelopeIndex][0] - abs(_blockGradient);
    }
    else
    {
      return envelopePoints[_envelopeIndex][0] + abs(_blockGradient);
    }
  }
  else
  {
    _envelopeCounter=0;
    _counter=0;
    while(_counter<_envelopeIndex)
    {
      _envelopeCounter+=envelopePoints[_counter][2];
      _counter++;
    }
    _blockGradient = (((envelopePoints[_envelopeIndex][1] - envelopePoints[_envelopeIndex][0]) / envelopePoints[_envelopeIndex][2]) * (tickCounter-_envelopeCounter));
    if(_blockGradient<0)
    {
      return envelopePoints[_envelopeIndex][0] - abs(_blockGradient);
    }
    else
    {
      return envelopePoints[_envelopeIndex][0] + abs(_blockGradient);
    }
  }
}

float envelopeGenerator::getEnvelopePercent(unsigned short int tickCounter, unsigned short int divident)
{
  return ((float)getEnvelope(tickCounter))/divident;
}

void envelopeGenerator::nextFrame(unsigned short int tick)
{
  frameCounter = (frameCounter+tick)%envelopeBandwidth;
}

void envelopeGenerator::prevFrame(unsigned short int tick)
{
  frameCounter = (frameCounter-tick)%envelopeBandwidth;
}
