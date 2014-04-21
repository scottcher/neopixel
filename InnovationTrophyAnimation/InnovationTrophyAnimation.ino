#include <Adafruit_NeoPixel.h>

#define PIN 0

int minLEDNum = 0;
int maxLEDNum = 30;

int animStartLEDNum = 1;

int ranLEDNum = 0;
int lastRanLEDNum = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLEDNum, PIN, NEO_GRB + NEO_KHZ800);

uint32_t cExelonBlueBright = strip.Color(0, 0, 204); 
uint32_t cExelonOrangeBright = strip.Color(255, 128, 0); 
uint32_t cExelonGreenBright = strip.Color(0, 153, 0);

uint32_t cLampBright = strip.Color(255, 255, 0); 
//uint32_t cWhiteBright = strip.Color(255, 255, 255); 
uint32_t cOff = strip.Color(0, 0, 0);

void setup(){
  strip.begin();
  lamp(cLampBright);  // Turn on the lamp
  strip.show();
}

void loop(){
  animationController(random(1,4),random(5));
}

// the main animation controller
void animationController(uint8_t animationNum, uint8_t repeatCount){
   switch (animationNum){
     case 1:
       pulseWave(cExelonBlueBright, 15, 0.80, repeatCount, 20);
       pulseWave(cExelonOrangeBright, 15, 0.80, repeatCount, 20);
       pulseWave(cExelonGreenBright, 15, 0.80, repeatCount, 20);
       break;
     case 2:
       rainbowCycle(repeatCount, 5);
       break;
     case 3:
       colorWipe(cExelonBlueBright, repeatCount, 40);
       colorWipe(cExelonOrangeBright, repeatCount, 40);
       colorWipe(cExelonGreenBright, repeatCount, 40);
       break;
   }
}

// Set the lamp pixels for the light-bulb 
void lamp(uint32_t c){
  for(int j=minLEDNum; j<animStartLEDNum; j++){
    strip.setPixelColor(j, c);
  }
  strip.show();
}

// Bright head followed by a tail
void pulseWave(uint32_t c, uint8_t tailLength, double fadePercent, uint8_t repeatCount, uint8_t wait){
  for( uint8_t r=0; r<repeatCount; r++){  // how many times to cycle
    for( uint8_t i=animStartLEDNum; i<strip.numPixels(); i++){ // cycle through the strip
      animationOff(); // turn off animation pixels
      strip.setPixelColor(i, c); // set head color
      for( uint8_t z=1; z<tailLength; z++){
        if(i-z >= animStartLEDNum){
          strip.setPixelColor(i-z, strip.Color(  getPixelColorComponent(i-z+1,1) * fadePercent,
                                                 getPixelColorComponent(i-z+1,2) * fadePercent,
                                                 getPixelColorComponent(i-z+1,3) * fadePercent));
        }
      }
      strip.show();
      delay(wait);
    }
  }
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t repeatCount, uint8_t wait) {
  for(uint8_t r=0; r<repeatCount; r++) { // how many times to cycle
   for(uint16_t i=animStartLEDNum; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
    animationOff(); // turn off animation pixels
    strip.show();
  }
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t repeatCount, uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*repeatCount; j++) { // repeatCount cycles of all colors on wheel
    for(i=animStartLEDNum; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// turn off the animation pixels
void animationOff(){
  for( uint8_t x=animStartLEDNum; x<strip.numPixels(); x++){
    strip.setPixelColor(x, cOff);
  }
  strip.show();
}

// Get a color value by segment (R=1, G=2, B=3) 
uint8_t getPixelColorComponent(uint8_t pixelNum, uint8_t segment){
  uint8_t segmentColorValue;
  uint32_t c = strip.getPixelColor(pixelNum);
  switch( segment ){
    case 1:
      segmentColorValue = ( c >> 16) & 255;
      break;
    case 2:
      segmentColorValue = ( c >> 8) & 255;
      break;
    case 3:
      segmentColorValue = c & 255;
      break;
  }
  return segmentColorValue;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
