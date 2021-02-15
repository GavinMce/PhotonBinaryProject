

#include "Particle.h"
#include "neopixel.h"
#include "math.h"

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 10
#define PIXEL_TYPE WS2813
#define BIT_WIDTH 8

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

bool eightBit[BIT_WIDTH];

int decimal;

void setup()
{
  strip.begin();
  Particle.function("change", number);
  Particle.function("clear", clear);
  Particle.variable("decimal", decimal);
}

void loop()
{
    for(int i = 0 ; i < strip.numPixels(); i++){
        if(eightBit[i]){
            strip.setPixelColor(i,100,100,100);
        } else{
            strip.setPixelColor(i,0,0,0);
        }
    }
    
  strip.show();
  decimal = toDecimal();
    
}

int number(String num){
    uint16_t change = atoi(num);
    eightBit[change] = !eightBit[change];
    return 0;
}

int clear(String args){
    for(int i = 0; i < BIT_WIDTH; i++){
        eightBit[i] = false;
    }
    return 0;
}

int toDecimal(){
    int sum = 0;
    for(int i = 0; i < BIT_WIDTH; i++){
        if(eightBit[i]){
            sum += pow(2,i);
        }
    }
    return sum;
}


