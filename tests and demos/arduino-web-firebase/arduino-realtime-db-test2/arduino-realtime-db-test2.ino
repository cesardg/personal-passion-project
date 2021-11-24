
#include <Firebase_Arduino_WiFiNINA.h>
 
#define FIREBASE_HOST "arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "WCkUg3iFB4NRbBHg2IXc0bsosgHo5kM5bXmUvZie"
#define WIFI_SSID "iPhone van Cesar"
#define WIFI_PASSWORD "not so safe 123"
 
FirebaseData firebaseData;
 
String treeId = "/Rudolph-A3EpYEF7zU";
String jsonStr;
 
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  
  Serial.print("Connecting to WiFi…");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);
}
 
void loop() {

  if (Firebase.getString(firebaseData, treeId + "/messages/message")) { 
    Serial.println(firebaseData.stringData()); 
 }
 

 Serial.println();
 delay(1000);
 
}
