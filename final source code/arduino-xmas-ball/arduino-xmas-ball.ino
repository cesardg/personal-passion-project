
#include <Firebase_Arduino_WiFiNINA.h>
#include <Arduino_LSM6DS3.h> 
#include <WiFiNINA.h> 
#include <utility/wifi_drv.h>
 
// Firebase 
#define FIREBASE_HOST "arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "WCkUg3iFB4NRbBHg2IXc0bsosgHo5kM5bXmUvZie"
#define WIFI_SSID "iPhone van Cesar"
#define WIFI_PASSWORD "not so safe 123"

String treeId = "/Rudolph-A3EpYEF7zU";

FirebaseData firebaseData;
 
void setup() {

  Serial.begin(9600);
  delay(1000);

  //show blue light
  WiFiDrv::pinMode(27, OUTPUT); 
  WiFiDrv::analogWrite(27, 128); 
  
  Serial.print("Connecting to WiFi…");
// wifi connecting...
  int status = WL_IDLE_STATUS;

  // holds everything until Wifi is connected
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }

  // wifi is connected, show green light
  WiFiDrv::pinMode(26, OUTPUT);  //GREEN
  WiFiDrv::analogWrite(27, LOW); 
  WiFiDrv::analogWrite(26, 128); 
  
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  // init gyro for shake detection
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

}
 
void loop() {
  detectShakeBall();
}

void detectShakeBall(){
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    
    if (abs(x) > 50 || abs(y) > 50 || abs(z) > 50){

      //if change in tilt is detected, send to db
      Firebase.setString(firebaseData, treeId  + "/mode/", "ball-shake" );

      //show red light as feedback
      WiFiDrv::pinMode(25, OUTPUT);
      WiFiDrv::analogWrite(26, LOW); 
      WiFiDrv::analogWrite(25, 128); 

      // for now, reset it after 1s
      delay(1000);
      Firebase.setString(firebaseData, treeId  + "/mode/", "idle" );

      delay(4000);
      // show green light again
      WiFiDrv::pinMode(26, OUTPUT);  
      WiFiDrv::analogWrite(25, LOW); 
      WiFiDrv::analogWrite(26, 128); 
    } 
  }
  delay(500);
}
