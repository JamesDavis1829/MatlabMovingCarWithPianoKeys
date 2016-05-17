#include <Servo.h>
#include <SPI.h>
#include <WiFi.h>

char ssid[] = "05EA2E"; //  your network SSID (name)
char pass[] = "4CE15BW207292";    // your network password (use for WPA, or use as key for WEP)

Servo left;
Servo right;

int keyIndex = 0;

int status = WL_IDLE_STATUS;

WiFiServer server(23);

void setup() {
  left.attach(9);
  right.attach(8);
  left.write(90);
  right.write(90);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }

  // start the server:
  server.begin();
  printWifiStatus();
}


void loop() {
  // wait for a new client:
  WiFiClient client = server.available();


  // when the client sends the first byte, say hello:
  if (client) {
    if (client.available() > 0) {
      // read the bytes incoming from the client:
      char thisChar = client.read();
      Serial.println(thisChar);
      // echo the bytes back to the client:
      if(thisChar == 'f'){
        Serial.println("forward");
        right.write(95);
        left.write(85);
      }else if(thisChar == 'r'){
        Serial.println("right");
        right.write(95);
        left.write(90);
      }else if(thisChar == 'l'){
        Serial.println("left");
        right.write(90);
        left.write(85);
      }else if(thisChar == 'b'){
        Serial.println("reverse");
        right.write(85);
        left.write(95);
      }else if(thisChar == 's'){
        Serial.println("stop");
        right.write(90);
        left.write(90);
      }
    }
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


