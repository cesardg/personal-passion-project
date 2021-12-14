
#include <Firebase_Arduino_WiFiNINA.h>
#include <Adafruit_DotStar.h>
#include <SPI.h>
#include <Arduino_LSM6DS3.h> 
#include <DHT.h> 
#include <Servo.h>       

// Firebase 
#define FIREBASE_HOST "arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "WCkUg3iFB4NRbBHg2IXc0bsosgHo5kM5bXmUvZie"
#define WIFI_SSID "iPhone van Cesar"
#define WIFI_PASSWORD "not so safe 123"

// DotStar ledstrip
#define NUMPIXELS 300
#define DATAPIN    4
#define CLOCKPIN   8

// temperature sensor
#define DHTPIN 7   
#define DHTTYPE DHT11

String treeId = "/Rudolph-A3EpYEF7zU";
String jsonStr;
String previousMessage;
String mode;

int pirInputPin = 2;               
int pirState = LOW;    
int pirVal = 0;  
int count = 0;

bool attackedByCat = false;

float previousHum;    
float previousTemp;   

int alfabed[][90]= {
/* A */ {242, 241, 224, 225, 226, 227, 228, 202, 203, 240, 243, 223, 221, 222, 207, 208, 209, 210, 211, 179, 180, 181, 165, 166, 167, 131, 132, 133, 134, 164, 163, 135, 136, 162, 161, 160, 159, 158, 157, 156, 190, 200, 201, 204, 188, 189, 141, 142, 140, 139, 138, 137, 106, 104, 105, 85, 86, 113, 114, 115, 75, 76, 77, 53, 54, 55, 84, 46, 45, 44}, 
/* B */ {246, 220, 221, 245, 244, 243, 223, 222, 224, 242, 241, 225, 226, 227, 240, 239, 238, 237, 228, 229, 230, 231, 199, 200, 201, 189, 190, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 181, 209, 210, 180, 182, 208, 183, 184, 185, 186, 187, 188, 143, 142, 141, 105, 104, 103, 87, 86, 85, 45, 84, 46, 83, 47, 48, 82, 166, 132, 133, 134, 112, 113, 114, 76, 77, 78, 79, 80, 81, 49, 50, 51, 52, 53, 54},
/* C */ {238, 239, 227, 228, 229, 230, 200, 201, 202, 240, 241, 242, 243, 244, 222, 223, 224, 225, 226, 221, 220, 219, 211, 210, 209, 181, 180, 179, 167, 166, 165, 133, 132, 131, 115, 114, 113, 77, 76, 75, 78, 79, 80, 81, 82, 83, 84, 85, 86, 104, 105, 106, 46, 47, 48, 49, 50, 51, 52, 53},
/* D */ {246, 245, 244, 243, 242, 241, 240, 239, 238, 228, 229, 227, 226, 225, 224, 223, 222, 221, 220, 210, 209, 208, 182, 181, 180, 166, 165, 164, 134, 133, 132, 114, 113, 112, 78, 77, 76, 54, 53, 52, 51, 79, 80, 81, 82, 49, 50, 48, 47, 83, 46, 84, 85, 86, 230, 231, 199, 200, 201, 189, 190, 191, 155, 156, 157, 141, 142, 143, 103, 104, 105}, 
/* E */ {236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 78, 79, 80, 81, 82, 83, 84, 85, 86, 182, 183, 184, 185, 186, 187, 188, 158}, 
/* F*/ {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 182, 183, 184, 185, 186, 187, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53}, 
/* G */ {245, 244, 243, 242, 241, 240, 239, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 203, 202, 201, 179, 180, 181, 167, 166, 165, 162, 161, 160, 159, 158, 157, 131, 132, 133, 136, 137, 138, 139, 140, 141, 115, 114, 113, 107, 106, 105, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 53, 52, 51, 50, 49, 48, 47},
/* H */ {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 140, 141, 142, 106, 105, 104, 84, 85, 86, 46, 45, 44, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53}, 
/* I */ {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 206, 205, 204, 184, 185, 186, 162, 161, 160, 136, 137, 138, 110, 109, 108, 80, 81, 82, 54, 53, 52, 75, 55, 76, 77, 78, 79, 51, 50, 49, 48, 83, 84, 85, 86, 47, 46, 45, 44}, 
/* J */ {239, 238, 237, 227, 228, 229, 203, 202, 201, 187, 188, 189, 159, 158, 157, 139, 140, 141, 107, 106, 105, 83, 130, 131, 132, 116, 115, 114, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 53, 52, 51, 50, 49, 48}, 
/* K */ {246, 245, 244, 238, 237, 236, 220, 221, 222, 226, 227, 228, 229, 210, 209, 208, 206, 205, 204, 203, 180, 181, 182, 183, 184, 185, 166, 165, 164, 163, 162, 132, 133, 134, 135, 136, 137, 114, 113, 112, 110, 109, 108, 107,76,  77, 78, 82, 83, 84, 85, 46, 45, 44, 54, 53, 52}, 
/* L */ {246, 245, 244, 220, 221, 222, 210, 209, 208, 180, 181, 182, 166, 165, 164, 132, 133, 134, 114, 113, 112, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44},
/* M */ {247, 246, 245, 238, 237, 236, 219, 220, 221, 222, 223, 226, 227, 228, 229, 230, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 179, 180, 181, 184, 185, 188, 189, 190, 167, 166, 165, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53, 158, 157, 156, 140, 141, 142, 106, 105, 104, 84, 85, 86, 46, 45, 44},
/* N */ {246, 245, 244, 238, 237, 236, 220, 221, 222, 223, 228, 229, 230, 210, 209, 208, 207, 206, 202, 201, 200, 180, 181, 182, 183, 184, 185, 188, 189, 190, 166, 165, 164, 162, 161, 160, 158, 157, 156, 132, 133, 134, 137, 138, 139, 140, 141, 142, 114, 113, 112, 108, 107, 106, 105, 104, 83, 84, 85, 86, 76, 77, 78, 54, 53, 52, 46, 45, 44},
/* O */ {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 179, 180, 181, 167, 166, 165, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 202, 201, 200, 188, 189, 190, 158, 157, 156, 140, 141, 142, 106, 105, 104, 53, 52, 51, 50, 49, 48, 47},
/* P */ {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 210, 209, 208, 201, 200, 199, 189, 180, 181, 182, 190, 191, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 114, 113, 112, 76, 77, 78, 54, 53, 52},
/* Q */ {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 179, 180, 181, 202, 201, 200, 188, 189, 190, 158, 157, 156, 167, 166, 165, 131, 132, 133, 140, 141, 142, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 106, 105, 104, 53, 52, 51, 50, 49, 48, 47, 46, 45, 86, 44, 107, 108, 109, 110, 137, 136},
/* R */ {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 210, 209, 208, 201, 200, 199, 180, 181, 182, 189, 190, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 132, 133, 134, 137, 138, 139, 114, 113, 112, 107, 106, 105, 76, 77, 78, 85, 86, 87, 54, 53, 52, 45, 44, 43},
/* S */ {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 180, 181, 202, 201, 200, 188, 189, 190, 182, 183, 184, 185, 164, 163, 162, 161, 160, 159, 138, 139, 140, 141, 106, 105, 104, 84, 85, 86, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 53, 52, 51, 50, 49, 48, 47, 46},
/* T */ {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 207, 206, 205, 204, 183, 184, 185, 186, 163, 162, 161, 160, 135, 136, 137, 138, 111, 110, 109, 108, 79, 80, 81, 82, 51, 50, 49, 48},
/* U */ {247, 246, 245, 219, 220, 221, 211, 210, 209, 179, 180, 181, 167, 166, 165, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 52, 51, 50, 49, 48, 47, 46, 112, 238, 237, 236, 228, 229, 230, 202, 201, 200, 188, 189, 190, 158, 157, 156, 140, 141, 142, 106, 105, 104, 107},
/* V */ {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 167, 166, 165, 188, 189, 190, 158, 157, 156, 131, 132, 133, 140, 141, 142, 114, 113, 112, 111, 108, 107, 106, 105, 77, 78, 79, 80, 81, 82, 83, 84, 51, 50, 49, 48},
/* W */ {247, 246, 245, 219, 220, 221, 238, 237, 236, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 188, 189, 190, 167, 166, 165, 158, 157, 156, 131, 132, 133, 140, 141, 142, 136, 137, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 75, 76, 77, 78, 83, 84, 85, 86, 55, 54, 53, 46, 45, 44},
/* X */ {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 210, 209, 208, 207, 204, 203, 202, 201, 182, 183, 184, 185, 186, 187, 164, 163, 162, 161, 160, 159, 132, 133, 134, 135, 138, 139, 140, 141, 115, 114, 113, 75, 76, 77, 55, 54, 53, 106, 105, 104, 84, 85, 86, 46, 45, 44},
/* Y */ {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 180, 181, 182, 187, 188, 189, 165, 164, 163, 162, 161, 160, 159, 158, 136, 137, 110, 109, 80, 81, 50, 49, 135, 138, 111, 108, 79, 82, 51, 48, 183, 186},
/* Z */ {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 204, 203, 202, 184, 185, 186, 164, 163, 162, 133, 134, 135, 114, 113, 112, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44},
};

