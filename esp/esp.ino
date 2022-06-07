#include <WiFi.h>
#include <ctype.h>
 
const char* ssid = "302";//"YourNetworkName";
const char* password =  "88888888";//"YourNetworkPassword";
 
WiFiServer wifiServer(80);
 
void setup() {
 
  Serial.begin(115200);
 
  delay(1000);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}
 
void loop() {
 
  WiFiClient client = wifiServer.available();
 
  if (client) {
 
    while (client.connected()) {
      while (client.available()>0) {
        char x = client.read();
        if(x == 's'){
          int a = random(0, 100);
          int b = random(0, 100);
          client.print(a);
          client.print(b);
          Serial.print(a);
          Serial.print('\t');
          Serial.println(b);
        }
      }
      delay(10);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
