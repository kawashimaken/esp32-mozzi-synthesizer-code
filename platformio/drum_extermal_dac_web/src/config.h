// config.h - Pure Drum Machine (EXACT original settings)
#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Audio settings - EXACTLY as in original working code
#define CONTROL_RATE 128
#define AUDIO_RATE 16384

// Force Mozzi to use our audio rate
#define MOZZI_AUDIO_RATE 16384

#define MOZZI_OUTPUT_2PIN_PWM 1
#define MOZZI_I2S_FORMAT I2S_LSB
#define MOZZI_I2S_PIN_BCK 26
#define MOZZI_I2S_PIN_WS 25
#define MOZZI_I2S_PIN_DATA 5

// Drum settings only
#define NUM_DRUM_TRACKS 8

// Web Server settings
#define WEB_SERVER_PORT 80
#define WEB_UPDATE_INTERVAL 50

#endif