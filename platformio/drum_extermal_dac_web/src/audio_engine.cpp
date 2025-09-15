// FORCE Mozzi settings BEFORE any Mozzi includes
#define MOZZI_AUDIO_RATE 16384
#define MOZZI_CONTROL_RATE 128

#include "config.h"
#include "audio_engine.h"

#include <MozziGuts.h>
#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <ADSR.h>
#include <Portamento.h>
#include <Line.h>
#include <Smooth.h>
#include <tables/square_no_alias_2048_int8.h>
#include <Oscil.h>
#include <Sample.h>
#include <EventDelay.h>

// Sample file includes
#include "kick9.h"
#include "snare3.h"
#include "snare4.h"
#include "hihattable.h"
#include "chihat2.h"
#include "clap2.h"
#include "water1.h"
#include "snap1.h"

// Trigger delay variables
static unsigned long last_trigger_time = 0;
static int trigger_delay_duration = 100;

// Audio objects - CRITICAL for proper sound
ADSR<16384, 16384> envB0;
ADSR<16384, 16384> envB1;
ADSR<16384, 16384> envB2;
ADSR<16384, 16384> envB3;

Line<long> aGliss;

const unsigned int AUDIO_STEPS_PER_CONTROL = 16384 / 128;
float smoothness = 0.01f;
Smooth<unsigned int> aSmooth(smoothness);
volatile unsigned int freq1;

// Oscillators - for synthesis sounds
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, 16384> aSqu0(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, 16384> aSqu1(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, 16384> aSqu2(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, 16384> aSqu3(SQUARE_NO_ALIAS_2048_DATA);

// Samples - drum sounds
Sample<kick9_NUM_CELLS, 16384> kick9(kick9_DATA);
Sample<snare3_NUM_CELLS, 16384> snare3(snare3_DATA);
Sample<snare4_NUM_CELLS, 16384> snare4(snare4_DATA);
Sample<HIHATTABLE_NUM_CELLS, 16384> hihat1(HIHATTABLE_DATA);
Sample<chihat2_NUM_CELLS, 16384> hihat2(chihat2_DATA);
Sample<clap2_NUM_CELLS, 16384> clap(clap2_DATA);
Sample<water1_NUM_CELLS, 16384> water1(water1_DATA);
Sample<snap1_NUM_CELLS, 16384> snap1(snap1_DATA);

void audio_init() {
  // Mozzi initialization
  startMozzi(128);
  
  Serial.println("Drum Machine Audio initialized with I2S");
  Serial.println("I2S Pins: BCK=26, WS=25, DATA=5");
  Serial.println("Audio Rate: 16384");
  Serial.println("Optimized for clean, powerful drum sound");
  
  // Set sample frequencies with proper coefficients
  set_freq();
}

int audio_update() {
  // Update ADSR envelopes
  envB0.update();
  envB1.update();
  envB2.update();
  envB3.update();
  
  int smoothedFreq = aSmooth.next(freq1);

  // Synthesized sounds with envelope control
  int code = envB0.next() * (aSqu0.next() >> 8) + 
             envB1.next() * (aSqu1.next() >> 8) + 
             envB2.next() * (aSqu2.next() >> 8) + 
             envB3.next() * (aSqu3.next() >> 8);
             
  // CRITICAL: Proper drum volume settings from original
  int drum_volume = 5;
  int kick_volume = 8;  // High volume setting for kick9
  
  // kick9 processed separately at high volume
  int kick_sound = kick9.next() * kick_volume;
  int other_drums = (snare3.next() + snare4.next() + snap1.next() + 
                    hihat1.next() + hihat2.next() + clap.next() + water1.next()) * drum_volume;

  return (code + kick_sound + other_drums);
}

void set_freq() {
  // CRITICAL: Original frequency coefficients for proper sound
  kick9.setFreq((float)7 * (float)kick9_SAMPLERATE / (float)kick9_NUM_CELLS);        
  snare3.setFreq(7 * (float)snare3_SAMPLERATE / (float)snare3_NUM_CELLS);           
  snare4.setFreq(7 * (float)snare4_SAMPLERATE / (float)snare4_NUM_CELLS);           
  hihat1.setFreq(18 * (float)HIHATTABLE_SAMPLERATE / (float)HIHATTABLE_NUM_CELLS);  
  hihat2.setFreq((float)8 * (float)chihat2_SAMPLERATE / (float)chihat2_NUM_CELLS);  
  clap.setFreq(7 * (float)clap2_SAMPLERATE / (float)clap2_NUM_CELLS);               
  water1.setFreq(3 * (float)water1_SAMPLERATE / (float)water1_NUM_CELLS);           
  snap1.setFreq((float)7 * (float)snap1_SAMPLERATE / (float)snap1_NUM_CELLS);       
  
  Serial.println("Sample frequencies set with original coefficients");
}

// Individual drum trigger functions for web interface
void trigger_kick() { 
  kick9.start(); 
}

void trigger_snare1() { 
  snare3.start(); 
}

void trigger_snare2() { 
  snare4.start(); 
}

void trigger_hihat1() { 
  hihat1.start(); 
}

void trigger_hihat2() { 
  hihat2.start(); 
}

void trigger_clap() { 
  clap.start(); 
}

void trigger_water() { 
  water1.start(); 
}

void trigger_snap() { 
  snap1.start(); 
}

void audio_hook_wrapper() {
  audioHook();
}