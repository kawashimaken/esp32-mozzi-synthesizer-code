#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "config.h"

// Audio engine initialization
void audio_init();

// Audio update
int audio_update();

// Drum part playback
void drum_part();

// Melody part playback
void melo_part();

// Sample frequency setup
void set_freq();

// Mozzi function wrappers
int mozzi_analog_read(unsigned char pin);
void audio_hook_wrapper();

// EventDelay access functions
bool trigger_delay_ready();
void trigger_delay_start(int time);

#endif // AUDIO_ENGINE_H