# personal-passion-project

## Connectree

Concept: https://cesar.vercel.app/concept

Process: https://cesar.vercel.app/

Send a message to my Connectree: https://cesardegreve.be/connectree/?tree-id=Rudolph-A3EpYEF7zU

## Hardware, components & supplies
* 2X Arduino UNO WiFi Rev2
* Adafruit DotStar Digital LED Strip - 30 LED per meter - 10 meter
* 5V 10A switching power supply for the LED strip
* 9V 1.8A power supply for the Arduino
* 9V battery + clip for the other Arduino
* Jumper wires & 4-pin JST SM Plugs
* 1000µF (6.3V or higher) capacitor
* USB cable
* Servo motor
* DHT11 Temperature & Humidity Sensor (3 pins)
* PIR motion sensor (WPSE314)
* Toggle switch

## Software
* Arduino IDE (1.8.13)
* Visual Studio Code
* Note: Make sure you add all the librarys (see top Arduino code file)
* Note: Before uploading the code you need to make 1 change in the Adafruit_DotStar.h library (due to incompatibility new ATmega4809 chip): 
    * Adafruit_DotStar.cpp --> Comment line 257: //#define SPI_PIPELINE.