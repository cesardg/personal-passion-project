
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
String mode;

// led mapping
int A[] = {242, 241, 224, 225, 226, 227, 228, 202, 203, 240, 243, 223, 221, 222, 207, 208, 209, 210, 211, 179, 180, 181, 165, 166, 167, 131, 132, 133, 134, 164, 163, 135, 136, 162, 161, 160, 159, 158, 157, 156, 190, 200, 201, 204, 188, 189, 141, 142, 140, 139, 138, 137, 106, 104, 105, 85, 86, 113, 114, 115, 75, 76, 77, 53, 54, 55, 84, 46, 45, 44};
int B[] = {246, 220, 221, 245, 244, 243, 223, 222, 224, 242, 241, 225, 226, 227, 240, 239, 238, 237, 228, 229, 230, 231, 199, 200, 201, 189, 190, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 181, 209, 210, 180, 182, 208, 183, 184, 185, 186, 187, 188, 143, 142, 141, 105, 104, 103, 87, 86, 85, 45, 84, 46, 83, 47, 48, 82, 166, 132, 133, 134, 112, 113, 114, 76, 77, 78, 79, 80, 81, 49, 50, 51, 52, 53, 54};
int C[] = {238, 239, 227, 228, 229, 230, 200, 201, 202, 240, 241, 242, 243, 244, 222, 223, 224, 225, 226, 221, 220, 219, 211, 210, 209, 181, 180, 179, 167, 166, 165, 133, 132, 131, 115, 114, 113, 77, 76, 75, 78, 79, 80, 81, 82, 83, 84, 85, 86, 104, 105, 106, 46, 47, 48, 49, 50, 51, 52, 53};
int D[] = {246, 245, 244, 243, 242, 241, 240, 239, 238, 228, 229, 227, 226, 225, 224, 223, 222, 221, 220, 210, 209, 208, 182, 181, 180, 166, 165, 164, 134, 133, 132, 114, 113, 112, 78, 77, 76, 54, 53, 52, 51, 79, 80, 81, 82, 49, 50, 48, 47, 83, 46, 84, 85, 86, 230, 231, 199, 200, 201, 189, 190, 191, 155, 156, 157, 141, 142, 143, 103, 104, 105};
int E[] = {236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 78, 79, 80, 81, 82, 83, 84, 85, 86, 182, 183, 184, 185, 186, 187, 188, 158};
int F[] = {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 211, 210, 209, 179, 180, 181, 182, 183, 184, 185, 186, 187, 167, 166, 165, 164, 163, 162, 161, 160, 159, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53};
int G[] = {245, 244, 243, 242, 241, 240, 239, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 203, 202, 201, 179, 180, 181, 167, 166, 165, 162, 161, 160, 159, 158, 157, 131, 132, 133, 136, 137, 138, 139, 140, 141, 115, 114, 113, 107, 106, 105, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 53, 52, 51, 50, 49, 48, 47};
int H[] = {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 140, 141, 142, 106, 105, 104, 84, 85, 86, 46, 45, 44, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53};
int I[] = {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 206, 205, 204, 184, 185, 186, 162, 161, 160, 136, 137, 138, 110, 109, 108, 80, 81, 82, 54, 53, 52, 75, 55, 76, 77, 78, 79, 51, 50, 49, 48, 83, 84, 85, 86, 47, 46, 45, 44};
int J[] = {239, 238, 237, 227, 228, 229, 203, 202, 201, 187, 188, 189, 159, 158, 157, 139, 140, 141, 107, 106, 105, 83, 130, 131, 132, 116, 115, 114, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84, 85, 53, 52, 51, 50, 49, 48};
int K[] = {246, 245, 244, 238, 237, 236, 220, 221, 222, 226, 227, 228, 229, 210, 209, 208, 206, 205, 204, 203, 180, 181, 182, 183, 184, 185, 166, 165, 164, 163, 162, 132, 133, 134, 135, 136, 137, 114, 113, 112, 110, 109, 108, 107,76,  77, 78, 82, 83, 84, 85, 46, 45, 44, 54, 53, 52};
int L[] = {246, 245, 244, 220, 221, 222, 210, 209, 208, 180, 181, 182, 166, 165, 164, 132, 133, 134, 114, 113, 112, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44};
int M[] = {247, 246, 245, 238, 237, 236, 219, 220, 221, 222, 223, 226, 227, 228, 229, 230, 211, 210, 209, 208, 207, 206, 205, 204, 203, 202, 201, 200, 179, 180, 181, 184, 185, 188, 189, 190, 167, 166, 165, 131, 132, 133, 115, 114, 113, 75, 76, 77, 55, 54, 53, 158, 157, 156, 140, 141, 142, 106, 105, 104, 84, 85, 86, 46, 45, 44};
int N[] = {246, 245, 244, 238, 237, 236, 220, 221, 222, 223, 228, 229, 230, 210, 209, 208, 207, 206, 202, 201, 200, 180, 181, 182, 183, 184, 185, 188, 189, 190, 166, 165, 164, 162, 161, 160, 158, 157, 156, 132, 133, 134, 137, 138, 139, 140, 141, 142, 114, 113, 112, 108, 107, 106, 105, 104, 83, 84, 85, 86, 76, 77, 78, 54, 53, 52, 46, 45, 44};
int O[] = {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 179, 180, 181, 167, 166, 165, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 86, 202, 201, 200, 188, 189, 190, 158, 157, 156, 140, 141, 142, 106, 105, 104, 53, 52, 51, 50, 49, 48, 47};
int P[] = {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 210, 209, 208, 201, 200, 199, 189, 180, 181, 182, 190, 191, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 114, 113, 112, 76, 77, 78, 54, 53, 52};
int Q[] = {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 179, 180, 181, 202, 201, 200, 188, 189, 190, 158, 157, 156, 167, 166, 165, 131, 132, 133, 140, 141, 142, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 106, 105, 104, 53, 52, 51, 50, 49, 48, 47, 46, 45, 86, 44, 107, 108, 109, 110, 137, 136};
int R[] = {246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 210, 209, 208, 201, 200, 199, 180, 181, 182, 189, 190, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 132, 133, 134, 137, 138, 139, 114, 113, 112, 107, 106, 105, 76, 77, 78, 85, 86, 87, 54, 53, 52, 45, 44, 43};
int S[] = {245, 244, 243, 242, 241, 240, 239, 238, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 211, 210, 209, 180, 181, 202, 201, 200, 188, 189, 190, 182, 183, 184, 185, 164, 163, 162, 161, 160, 159, 138, 139, 140, 141, 106, 105, 104, 84, 85, 86, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 53, 52, 51, 50, 49, 48, 47, 46};
int T[] = {247, 246, 245, 244, 243, 242, 241, 240, 239, 238, 237, 236, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 207, 206, 205, 204, 183, 184, 185, 186, 163, 162, 161, 160, 135, 136, 137, 138, 111, 110, 109, 108, 79, 80, 81, 82, 51, 50, 49, 48};
int U[] = {247, 246, 245, 219, 220, 221, 211, 210, 209, 179, 180, 181, 167, 166, 165, 131, 132, 133, 115, 114, 113, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 52, 51, 50, 49, 48, 47, 46, 112, 238, 237, 236, 228, 229, 230, 202, 201, 200, 188, 189, 190, 158, 157, 156, 140, 141, 142, 106, 105, 104, 107};
int V[] = {247, 246, 245, 238, 237, 236, 219, 220, 221, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 167, 166, 165, 188, 189, 190, 158, 157, 156, 131, 132, 133, 140, 141, 142, 114, 113, 112, 111, 108, 107, 106, 105, 77, 78, 79, 80, 81, 82, 83, 84, 51, 50, 49, 48};
int W[] = {247, 246, 245, 219, 220, 221, 238, 237, 236, 228, 229, 230, 211, 210, 209, 202, 201, 200, 179, 180, 181, 188, 189, 190, 167, 166, 165, 158, 157, 156, 131, 132, 133, 140, 141, 142, 136, 137, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 75, 76, 77, 78, 83, 84, 85, 86, 55, 54, 53, 46, 45, 44};

