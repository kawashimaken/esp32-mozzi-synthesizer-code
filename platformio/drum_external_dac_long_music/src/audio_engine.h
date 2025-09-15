// audio_engine.h
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <Arduino.h>

// Function declarations
void audio_init();
int audio_update();
void drum_part();
void melo_part();
void set_freq();
int mozzi_analog_read(unsigned char pin);
void audio_hook_wrapper();

#endif