#include <Adafruit_DotStar.h>
#include <SPI.h>         


#define NUMPIXELS 300 // Number of LEDs in strip


#define DATAPIN    11 
#define CLOCKPIN   13 

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BGR);

void setup() {


  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}



void loop() {


  
  //for (int i=100; i<300; i++) strip.setPixelColor(i, 0x00FF00);
  strip.fill(0x00FF00, 0, 300);
  strip.setBrightness(40);
  strip.show();                     // Refresh strip
 
}