int alp[] = {A, B,C, D, E, F, G ,H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W};

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

  if (Firebase.getString(firebaseData, treeId + "/message/")) { 
    previousMessage = firebaseData.stringData();
    Serial.println(previousMessage);
  }
}
 
void loop() {
  if (Firebase.getString(firebaseData, treeId + "/mode/")) { 
    mode = firebaseData.stringData();
  }

  if (mode == "message"){
     listeningForMessages();
  }
  

}

void listeningForMessages(){
   if (Firebase.getString(firebaseData, treeId + "/message/")) { 
      if (previousMessage != firebaseData.stringData()) {
        mapMessageInLeds(firebaseData.stringData());
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Message:");
        lcd.setCursor(0,1);
        lcd.print(firebaseData.stringData());
      }
    previousMessage = firebaseData.stringData();
     
  }
 delay(1000);
 }

 

// wordt getriggered als er een nieuwe message binnenkomt en print het in de Serial monitor
 void mapMessageInLeds(String message){
  Serial.println(message);
  //hello

  //omzetten in char array
  message.toUpperCase();
  int str_len = message.length() + 1;
  char char_array[str_len];
  
  message.toCharArray(char_array, str_len);

  
  //Serial.println(char_array);

  for (int i=0; i<str_len; i++) {
      Serial.println(int(char_array[i]));

      int index = int(char_array[i]) - 65;

      Serial.println(alp[index]);
      
  
  }
 
      
  
 }










 
