// config_wifi.h - WiFi configuration options file
// Add this file to .gitignore to manage personal WiFi settings

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

// Optional: Create this file if you want to connect to an existing WiFi network
// Usage example:
// #define USE_EXISTING_WIFI
// #define WIFI_SSID "YourWiFiName"
// #define WIFI_PASSWORD "YourPassword"

// Default is access point mode
#ifndef USE_EXISTING_WIFI
#define AP_SSID "DrumMachine-AP"
#define AP_PASSWORD "drum1234"
#define AP_IP_ADDRESS "192.168.4.1"
#endif

#endif