#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

#define NUM_DRUM_TRACKS 8

// External variables
extern bool web_sequence[NUM_DRUM_TRACKS][16];
extern bool web_sequence_playing;
extern int web_current_step;
extern int web_bpm;

// Function declarations
void web_server_init();
void setup_wifi();
void web_server_update();

// HTTP handlers
void handle_root();
void handle_drum_trigger();
void handle_sequence_update();
void handle_transport_control();
void handle_status();
void handle_not_found();
void handle_bpm_update();

// Utility functions
void trigger_drum_sample(int drum_id);
void web_play();
void web_stop();
void web_reset();
String get_current_status_json();

#endif