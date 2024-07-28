/*Digital Rain 2.  
  Previously:  Prototype exists now only in compiled form.  RIP unbacked-up repository.
  I loved you, but respected you not nearly enough.In your honor, your reproduction
  shall be written and rewritten to teach.

  Overview:  Using coin tosses and a few simple rules, we shall cycle a limited palette in a
  way that shimmers.  See rain.h tab at top of window for more details.
  
  Terms:
    LED   Generally used when referring to the physical hardware.
    PIXEL Generally to refer to the digital representation of the LED
  */

//Uses Arduino Genuino Micro board designation 

//TODO protect constants in V3
//Hardware constants
const short PIN_LED = 9;  //Pin connecting the IN on the LED strip to the CPU board.
const short NUM_LEDS = 16; //Num LEDS in our array.

#include <Adafruit_NeoPixel.h>  //Someone else did the heavy lifting.  Say thanks!
#ifdef __AVR__
  #include <avr/power.h>
#endif

/*Include the other tabs from the top of this window in our application. 
 * This structure isn't required but it's a helpful way to collect 
 * related notions and it's good to get organized early on
 */
 #include "rain.h"  //The digital rain algorithm
  
//TODO protect globals in V3.
//Global variables
/*Handle to the LED array. We will use this to apply the values to the pixels in the array.*/
//string leds are RGB strips are GRB
Adafruit_NeoPixel H_LEDS = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_RGB + NEO_KHZ800);

byte MAX_BRITE=255;  //The brightest we want our display to get. 

Rain rain;           //Container class for rain algorithm.  See rain.h for details

void setup() {       //Builtin function run once at start of app.
  Serial.begin(9600); //Open serial(Com speed) Useful for debug but watch string memory use.

  H_LEDS.setBrightness(MAX_BRITE);  //TODO experiment with this feature.
  H_LEDS.begin(); //Initialize communication with WS281* chain.
  H_LEDS.show(); //No values are set so this should be black.
}

void loop() { //Builtin function.
  rain.loopStep();
  H_LEDS.show();
  //TODO:
  /*
   * This delay is hard-coded and we have to recompile and re-upload any time
   * we want to change it.  A variable control would be cool.  In V3 we'll 
   * think of that control as a discrete concept and discuss implementing it
   * over serial, potentiometer, or digital signal and some example uses of 
   * each.
   */
  //delay(50);
}
