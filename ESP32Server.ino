
//Libraries
#include <WiFi.h>
#include <FirebaseESP32.h>


//Firebase Host
#define FIREBASE_HOST "water-tanks-4d7d4-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "qpaFzh6lk60lzd39EzSXy83rLJXAkMp2RUjhalv3"

//Wifi with Name and passowrd.
#define WIFI_SSID "amjad"
#define WIFI_PASSWORD "ebda3@2013"

//firebase Keys paths.
FirebaseData firebaseData;
#define switchOnePath "data/switchOne"
#define switchTwoPath "data/switchTwo"
#define manualPath  "data/manual"
#define autoPath  "data/auto"
#define waterLevelPath "data/waterLevel"



bool auto_ = true;
bool manual = false;
bool switchOne = false;
bool switchTwo = false;
int level = 0;

void establishingConnection() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());
}

void establishingConnectionWithFirbase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
} 



void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  Serial2.begin(115200);
  establishingConnection();
  establishingConnectionWithFirbase();
}
void loop() {
  if (Serial1.available()) {
     Data = Serial1.readString();
    Serial.println(Data);
    Serial1.flush();
    level = Data.toInt();
  }
  
  setWaterLeveL(level);
  auto_ = getAutoValue();
  manual = getManualValue();
  switchOne = getSwitchOneValue();
  switchTwo = getSwitchTwoValue();
  Serial2(String(switchOne)+ String(switchTwo)+ String(auto_) + String(manual)));
  printData();
}


void printData(){
  Serial.print("auto: ");
  Serial.println(auto_);
  Serial.print("manual: ");
  Serial.println(manual);
  Serial.print("switchOne: ");
  Serial.println(switchOne);
  Serial.print("switchTwo: ");
  Serial.println(switchTwo);
 }

void setWaterLeveL(double level){
    Firebase.setInt(firebaseData,waterLevelPath, level);
}


int getSwitchOneValue() {
  if (Firebase.getBool(firebaseData, switchOnePath)) {
    return firebaseData.boolData();
  }
}

int getSwitchTwoValue() {
    if (Firebase.getBool(firebaseData, switchTwoPath)) {
    return firebaseData.boolData();
  }
}

int getManualValue() {
  if (Firebase.getBool(firebaseData, manualPath)) {
    return firebaseData.boolData();
  }
}


int getAutoValue() {  
  if (Firebase.getBool(firebaseData, autoPath)) {
    return firebaseData.boolData();
  }
}
