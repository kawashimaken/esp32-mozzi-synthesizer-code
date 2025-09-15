#include "audio_engine.h"
#include "config.h"           
#include "song_structure.h"   

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
  
  Serial.println("K-POP Audio initialized with I2S");
  Serial.println("I2S Pins: BCK=26, WS=25, DATA=5");
  Serial.println("Optimized for clean, modern production");
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
             
  // K-POP style drum volume adjustment - kick9 specially enhanced
  int drum_volume = 5;
  int kick_volume = 8;  // High volume setting for kick9
  
  // kick9 processed separately at high volume
  int kick_sound = kick9.next() * kick_volume;
  int other_drums = (snare3.next() + snare4.next() + snap1.next() + 
                    hihat1.next() + hihat2.next() + clap.next() + water1.next()) * drum_volume;

  return (code + kick_sound + other_drums);
}

void drum_part() {
  // K-POP style drum processing (256-step support)
  int current_step = master_count % SEQUENCE_LENGTH;
  
  if (seq_drum[0][current_step]) {
    kick9.start();
  }
  if (seq_drum[1][current_step]) {
    snare3.start();
  }
  if (seq_drum[2][current_step]) {
    snare4.start();
  }
  if (seq_drum[3][current_step]) {
    hihat1.start();
  }
  if (seq_drum[4][current_step]) {
    hihat2.start();
  }
  if (seq_drum[5][current_step]) {
    clap.start();
  }
  if (seq_drum[7][current_step]) {
    snap1.start();
  }
}

void melo_part() {
  // K-POP style melody processing (256-step support)
  int current_step = master_count % SEQUENCE_LENGTH;
  
  if (seq_melo_trig[0][current_step]) {
    aSqu0.setFreq(mtof(seq_melo[0][current_step]));
    envB0.setADLevels((byte)220, (byte)150);
    envB0.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB0.noteOn();
  }
  if (seq_melo_trig[1][current_step]) {
    aSqu1.setFreq(mtof(seq_melo[1][current_step]));
    envB1.setADLevels((byte)200, (byte)140);
    envB1.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB1.noteOn();
  }
  if (seq_melo_trig[2][current_step]) {
    aSqu2.setFreq(mtof(seq_melo[2][current_step]));
    envB2.setADLevels((byte)180, (byte)130);
    envB2.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB2.noteOn();
  }
  if (seq_melo_trig[3][current_step]) {
    aSqu3.setFreq(mtof(seq_melo[3][current_step]));
    envB3.setADLevels((byte)240, (byte)160); // Emphasize lead melody
    envB3.setTimes(attack_time, decay_time, sustain_time, release_time);
    envB3.noteOn();
  }
}

void set_freq() {
  // K-POP style sample frequency settings
  kick9.setFreq((float)7 * (float)kick9_SAMPLERATE / (float)kick9_NUM_CELLS);        // Slightly higher for punch
  snare3.setFreq(7 * (float)snare3_SAMPLERATE / (float)snare3_NUM_CELLS);           // Clear snap
  snare4.setFreq(7 * (float)snare4_SAMPLERATE / (float)snare4_NUM_CELLS);           // For layering
  hihat1.setFreq(18 * (float)HIHATTABLE_SAMPLERATE / (float)HIHATTABLE_NUM_CELLS);  // Higher and tight
  hihat2.setFreq((float)8 * (float)chihat2_SAMPLERATE / (float)chihat2_NUM_CELLS);  // For accents
  clap.setFreq(7 * (float)clap2_SAMPLERATE / (float)clap2_NUM_CELLS);               // Modern clap
  water1.setFreq(3 * (float)water1_SAMPLERATE / (float)water1_NUM_CELLS);           // Subtle
  snap1.setFreq((float)7 * (float)snap1_SAMPLERATE / (float)snap1_NUM_CELLS);       // Percussion
}

int mozzi_analog_read(unsigned char pin) {
  return mozziAnalogRead<12>(pin);
}

void audio_hook_wrapper() {
  audioHook();
}
