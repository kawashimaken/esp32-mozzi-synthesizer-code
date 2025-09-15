#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "config.h"

// Initialize the audio engine
void audio_init();

// Update audio processing
int audio_update();

// Play drum part
void drum_part();

// Play melody part
void melo_part();

// Set sample frequency
void set_freq();

// Mozzi function wrappers
int mozzi_analog_read(unsigned char pin);
void audio_hook_wrapper();

// Access functions for EventDelay
bool trigger_delay_ready();
void trigger_delay_start(int time);

#endif // AUDIO_ENGINE_H
