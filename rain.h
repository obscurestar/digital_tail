//rain.h
//Use random walks to do a palette shift.  

#ifndef RAIN_H  //These preprocessor directives let you include without worrying about dupes.
#define RAIN_H  //Once defined it doesn't need to be re-included.
#include <Adafruit_NeoPixel.h>  //Someone else did the heavy lifting.  Say thanks!
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include "color.h"

extern const short NUM_LEDS; //Let's address this in V3!
extern Adafruit_NeoPixel H_LEDS;

class Rain
{
public:   //public variables.
  int mShiftOdds; //The 1 in n odds of picking a new hue mask.
public:   //public functions.
  Rain(); //Default constructor
  void loopStep();  //Per frame call from loop.
private:
  byte pickHueMask();   //Get a new hue mask
  byte walkPixels();    //The math of the shimmer.
private:  //class private variables
  byte mHueMask;  //Which bits are active on this iteration.
  bool mDirty;    //Set to true when any RGB not in current set is set for any pixel in chain.
};

Rain::Rain() : mDirty(false),
               mShiftOdds(2000)
{
  mHueMask = pickHueMask();
}

void Rain::loopStep()
{
  if (!walkPixels())
  {
    if (!random(mShiftOdds))
    {
      mHueMask = pickHueMask();
    }
  }
}

byte Rain::pickHueMask()
{
  //TODO pass in exclude_bit.

  byte cbits=random(4)+3;  //generate value from 1-7 this excludes 0(black)

  return cbits;
}

//Iterate through pixels and stagger around in the relative color space. 
byte Rain::walkPixels()
{
  mDirty=false;
  for (int p=0;p<NUM_LEDS; ++p)  //Loop through pixels.
  {
    for (int c=0;c<3;++c)     //Loop through RBG sub-pixels of each pixel.
    {
      COLOR pc;
      pc.l = H_LEDS.getPixelColor(p);
      
      if ( (mHueMask >> c) & 1 )
      {
          signed int val =pc.c[c] + (random(3) - 1); // rand result set [0,1,2] - 1 = [-1, 0, 1]
          if (val > 0 && val < 255)
          {
            pc.c[c] = val;  //Stagger around in the relative color space.
            H_LEDS.setPixelColor(p,pc.l);
          }
      }
      else
      {                       //Stagger towards 0, let iterator know this one doesn't count. 
        if (pc.c[c] > 0) //This RGB should not be set in this hue. Still draining previous color
        {
          mDirty=true;
          if (!random(8))
          {
            pc.c[c] --; //Wander slowly towards 0.
            H_LEDS.setPixelColor(p,pc.l);
          }
        }
      }
    }
  }
  return mDirty;
}


#endif //RAIN_H
