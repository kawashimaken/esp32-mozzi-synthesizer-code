#include "config.h"
// backup

// Global variables
int master_count = 0;
int tempo = 0;
bool trigger;
byte check;

int cursor_x_drum = 0;
int cursor_y_drum = 0;
int cursor_x_melo_12 = 0;
int cursor_y_melo_12 = 0;
int cursor_x_melo_34 = 0;
int cursor_y_melo_34 = 0;
int cursor_select = 0;

int attack_time = 0;
int decay_time = 0;
int sustain_time = 0;
int release_time = 0;

// Sequencer data
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // kick
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // snare3
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // snare4
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // hihat1
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // hihat2
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // clap1
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // water1
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // snap1
};

int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

// Note and octave names
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Drum sequence strings
String seq_drum_kick = "----------------";
String seq_drum_snare3 = "----------------";
String seq_drum_snare4 = "----------------";
String seq_drum_hihat1 = "----------------";
String seq_drum_hihat2 = "----------------";
String seq_drum_clap1 = "----------------";
String seq_drum_water1 = "----------------";
String seq_drum_snap1 = "----------------";

// Melody sequence strings (8-step)
String seq_melo_oct0_8 = "";
String seq_melo_key0_8 = "";
String seq_melo_oct1_8 = "";
String seq_melo_key1_8 = "";
String seq_melo_oct2_8 = "";
String seq_melo_key2_8 = "";
String seq_melo_oct3_8 = "";
String seq_melo_key3_8 = "";

// Melody sequence strings (16-step)
String seq_melo_oct0_16 = "";
String seq_melo_key0_16 = "";
String seq_melo_oct1_16 = "";
String seq_melo_key1_16 = "";
String seq_melo_oct2_16 = "";
String seq_melo_key2_16 = "";
String seq_melo_oct3_16 = "";
String seq_melo_key3_16 = "";
