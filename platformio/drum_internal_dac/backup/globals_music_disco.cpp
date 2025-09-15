#include "config.h"
// disco music style globals

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

// Drum sequence for 80s disco/dance style (fast tempo, strong drum emphasis)
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },  // Kick
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },  // Snare3
  { 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },  // Snare4
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1 },  // Hihat1
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  // Hihat2
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },  // Clap
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // Water1 (not used)
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }   // Snap1
};

// Melody sequence (MIDI note numbers, low range)
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 38, 0, 38, 41, 36, 0, 36, 39, 36, 0, 36, 40, 33, 0, 33, 36 }, // Track1: bassline
  { 0, 38, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 33, 0, 0 },          // Track2: walking bass
  { 62, 0, 0, 0, 59, 0, 0, 0, 60, 0, 0, 0, 57, 0, 0, 0 },          // Track3: chord comping
  { 0, 67, 0, 65, 0, 64, 0, 62, 0, 64, 0, 67, 0, 69, 0, 65 }       // Track4: lead melody
};

// Trigger sequence for disco/dance grooves
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Track1: bass 8th notes
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, // Track2: bass harmony off-beat
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Track3: strings 4th notes
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }  // Track4: lead 16th notes
};

// Note and octave names
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Display strings for sequencer
String seq_drum_kick    = "X--XX---X-X-X--X";
String seq_drum_snare3  = "----X-X-----X-X-";
String seq_drum_snare4  = "-X--X-X-X-X---X";
String seq_drum_hihat1  = "X-XX-X-XX-XX-X-X";
String seq_drum_hihat2  = "------X-------X-";
String seq_drum_clap1   = "----X--X----X---";
String seq_drum_water1  = "----------------";
String seq_drum_snap1   = "--X------X---X--";

// Melody display strings (8-step)
String seq_melo_key0_8 =  "D_DA_C_CG_C_CE_A";
String seq_melo_oct0_8 =  "0201020101010201";
String seq_melo_key1_8 =  "_D___C___C___A__";  
String seq_melo_oct1_8 =  "0201020102020201";
String seq_melo_key2_8 =  "D___B___C___A___";
String seq_melo_oct2_8 =  "0303030303030303";
String seq_melo_key3_8 =  "_G_F_E_D_E_G_A_F";
String seq_melo_oct3_8 =  "0403040304030403";

// Melody display strings (16-step)
String seq_melo_key0_16 = "A_A_F_F_C_C_G_G_A_A_F_F_C_C_G_G_";
String seq_melo_oct0_16 = "02020202020202020202020202020202";
String seq_melo_key1_16 = "_E_E_C_C_G_G_D_D_E_E_C_C_G_G_D_D";  
String seq_melo_oct1_16 = "03030303030303030303030303030303";
String seq_melo_key2_16 = "A___F___C___G___A___F___C___G___";
String seq_melo_oct2_16 = "04040404040404040404040404040404";
String seq_melo_key3_16 = "_A_G_F_E_D_C_D_E_A_G_F_E_D_C_D_E";
String seq_melo_oct3_16 = "05050505050505050505050505050505";

// ADSR settings for disco/dance sounds
int attack_time = 2;     // Short attack (2ms) for punch
int decay_time = 30;     // Short decay (30ms) for crispness
int sustain_time = 150;  // Medium sustain (150ms) for dance groove
int release_time = 100;  // Release (100ms) for smooth transition
