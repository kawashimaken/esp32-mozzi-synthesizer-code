#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ADC pin definitions
#define A0_meter 39  // tempo
#define A1_meter 34  // channel
#define A2_meter 35  // release
#define A3_meter 32  // sustain
#define A4_meter 33  // decay
#define A5_meter 27  // attack

// Button pin definitions
#define cross_button_up 13
#define cross_button_down 23 
#define cross_button_left 4
#define cross_button_right 18
#define button_confirm 19
#define button_cancel 16

// Other pin definitions
#define clock_out 12
#define run_stop 14

// Settings
#define CONTROL_RATE 1024
#define SECONDS 4

// Sequencer settings
#define NUM_DRUM_TRACKS 8
#define NUM_MELO_TRACKS 4
#define SEQUENCE_LENGTH 16

// Global variable declarations
extern int master_count;
extern int tempo;
extern bool trigger;
extern byte check;

extern int cursor_x_drum;
extern int cursor_y_drum;
extern int cursor_x_melo_12;
extern int cursor_y_melo_12;
extern int cursor_x_melo_34;
extern int cursor_y_melo_34;
extern int cursor_select;

extern int attack_time;
extern int decay_time;
extern int sustain_time;
extern int release_time;

// Sequencer data
extern boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH];
extern int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH];
extern boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH];

// Display strings
extern String seq_drum_kick;
extern String seq_drum_snare3;
extern String seq_drum_snare4;
extern String seq_drum_hihat1;
extern String seq_drum_hihat2;
extern String seq_drum_clap1;
extern String seq_drum_water1;
extern String seq_drum_snap1;

extern String seq_melo_oct0_8;
extern String seq_melo_key0_8;
extern String seq_melo_oct1_8;
extern String seq_melo_key1_8;
extern String seq_melo_oct2_8;
extern String seq_melo_key2_8;
extern String seq_melo_oct3_8;
extern String seq_melo_key3_8;

extern String seq_melo_oct0_16;
extern String seq_melo_key0_16;
extern String seq_melo_oct1_16;
extern String seq_melo_key1_16;
extern String seq_melo_oct2_16;
extern String seq_melo_key2_16;
extern String seq_melo_oct3_16;
extern String seq_melo_key3_16;

extern String note_name[];
extern String oct_name[];

#endif // CONFIG_H
