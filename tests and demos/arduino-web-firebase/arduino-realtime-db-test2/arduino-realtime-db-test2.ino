
#include <Firebase_Arduino_WiFiNINA.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

 
#define FIREBASE_HOST "arduino-wi-fi-xmas-tree-db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "WCkUg3iFB4NRbBHg2IXc0bsosgHo5kM5bXmUvZie"
#define WIFI_SSID "iPhone van Cesar"
#define WIFI_PASSWORD "not so safe 123"
 

String treeId = "/Rudolph-A3EpYEF7zU";
String jsonStr;
String previousMessage;

// LCD pinout
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;

FirebaseData firebaseData;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
 
void setup() {
  Serial.begin(9600);
  delay(1000);
  
  lcd.begin(16,2);

    
  Serial.print("Connecting to WiFi…");
  lcd.setCursor(0,0);
  lcd.print("Wifi: connecting");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print(".");
    delay(300);
  }
  Serial.print(" IP: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.print("Wifi: connected");
  Serial.println();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, WIFI_SSID, WIFI_PASSWORD);
  Firebase.reconnectWiFi(true);

  lcd.setCursor(0,1);
  lcd.print("Waiting for msg...");

  if (Firebase.getString(firebaseData, treeId + "/messages/message")) { 
    previousMessage = firebaseData.stringData();
  }
}
 
void loop() {
 listeningForMessages();
}

void listeningForMessages(){
   if (Firebase.getString(firebaseData, treeId + "/messages/message")) { 
      if (previousMessage != firebaseData.stringData()) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Message:");
        lcd.setCursor(0,1);
        lcd.print(firebaseData.stringData());
        Serial.println(firebaseData.stringData());
      }
    previousMessage = firebaseData.stringData();
     
  }
 delay(1000);
 }
