/*
 * DweetIO Client Program
 * 
 * NodeMCU acts as a client that repeatedly sends a GET request to the DweetIO
 * service to retrieve the latest Dweet to a user-specificed Dweet tag.
 * 
 * To use this, modify the constants under "---- MODIFIABLE CONSTANTS ----" for
 * your own personal use-case.
 */


// ---- DEPENDENCIES ----
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// ---- MODIFIABLE CONSTANTS ----
const char * ssid = "ssid"; // put your ssid (network name) here
const char * password = "password"; // put your network password here
const String dweetTag = "tag"; // put your unique dweet tag here

// ---- UNMODIFIABLE CONSTANTS ----
const String host = "dweet.io";

/*
 * Setup
 * 
 * Runs once when the NodeMCU is powered on.
 */
void setup() {
  
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.print("\nIP Address is: "); Serial.println(WiFi.localIP());

}

/*
 * Loop
 * 
 * Runs repeatedly until the NodeMCU loses power.
 */
void loop() {

  /*
   * To act as a client, we have to send a proper GET request to
   * the server we are requesting information from. The following
   * code block produces output similar to the following:
   * 
   * GET /get/latest/dweet/for/<dweetTag> HTTP/1.1
   * Host: <host>
   * Connection: close
   */
  WiFiClient client;
  if (client.connect(host, 80)) {
    String url = "/get/latest/dweet/for/" + dweetTag;
    Serial.print('\n');
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
      "Host: " + host + "\r\n" +
      "Connection: close\r\n\r\n");
    while (client.connected()) {
      String receivedData = client.readStringUntil('\r');
      Serial.print(receivedData);
    }
    client.stop();
  }
  delay(5000); // wait five seconds before getting next dweet
  
}