int numbers[][90]= {
 /* 0 */ {244, 243, 242, 241, 240, 239, 221, 222, 223, 224, 225, 226, 227, 228, 211, 210, 209, 202, 201, 200, 179, 180, 181, 188, 189, 190, 167, 166, 165, 158, 157, 156, 131, 132, 133, 140, 141, 142, 115, 114, 113, 106, 105, 104, 77, 78, 79, 80, 81, 82, 83, 84, 52, 51, 50, 49, 48, 47, 184, 185, 162, 161, 136, 137}, 
 /* 1 */ {241, 240, 239, 223, 224, 225, 226, 227, 209, 208, 207, 206, 205, 204, 203, 179, 180, 181, 182, 185, 186, 187, 167, 166, 165, 161, 160, 159, 137, 138, 139, 109, 108, 107, 81, 82, 83, 49, 48, 47},
 /* 2 */ {244, 243, 242, 241, 240, 239, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 202, 201, 200, 188, 189, 187, 179, 180, 181, 162, 161, 160, 159, 135, 136, 137, 138, 113, 112, 111, 110, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45},
 /* 3 */ {244, 243, 242, 241, 240, 239, 238, 221, 222, 223, 224, 225, 226, 227, 228, 229, 202, 201, 200, 210, 209, 208, 188, 189, 184, 185, 186, 187, 162, 161, 160, 159, 158, 157, 140, 141, 142, 106, 105, 104, 114, 113, 112, 77, 78, 79, 80, 81, 82, 83, 84, 85, 52, 51, 50, 49, 48, 47},
 /* 4 */ {240, 239, 238, 226, 227, 228, 224, 225, 208, 207, 206, 204, 203, 202, 180, 181, 182, 186, 187, 188, 168, 167, 166, 160, 159, 158, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 108, 107, 106, 82, 83, 84, 48, 47, 46},
 /* 5 */ {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 210, 209, 208, 180, 181, 182, 183, 184, 185, 186, 187, 188, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 139, 140, 141, 107, 106, 105, 76, 77, 78, 79, 80, 81, 82, 83, 84, 53, 52, 51, 50, 49, 48, 47},
 /* 6 */ {238, 244, 243, 242, 241, 240, 239, 221, 222, 223, 224, 225, 226, 227, 228, 229, 210, 209, 208, 202, 201, 200, 180, 181, 182, 183, 184, 185, 186, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 140, 141, 142, 132, 133, 134, 114, 113, 112, 77, 78, 79, 80, 81, 82, 83, 84, 85, 106, 105, 104, 52, 51, 50, 49, 48, 47, 46},
 /* 7 */ {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 203, 202, 201, 186, 187, 188, 161, 160, 159, 136, 137, 138, 111, 110, 109, 79, 80, 81, 51, 50},
 /* 8 */ {244, 243, 242, 241, 240, 239, 221, 222, 220, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 202, 201, 200, 180, 181, 188, 189, 159, 160, 161, 162, 163, 164, 133, 132, 140, 141, 106, 105, 104, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 52, 51, 50, 49, 48, 47},
 /* 9 */ {244, 243, 242, 241, 240, 239, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 203, 202, 201, 179, 180, 181, 187, 188, 189, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 139, 140, 141, 107, 106, 105, 83, 84, 115, 114, 75, 76, 77, 78, 79, 80, 81, 82, 53, 52, 51, 50, 49, 48}
 };

 int specialChars[][50]= {
 /* ? */ {244, 243, 242, 241, 240, 239, 221, 222, 223, 226, 227, 228, 210, 209, 208, 203, 202, 201, 187, 188, 189, 160, 159, 161, 136, 137, 138, 80, 81, 82, 50, 49, 48, 224, 225}, 
 /* ! */ {242, 241, 240, 243, 223, 224, 225, 226, 207, 206, 205, 204, 183, 184, 185, 186, 163, 162, 161, 160, 135, 136, 137, 138, 51, 50, 49, 48, 79, 80, 81, 82},
 /* - */ {166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141}
 };


