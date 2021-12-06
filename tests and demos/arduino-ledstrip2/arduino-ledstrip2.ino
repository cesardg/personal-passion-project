#include <Adafruit_DotStar.h>
#include <SPI.h>         


#define NUMPIXELS 300 // Number of LEDs in strip


#define DATAPIN    11 
#define CLOCKPIN   13 

Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BGR);
//Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup() {


  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}



void loop() {

  //for (int i=100; i<30; i++) strip.setPixelColor(i, 0x00FF00);
  strip.fill(0x00FF00, 0, 30);
  strip.setBrightness(40);
  strip.show();       // Refresh strip
  delay(1000);
  
}
