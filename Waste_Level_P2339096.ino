#include <SoftwareSerial.h>

#define DEBUG true
#define ULTRASOUND1_TRIG A4
#define ULTRASOUND1_ECHO A3
#define ULTRASOUND2_TRIG A0
#define ULTRASOUND2_ECHO A1
#define DIP_SWITCH1_PIN 13
#define DIP_SWITCH2_PIN 12
#define DIP_SWITCH3_PIN 11
#define DIP_SWITCH4_PIN 10
#define RED_LED_PIN 6
#define GREEN_LED_PIN 7

int decimalNumber;
String ultrasound_1, ultrasound_2;
String apiKey = "XGFAAPCSS9CN7QCB"; // Write API key
String cmd = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";   //Send to Esp
SoftwareSerial ESP01(2, 3); // RX, TX

void esploop();
void checkWasteLevels();
String sendData(String command, const int timeout, boolean debug);
bool checkWasteFull(int trigPin, int echoPin, int pin, int sec);

void setup() {
  Serial.begin(115200);
  ESP01.begin(9600);

  pinMode(ULTRASOUND1_TRIG, OUTPUT);
  pinMode(ULTRASOUND1_ECHO, INPUT);
  pinMode(ULTRASOUND2_TRIG, OUTPUT);
  pinMode(ULTRASOUND2_ECHO, INPUT);
  pinMode(DIP_SWITCH1_PIN, INPUT);
  pinMode(DIP_SWITCH2_PIN, INPUT);
  pinMode(DIP_SWITCH3_PIN, INPUT);
  pinMode(DIP_SWITCH4_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  Serial.println("Starting...");
  sendData("AT+RST\r\n", 1000, DEBUG);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  sendData("AT+CWJAP=\"Yin Win\",\"14111973\"\r\n", 2000, DEBUG);  // Change these  "Yin Win\",\"14111973
  sendData("AT+CIPMUX=0\r\n", 1000, DEBUG);
}

void loop() {
  // Main loop 
  // Bin ID Check
 //  Serial.println("Getting Data from SWITCH.............");
  decimalNumber = (digitalRead(DIP_SWITCH1_PIN) * 8) + 
                      (digitalRead(DIP_SWITCH2_PIN) * 4) + 
                      (digitalRead(DIP_SWITCH3_PIN) * 2) + 
                      digitalRead(DIP_SWITCH4_PIN);
 // ..............................
  //Bin/Waste Level Check
 // Serial.println("Getting Data from Two ULTRASOUND SENSORS.............");
  checkWasteLevels();
  //..................................
  // Send ESP Data
  esploop();
}

void esploop(){
// SENDING ESP DATA over IOT
   //Send to Esp
  String cmd = "AT+CIPSTART=\"TCP\",\"184.106.153.149\",80\r\n";
  sendData(cmd, 2000, DEBUG);

  String getStr = "GET /update?api_key=" + apiKey + 
                  "&field1=" + ultrasound_1 + 
                  "&field2=" + ultrasound_2 + 
                  "&field3=" + String(decimalNumber) + "\r\n";

  ESP01.print("AT+CIPSEND=");
  ESP01.println(getStr.length());
  //delay(500);
  
  if (ESP01.find(">")) {
    sendData(getStr, 2000, DEBUG);
  }
  //..................................
}
void checkWasteLevels() {
  bool generalFull = checkWasteFull(ULTRASOUND1_TRIG, ULTRASOUND1_ECHO, 1,8);
  bool plasticFull = checkWasteFull(ULTRASOUND2_TRIG, ULTRASOUND2_ECHO, 2,8);
  Serial.print("generalFull , plasticFull:   ");Serial.print(generalFull); 
  Serial.print(" , ");Serial.println(plasticFull); 
  if (generalFull || plasticFull) {   
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
  } else {
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}

String sendData(String command, const int timeout, boolean debug) {
  String response = "";
  ESP01.print(command);
  long int time = millis();
  
  while ((time + timeout) > millis()) {
   while (ESP01.available()) {
      char c = ESP01.read();
      response += c;
    }
  }

  if (debug) {
    //Serial.print("Response:  ");
   // Serial.println(response);
  }
  
  return response;
}

bool checkWasteFull(int trigPin, int echoPin, int pin, int sec) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2; // Convert to cm
  
  if (pin == 1) {
    ultrasound_1 = String(distance);
  } else {
    ultrasound_2 = String(distance);
  }

  return (distance < sec); // Adjust threshold value as needed
}
