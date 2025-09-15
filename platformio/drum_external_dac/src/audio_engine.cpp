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

// EventDelay instance definition
EventDelay kTriggerDelay;

// Audio objects
ADSR<AUDIO_RATE, AUDIO_RATE> envB0;
ADSR<AUDIO_RATE, AUDIO_RATE> envB1;
ADSR<AUDIO_RATE, AUDIO_RATE> envB2;
ADSR<AUDIO_RATE, AUDIO_RATE> envB3;

Line<long> aGliss;

const unsigned int AUDIO_STEPS_PER_CONTROL = AUDIO_RATE / CONTROL_RATE;
float smoothness = 0.01f;
Smooth<unsigned int> aSmooth(smoothness);
volatile unsigned int freq1;

long audio_steps_per_gliss = AUDIO_RATE / 64;
long control_steps_per_gliss = CONTROL_RATE / 4;
long gliss_start;
long gliss_end;

// Oscillators
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> aSqu0(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> aSqu1(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> aSqu2(SQUARE_NO_ALIAS_2048_DATA);
Oscil<SQUARE_NO_ALIAS_2048_NUM_CELLS, AUDIO_RATE> aSqu3(SQUARE_NO_ALIAS_2048_DATA);

// Samples
Sample<kick9_NUM_CELLS, AUDIO_RATE> kick9(kick9_DATA);
Sample<snare3_NUM_CELLS, AUDIO_RATE> snare3(snare3_DATA);
Sample<snare4_NUM_CELLS, AUDIO_RATE> snare4(snare4_DATA);
Sample<HIHATTABLE_NUM_CELLS, AUDIO_RATE> hihat1(HIHATTABLE_DATA);
Sample<chihat2_NUM_CELLS, AUDIO_RATE> hihat2(chihat2_DATA);
Sample<clap2_NUM_CELLS, AUDIO_RATE> clap(clap2_DATA);
Sample<water1_NUM_CELLS, AUDIO_RATE> water1(water1_DATA);
Sample<snap1_NUM_CELLS, AUDIO_RATE> snap1(snap1_DATA);

void audio_init() {
  // Mozzi initialization (I2S settings specified in build_flags)
  startMozzi(CONTROL_RATE);
  kTriggerDelay.start(100);
  
  Serial.println("Audio initialized with I2S");
  Serial.println("I2S Pins: BCK=26, WS=25, DATA=5");
}

int audio_update() {
  envB0.update();
  envB1.update();
  envB2.update();
  envB3.update();
  
  int smoothedFreq = aSmooth.next(freq1);

  int code = envB0.next() * (aSqu0.next() >> 8) + 
             envB1.next() * (aSqu1.next() >> 8) + 
             envB2.next() * (aSqu2.next() >> 8) + 
             envB3.next() * (aSqu3.next() >> 8);
             
  int drum_volume = 4;  // 4x amplification

  int drum_mix = (snare3.next() + snare4.next() + snap1.next() + 
                  kick9.next() + hihat1.next() + hihat2.next() + 
                  clap.next() + water1.next()) * drum_volume;

  return (code  + drum_mix);
}

void drum_part() {
  if (seq_drum[0][master_count]) {
    kick9.start();
  }
  if (seq_drum[1][master_count]) {
    snare3.start();
  }
  if (seq_drum[2][master_count]) {
    snare4.start();
  }
  if (seq_drum[3][master_count]) {
    hihat1.start();
  }
  if (seq_drum[4][master_count]) {
    hihat2.start();
  }
  if (seq_drum[5][master_count]) {
    clap.start();
  }
  if (seq_drum[6][master_count]) {
    water1.start();
  }
  if (seq_drum[7][master_count]) {
    snap1.start();
  }
}

void melo_part() {
  if (seq_melo_trig[0][master_count]) {
    aSqu0.setFreq(mtof(seq_melo[0][master_count]));
    envB0.setADLevels((byte)220, (byte)150);
    envB0.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB0.noteOn();
  }
  if (seq_melo_trig[1][master_count]) {
    aSqu1.setFreq(mtof(seq_melo[1][master_count]));
    envB1.setADLevels((byte)220, (byte)150);
    envB1.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB1.noteOn();
  }
  if (seq_melo_trig[2][master_count]) {
    aSqu2.setFreq(mtof(seq_melo[2][master_count]));
    envB2.setADLevels((byte)220, (byte)150);
    envB2.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB2.noteOn();
  }
  if (seq_melo_trig[3][master_count]) {
    aSqu3.setFreq(mtof(seq_melo[3][master_count]));
    envB3.setADLevels((byte)220, (byte)150);
    envB3.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB3.noteOn();
  }
}

void set_freq() {
  kick9.setFreq((float)6 * (float)kick9_SAMPLERATE / (float)kick9_NUM_CELLS);
  snare3.setFreq(6 * (float)snare3_SAMPLERATE / (float)snare3_NUM_CELLS);
  snare4.setFreq(6 * (float)snare4_SAMPLERATE / (float)snare4_NUM_CELLS);
  hihat1.setFreq(16 * (float)HIHATTABLE_SAMPLERATE / (float)HIHATTABLE_NUM_CELLS);
  hihat2.setFreq((float)7 * (float)chihat2_SAMPLERATE / (float)chihat2_NUM_CELLS);
  clap.setFreq(6 * (float)clap2_SAMPLERATE / (float)clap2_NUM_CELLS);
  water1.setFreq(5 * (float)water1_SAMPLERATE / (float)water1_NUM_CELLS);
  snap1.setFreq((float)6 * (float)snap1_SAMPLERATE / (float)snap1_NUM_CELLS);
}

int mozzi_analog_read(unsigned char pin) {
  return mozziAnalogRead<12>(pin);
}

void audio_hook_wrapper() {
  audioHook();
}

bool trigger_delay_ready() {
  return kTriggerDelay.ready();
}

void trigger_delay_start(int time) {
  kTriggerDelay.start(time);
}