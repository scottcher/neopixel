#include <Adafruit_NeoPixel.h>

#define PIN 0

int minLEDNum = 0;
int maxLEDNum = 9;

int animStartLEDNum = 1;

int ranLEDNum = 0;
int lastRanLEDNum = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxLEDNum, PIN, NEO_GRB + NEO_KHZ800);

uint32_t cExelonBlueBright = strip.Color(0, 0, 204); 
uint32_t cExelonOrangeBright = strip.Color(255, 128, 0); 
uint32_t cExelonGreenBright = strip.Color(0, 153, 0);

uint32_t cExelonBlueDim = strip.Color(0, 0, 102); 
uint32_t cExelonOrangeDim = strip.Color(60, 30, 0); 
uint32_t cExelonGreenDim = strip.Color(0, 76, 0);

uint32_t cLampBright = strip.Color(255, 255, 0); 
uint32_t cWhiteBright = strip.Color(255, 255, 255); 
uint32_t cOff = strip.Color(0, 0, 0);

void setup(){
  strip.begin();
  lamp(cLampBright);  // Turn on the lamp
  strip.show();
}

void loop(){
  animationController(random(1,5),random(5));
}

// the main animation controller
void animationController(uint8_t animationNum, uint8_t repeatCount){
   switch (animationNum){
     case 1:
       colorWipe(cExelonBlueDim, 1, 60);
       colorWipe(cExelonOrangeDim, 1, 60);
       colorWipe(cExelonGreenDim, 1, 60);
       break;
     case 2:
       paparazzi(cExelonBlueBright, 1, repeatCount*30, 50);
       paparazzi(cExelonOrangeBright, 1, repeatCount*30, 50);
       paparazzi(cExelonGreenBright, 1, repeatCount*30, 50);
       break;
     case 3:
       paparazzi(cWhiteBright, 1, repeatCount*30, 50);
       break;
     case 4:
       pulseWave(cExelonBlueBright, 6, 0.40, 1, 100);
       pulseWave(cExelonOrangeBright, 6, 0.40, 1, 100);
       pulseWave(cExelonGreenBright, 6, 0.40, 1, 100);
       break;
   }
}

// Set the lamp pixels for the light-bulb void lamp(uint32_t c){
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

// Fill the dots one after the other with a color void colorWipe(uint32_t c, uint8_t repeatCount, uint8_t wait){
  animationOff();
  for(uint8_t r=0; r<repeatCount; r++){  // how many times to cycle
    for(uint16_t i=animStartLEDNum; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
  }
}

// Randomly flash lights like flashbulbs void paparazzi(uint32_t c, uint8_t minJump, uint8_t repeatCount, uint8_t wait){
  for(uint8_t r=0; r<repeatCount; r++){  // how many times to cycle
    ranLEDNum = random(animStartLEDNum,maxLEDNum);
    if( ranLEDNum == lastRanLEDNum) continue;
    if( abs(ranLEDNum - lastRanLEDNum) <= minJump) continue;
    animationOff();
    strip.setPixelColor(ranLEDNum, c);
    strip.show();
    lastRanLEDNum = ranLEDNum;
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

// Get a color value by segment (R=1, G=2, B=3) uint8_t getPixelColorComponent(uint8_t pixelNum, uint8_t segment){
  uint8_t segmentColorValue;
  uint32_t c = strip.getPixelColor(pixelNum);
  switch( segment){
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
