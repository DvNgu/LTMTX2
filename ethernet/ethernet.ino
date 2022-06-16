#include <SPI.h>
#include <Ethernet.h>
#include "DHT.h"

byte mac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED};
#define DHTPIN 2
#define DHTTYPE DHT11  

IPAddress ip(192,168,0,177);
//IPAddress myDns(192,168,0,1);

EthernetClient client;
EthernetServer server = EthernetServer(8888);
DHT dht(DHTPIN, DHTTYPE);
byte command;
float sineWaveBuffer[250];

void setup()
{
  // Initialize serial communication.
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // Wait for serial port to connect.
  }
  
  Ethernet.begin(mac,ip/*,myDns*/);
  Serial.print("Manually assigned the following IP address to the Arduino:");
  Serial.println();
  Serial.println(Ethernet.localIP());
  Serial.println(Ethernet.gatewayIP());
  if (Ethernet.hardwareStatus() == EthernetNoHardware)
  {
    Serial.println("Ethernet shield was not found.");
  }
  if (Ethernet.linkStatus() == LinkOFF) 
  {
    Serial.println("Ethernet cable is not connected.");
  }
   server.begin();
   dht.begin();

}
// Main processing loop
void loop()
{
  EthernetClient client = server.available();
  if (client) {
 
    while (client.connected()) {
      while (client.available()>0) {
        char x = client.read();
        if(x == 's'){
          int h = dht.readHumidity();
          int t = dht.readTemperature();
          client.print(t);
          client.print(h);
          Serial.print(t);
          Serial.print('\t');
          Serial.println(h);
        }
      }
      delay(10);
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
