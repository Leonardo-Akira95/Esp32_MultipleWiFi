/*
 * Esp 32 multiple wi-fi implementation with Watchdog and hardware interrupts
 * This is done with basically four variables:
 * wifiConnectionIndex: Defines which network from the array of SSID's we're trying to connect
 * qtyNetworks: The number of networks we want the esp32 to try to establish a connection
 * ssid: Enter here your network SSID's
 * pwds: Enter here your network passwords
 *
 * I've commented everything i could, hope this helps someone! :)
 */

#include <WiFi.h>

// Variable to control which network we're trying to connect
int wifiConnectionIndex = 0;

// You can adjust the number of networks the esp32 will try to connect to by adding or substracting indexes from qtyNetworks
const int qtyNetworks = 2;
// Add here your credentials (i.e: SSID: myHouse PWD: myPassword)
const char *ssid[qtyNetworks] = {"YOUR PRIMARY SSID", "YOUR SECONDARY SSID"};
const char *pwds[qtyNetworks] = {"YOUR PRIMARY NETWORK PASSWORD", "YOUR SECONDARY NETWORK PASSWORD"};

// Responsible for changing which ssid esp32 will try to connect
void changeWifiIndex(){
  wifiConnectionIndex++;
  
  // Will prevent esp32 from connection to anything other than the defined networks, resetting wifiConnectionIndex to zero
  if(wifiConnectionIndex > qtyNetworks -1){
    wifiConnectionIndex = 0;
  }
  Serial.print("Changed connection index to: ");
  Serial.println(wifiConnectionIndex);
}

void connectToWifi() {
  Serial.println("Trying to connnect to ssid/password: ");
  Serial.println(ssid[wifiConnectionIndex]);
  Serial.println(pwds[wifiConnectionIndex]);
  WiFi.begin(ssid[wifiConnectionIndex], pwds[wifiConnectionIndex]);
  Serial.println("MAC Address:");
  Serial.println(WiFi.macAddress());
}

// Handle events from wi-fi, if disconnected will change wi-fi index and try to connect again
// For more info on wi-fi events:
// DOCUMENTATION FROM ESPESSIF OFFICIAL SITE: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/event-handling.html
void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event) {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      changeWifiIndex();
      connectToWifi();
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.onEvent(WiFiEvent); // handle WiFiEvents
  connectToWifi();
}

void loop() {

  delay(1000);
}
