// audio_engine.h - Minimal drum-only version
#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H
#include <Arduino.h>

// Function declarations
void audio_init();
int audio_update();
void set_freq();
void audio_hook_wrapper();

// Individual drum trigger functions
void trigger_kick();
void trigger_snare1();
void trigger_snare2();
void trigger_hihat1();
void trigger_hihat2();
void trigger_clap();
void trigger_water();
void trigger_snap();

#endif