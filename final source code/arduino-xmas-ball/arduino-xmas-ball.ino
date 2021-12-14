
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
int count = 0;

FirebaseData firebaseData;
FirebaseData stream;
 
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


  if (Firebase.beginStream(stream, treeId + "/mode/" )){
   Serial.println("test1");
 }
}
 
void loop() {
  detectShakeBall();

 if (!Firebase.readStream(stream))
  {
    Serial.println("Can't read stream, "+ stream.errorReason());
  }

  if (stream.streamTimeout())
  {
    Serial.println("Stream timed out, resuming...");
  }

  if (stream.streamAvailable())
  {
    count++;
    if (stream.dataType() == "null")
      count = 0;

    Serial.println("Stream data received... ");
    Serial.println(stream.stringData());
    showDrawing();
  }



  
}

void detectShakeBall(){
  float x, y, z;
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
    
    if (abs(x) > 30 || abs(y) > 30 || abs(z) > 30){

      //if change in tilt is detected, send to db
      Firebase.setBool(firebaseData, treeId  + "/users/0/ballIsShaked/", true);
      Firebase.setTimestamp(firebaseData, treeId + "/users/0/time/");
      

      //show red light as feedback
      WiFiDrv::pinMode(25, OUTPUT);
      WiFiDrv::analogWrite(26, LOW); 
      WiFiDrv::analogWrite(25, 128); 

      // for now, reset it after 5s
      delay(5000);

      Firebase.setBool(firebaseData, treeId  + "/users/0/ballIsShaked/", false);

      // show green light again
      WiFiDrv::pinMode(26, OUTPUT);  
      WiFiDrv::analogWrite(25, LOW); 
      WiFiDrv::analogWrite(26, 128); 
    } 
  }
  delay(500);
}


void showDrawing(){

  // Somehow you can only fetch 25 items max from an array
    Serial.println("showdrawing");
    if (Firebase.getArray(firebaseData, treeId + "/lights")) { 
          Serial.println("begin");
          Serial.println(firebaseData.arrayData());
          Serial.println("einde");
  }
  delay(5000);
}
