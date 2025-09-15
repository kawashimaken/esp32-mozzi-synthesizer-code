#ifndef WEB_UI_H
#define WEB_UI_H

#include <Arduino.h>

// HTML/CSS generation functions
String getWebUIHTML();
String getCSS();
String getDrumPadHTML();
String getTransportHTML();
String getSequencerHTML();
String getStatusHTML();

// JavaScript function moved to web_js.h/cpp

#endif