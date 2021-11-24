 /*
 Project: Send Data to Firebase Using Arduino Uno WiFi Rev2
 Board: Arduino Uno WiFi Rev2
 
 External libraries:
 – Arduino_LSM6DS3 by Arduino V1.0.0
 – Firebase Arduino based on WiFiNINA by Mobizt V1.1.4
 */
 
#include <Arduino_LSM6DS3.h>
#include <Firebase_Arduino_WiFiNINA.h>
 
#define FIREBASE_HOST "arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "WCkUg3iFB4NRbBHg2IXc0bsosgHo5kM5bXmUvZie"
#define WIFI_SSID "iPhone van Cesar"
#define WIFI_PASSWORD "not so safe 123"
 
FirebaseData firebaseData;
 
String path = "/test";
String jsonStr;
 
void setup()
{
 Serial.begin(9600);
 delay(1000);
 Serial.println();
 
 Serial.print("Initialize IMU sensor…");
 if (!IMU.begin()) {
 Serial.println(" failed!");
 while (1);
 }
 Serial.println(" done");
 Serial.print("Accelerometer sample rate = ");
 Serial.print(IMU.accelerationSampleRate());
 Serial.println(" Hz");
 
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
 
void loop()
{
 float x, y, z;
 
 // Read IMU acceleration data
 if (IMU.accelerationAvailable()) {
 IMU.readAcceleration(x, y, z);
 
 // Send data to Firebase with specific path
 if (Firebase.setFloat(firebaseData, path + "/gyro-values/X-axis", x)) {
 Serial.println(firebaseData.dataPath() + " = " + x);
 }
 if (Firebase.setFloat(firebaseData, path + "/gyro-values/Y-axis", y)) {
 Serial.println(firebaseData.dataPath() + " = " + y);
 }
 if (Firebase.setFloat(firebaseData, path + "/gyro-values/Z-axis", z)) {
 Serial.println(firebaseData.dataPath() + " = " + z);
 }


  if (Firebase.getString(firebaseData, path + "/messages/message")) // also can use Firebase.get(fbdo, path)
  {
    Serial.println("ok");
    Serial.println("path: " + firebaseData.dataPath());
    Serial.println("type: " + firebaseData.dataType());
    Serial.print("value: ");
    if (firebaseData.dataType() == "int")
      Serial.println(firebaseData.intData());
    if (firebaseData.dataType() == "int64")
      Serial.println(firebaseData.int64Data());
    if (firebaseData.dataType() == "uint64")
      Serial.println(firebaseData.uint64Data());
    else if (firebaseData.dataType() == "double")
      Serial.println(firebaseData.doubleData());
    else if (firebaseData.dataType() == "float")
      Serial.println(firebaseData.floatData());
    else if (firebaseData.dataType() == "boolean")
      Serial.println(firebaseData.boolData() == 1 ? "true" : "false");
    else if (firebaseData.dataType() == "string")
      Serial.println(firebaseData.stringData());
    else if (firebaseData.dataType() == "json")
      Serial.println(firebaseData.jsonData());
    else if (firebaseData.dataType() == "array")
      Serial.println(firebaseData.arrayData());
  }
 
 // Push data using pushJSON
 jsonStr = "{\"X\":" + String(x,6) + ",\"Y\":" + String(y,6) + ",\"Z\":" + String(z,6) + "}";
 
 if (Firebase.pushJSON(firebaseData, path + "/gyroJSON", jsonStr)) {
 Serial.println(firebaseData.dataPath() + " = " + firebaseData.pushName());
 }
 else {
 Serial.println("Error: " + firebaseData.errorReason());
 }
 
 Serial.println();
 delay(5000);
 }
}