FirebaseData firebaseData;
FirebaseData stream;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BGR);
Servo servo1; 
 
void setup() {

  Serial.begin(9600);
  delay(1000);

  // init led strip
  
  //strip.begin(); // Initialize pins for output
  //strip.show();  // Turn all LEDs off ASAP

  //showLedPatternFullGreen();
  
  Serial.print("Connecting to WiFi…");
// wifi connecting...
  int status = WL_IDLE_STATUS;

  // holds everything until Wifi is connected
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }

  // wifi is connected
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);


  // subscribe on message mode (simular to onvalue change)
  if (Firebase.beginStream(stream, treeId + "/mode/" )){
   Serial.println("suscribed on mode");
 }

 
  if (Firebase.getString(firebaseData, treeId + "/message/")) { 
    previousMessage = firebaseData.stringData();
  }

  // init gyro for cat attack detector
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }


  // init temperature
  dht.begin();
  previousTemp= dht.readTemperature();
  previousHum = dht.readHumidity();  
  Firebase.setFloat(firebaseData, treeId  + "/roomTemp/", previousTemp); 
  Firebase.setFloat(firebaseData, treeId  + "/roomHumidity/", previousHum);

  //PIR sensor
   pinMode(pirInputPin, INPUT); 

   //servo 
    servo1.attach(11);
 
}
 
