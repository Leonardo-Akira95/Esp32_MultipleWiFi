# Dynamic Wifi implementation using esp32
Setup multiple wi-fi connections for esp32 using WiFi library

 ### This is done basically with:
 * wifiConnectionIndex: Defines which network from the array of SSID's we're trying to connect to
 * qtyNetworks: The number of networks we want the esp32 to try to establish a connection
 * ssid: Enter here your network SSID's
 * pwds: Enter here your network passwords

### For more information on handling wi-fi events:
OFFICIAL ESPRESSIF DOCUMENTATION: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/event-handling.html
