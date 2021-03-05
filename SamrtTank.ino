int ON = 1;
int OFF = 0;
int auto_ = 1;
int manual = 0;
int switchOne = 1;
int switchTwo = 1; 
int minWatkerLeveL = 6;//cm
float waterlevel = 0.0; //cm
int tanklevel = 12; //cm
float duration, distance;
String data_ = "1110";

//ultrasonic sensor pins.
const int trigPin = 8;
const int echoPin = 10;

//relay pins
const int RELAY_PIN = 3;  // the Arduino pin, which connects to the IN pin of relay
const int RELAY_PIN_soleniod_A = 4;
const int RELAY_PIN_soleniod_B = 5;

void sendWaterLevel(double waterlevel){
  Serial1.print(String(waterlevel));
}

void updateSwitchsStatus(){
   if (Serial2.available()) {
    data_ = Serial2.readString();
    Serial.println(data_);
    Serial2.flush();
  }
}

void checkSwitchOneValue(){
  switchOne = String(data_[0]).toInt();
}

void checkSwitchTwoValue(){
  switchTwo =String(data_[1]).toInt();
}

void  checkAutoValue(){
  auto_ = String(data_[2]).toInt();
}


void  checkManualValue(){
  manual = String(data_[3]).toInt();
}

void turnOnSwithOne(){
Serial.println("Solenoid valve is ON");
digitalWrite(RELAY_PIN_soleniod_A,HIGH); 
}

void turnOFFSwithOne(){
Serial.println("Solenoid valve is OFF");
digitalWrite(RELAY_PIN_soleniod_A,LOW); 
}


void turnOnSwithTwo(){
  digitalWrite(RELAY_PIN_soleniod_B,HIGH);
  Serial.println("Solenoid valve is ON"); 
}

void turnOFFSwithTwo(){
digitalWrite(RELAY_PIN_soleniod_B,LOW);
Serial.println("Solenoid valve is OFF"); 
}

void checkWaterLeveL(){
  if(waterlevel<minWatkerLeveL && auto_ == ON){
      Serial.println("Pump is ON");
      turnOnPump();
      //callevel();
    }else{
        Serial.println("Pump is OFF");
        turnOFFPump();
    }
}


void turnOnPump(){
  digitalWrite(RELAY_PIN, HIGH);
}

void turnOFFPump(){
  digitalWrite(RELAY_PIN, LOW);
}
void callevel(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration*.0343)/2;
    waterlevel = tanklevel -  distance;
    Serial.print("Waterlevel: ");
    Serial.println(waterlevel);
    delay(1000);
  }

  void setup() {
  Serial1.begin(115200);
  Serial2.begin(115200);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RELAY_PIN_soleniod_A, OUTPUT);
  pinMode(RELAY_PIN_soleniod_B, OUTPUT);
}


void loop() {
   callevel();
   updateSwitchsStatus();
   checkSwitchOneValue();
   checkSwitchTwoValue();
   checkAutoValue();
   checkManualValue();
   checkWaterLeveL();
   delay(1000);
   sendWaterLevel(waterlevel);
   if(switchOne == ON){
      turnOnSwithOne(); 
   }else{
      turnOFFSwithOne();
   }
   if(switchTwo == ON){
      turnOnSwithTwo();
   }else{
      turnOFFSwithTwo();
   }
}
