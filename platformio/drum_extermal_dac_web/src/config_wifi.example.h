// config_wifi.example.h - WiFi access point settings (template)
//
// Copy this file to config_wifi.h in the same folder and set AP_PASSWORD
// before building:
//
//   cp config_wifi.example.h config_wifi.h
//
// config_wifi.h is listed in .gitignore so your password is never committed.
// The build stops with an error if config_wifi.h is missing or if AP_PASSWORD
// is shorter than 8 characters (the WPA2 minimum).

#ifndef CONFIG_WIFI_H
#define CONFIG_WIFI_H

// Network name broadcast by the drum machine.
#define AP_SSID "DrumMachine-AP"

// Password for the access point: 8 to 63 characters. Choose your own.
#define AP_PASSWORD ""

// Fixed address of the access point (ESP32 soft-AP default).
#define AP_IP_ADDRESS "192.168.4.1"

#endif
