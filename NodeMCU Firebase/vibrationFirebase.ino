#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>


#define FIREBASE_HOST "vibration-monitor-b3687-default-rtdb.firebaseio.com"
#define auth "0DBbxiDdDKFUiVmpVUZOy6EOdQ3Z5bonGyKNoIQy"

#define WIFI_SSID "Ltu"
#define WIFI_PASSWORD "madhavan6"

const int vibrationPin = D0; // Define the vibration sensor pin

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  pinMode(vibrationPin, INPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi...");
    delay(1000);
  }

  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST,auth);
}

void loop() {
  int vibrationValue = vibration();
  Serial.println(vibrationValue);

  Firebase.setInt(firebaseData, "vibration", vibrationValue);

  delay(1000);
}


int vibration(){
  int value = pulseIn(vibrationPin,HIGH);
  return value;
}