void loop() {

 if (!Firebase.readStream(stream)){Serial.println("Can't read stream, "+ stream.errorReason());}
 if (stream.streamTimeout()){Serial.println("Stream timed out, resuming..."); }

  if (stream.streamAvailable())
  {
    count++;
    if (stream.dataType() == "null")
      count = 0;
    mode = stream.stringData();
  }

  if (mode == "message"){
     listeningForMessages();

     //and back to normal;
     //showLedPatternFullGreen();
  }


  if (mode == "drawing"){
     showDrawing();
  }

// only works in idle mode to save computational power for other tasks. 
  if (mode == "idle"){
      detectCatAttack();
      detectIntruder();
      getTemperature();
  }

}

void detectIntruder (){
    pirVal = digitalRead(pirInputPin);  
  if (pirVal == HIGH) {            
    if (pirState == LOW) {
      Firebase.setBool(firebaseData, treeId  + "/intruderDetection/detected/", true);
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){
      pirState = LOW;
    }
  }
  
}

void getTemperature (){

    if (previousTemp != dht.readTemperature()){
    Firebase.setFloat(firebaseData, treeId  + "/roomTemp/", dht.readTemperature());
  }

  if (previousHum != dht.readHumidity()){
    Firebase.setFloat(firebaseData, treeId  + "/roomHumidity/", dht.readHumidity());
  }   

  previousHum = dht.readHumidity();  
  previousTemp= dht.readTemperature(); 
}

void detectCatAttack(){
   float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    
    if (abs(x) > 30 || abs(y) > 30 || abs(z) > 30){

      //if change in tilt is detected, send to db
      attackedByCat = true;
      Firebase.setBool(firebaseData, treeId + "/catAttackDetection/detected/", attackedByCat);
      Firebase.setTimestamp(firebaseData, treeId + "/catAttackDetection/time/");

      // for now, reset it after 5s
      delay(5000);
      attackedByCat = false;
    } else {
      attackedByCat = false;
    }
  }
}

// shows drawing in leds
void showDrawing(){

    String strsLed[100];
    int StringCountLed = 0;
    String strsColor[100];
    int StringCountColor = 0;


    if (Firebase.getString(firebaseData, treeId + "/drawing/litLightsOnlyIndex/")) { 
        Serial.println("huh");
          String str1 = {firebaseData.stringData()};

                     // Split the string into substrings
            while (str1.length() > 0)
            {
              int index = str1.indexOf(' ');
              if (index == -1) // No space found
              {
                strsLed[StringCountLed++] = str1;
                break;
              }
              else
              {
                strsLed[StringCountLed++] = str1.substring(0, index);
                str1 = str1.substring(index+1);
              }
            }
          
      delay(20);

         
     }

    if (Firebase.getString(firebaseData, treeId + "/drawing/litLightsOnlyColor/")) { 
          String str = {firebaseData.stringData()};
                Serial.println("huh2");

            while (str.length() > 0)
            {
              int index = str.indexOf(' ');
              if (index == -1) // No space found
              {
                strsColor[StringCountColor++] = str;
                break;
              }
              else
              {
                strsColor[StringCountColor++] = str.substring(0, index);
                str = str.substring(index+1);
              }
            }
          
      delay(20);
     }

      Serial.println(strsLed[0]);
       Serial.println(strsColor[0]);
       
      delay(3000);
    Firebase.setString(firebaseData, treeId  + "/mode/", "idle");
    
   
}

 // when new message is detected
void listeningForMessages(){
   if (Firebase.getString(firebaseData, treeId + "/message/")) { 
      if (previousMessage != firebaseData.stringData()) {
        playRingtoneServo();
        mapMessageInLeds(firebaseData.stringData());
      }
    previousMessage = firebaseData.stringData();
  }
 delay(1000);

 //set mode back to idle
  Firebase.setString(firebaseData, treeId  + "/mode/", "idle");
 }

 
  // string message to led array
 void mapMessageInLeds(String message){


  //led uit zetten 
  //strip.clear();
  
  Serial.println(message);
  message.toUpperCase();
  int messageLenght = message.length() + 1;
  char messageArray[messageLenght];
  
  message.toCharArray(messageArray, messageLenght);

  for (int i=0; i<messageLenght-1; i++) {
      //search for ASCII number and substract it with 65
      int index = int(messageArray[i]);
      Serial.println(index);
      Serial.print("These leds needs to be on for ");
      Serial.print(messageArray[i]);
      Serial.print(": ");

      if ((index >=65) && (index<= 90)) {
        
      //loop over alfabed
      
        for (int j =0; j < 90; j++) {
          if (alfabed[index- 65][j] != 0 && alfabed[index- 65][j] > 0 && alfabed[index- 65][j] < 300 ){
          //strip.setPixelColor(alfabed[index- 65][j], 0x00FF00);
          Serial.print(alfabed[index- 65][j]);
          Serial.print("-");
          } 
        }
        
      } else if (index == 63){
       
         //loop over special chars (?!-)
         for (int j =0; j < 50; j++) {
          if (specialChars[0][j] != 0 && specialChars[0][j] > 0 && specialChars[0][j] < 300 ){
          //strip.setPixelColor(specialChars[0][j], 0x00FF00);
          Serial.print(specialChars[0][j]);
          Serial.print("-");
          } 
        }
        
        
      }  else if (index == 33){
       
         //loop over special chars (?!-)
         for (int j =0; j < 50; j++) {
          if (specialChars[1][j] != 0 && specialChars[1][j] > 0 && specialChars[1][j] < 300 ){
          //strip.setPixelColor(specialChars[1][j], 0x00FF00);
          Serial.print(specialChars[1][j]);
          Serial.print("-");
          } 
        }
        
        
      }else if (index == 45 || index == 32){
       
         //loop over special chars (?!-)
         for (int j =0; j < 50; j++) {
          if (specialChars[2][j] != 0 && specialChars[2][j] > 0 && specialChars[2][j] < 300 ){
          //strip.setPixelColor(specialChars[2][j], 0x00FF00);
          Serial.print(specialChars[2][j]);
          Serial.print("-");
          } 
        }
        
      }else if ((index >=48) && (index<= 57)){
        
             //loop over number

         for (int j =0; j < 90; j++) {
          if (numbers[index- 48][j] != 0 && numbers[index- 48][j] > 0 && numbers[index- 48][j] < 300 ){
          //strip.setPixelColor(numbers[index- 48][j], 0x00FF00);
          Serial.print(numbers[index- 48][j]);
          Serial.print("-");
         } 
        
      }

      }
      
      //strip.show(); 
      Serial.println();
      delay(500);
      //strip.clear();
  }
 }

 void playRingtoneServo () {
    servo1.write(10);
    delay(1000);
    servo1.write(170);
    delay(1000);
    servo1.write(10);
 }

 void showLedPatternFullGreen () {
  strip.fill(0x00FF00, 0, 300);
  strip.setBrightness(40);
  strip.show();
 }



 
