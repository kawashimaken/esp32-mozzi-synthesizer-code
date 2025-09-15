#include "config.h"
// electronica / poppin music style globals

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

// Modern electropop (popping dance style)
// Tempo: 100-110 BPM (medium tempo suitable for popping)

// Electropop drum sequence (1=ON, 0=OFF)
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 },  // Kick
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },  // Snare3
  { 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0 },  // Snare4
  { 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },  // Hihat1
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },  // Hihat2
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },  // Clap
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },  // Water1
  { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }   // Snap1
};

// Electropop melody sequence (MIDI note numbers)
// Chord progression: Em - Am - C - D
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 40, 0, 40, 0, 45, 0, 45, 0, 48, 0, 48, 0, 50, 0, 50, 0 },  // Track1: synth bass
  { 28, 0, 0, 0, 33, 0, 0, 0, 36, 0, 0, 0, 38, 0, 0, 0 },       // Track2: sub bass
  { 64, 0, 67, 0, 69, 0, 67, 0, 72, 0, 71, 0, 74, 0, 72, 0 },   // Track3: lead synth
  { 0, 64, 0, 67, 0, 69, 0, 72, 0, 69, 0, 72, 0, 74, 0, 76 }    // Track4: arpeggiator
};

// Popping dance trigger sequence (robotic groove)
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Track1: synth bass
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Track2: sub bass
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Track3: lead synth
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }  // Track4: arpeggiator
};

// Note and octave names
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Display strings for drums
String seq_drum_kick    = "X---X-X-X---X-X-";
String seq_drum_snare3  = "----X-------X--X";
String seq_drum_snare4  = "-X-X--X--X-X--X-";
String seq_drum_hihat1  = "XXXX-X-XXXXX-X-X";
String seq_drum_hihat2  = "---X---X---X---X";
String seq_drum_clap1   = "--X---X---X---X-";
String seq_drum_water1  = "-----X-------X--";
String seq_drum_snap1   = "X-------X-------";

// Melody display strings (8-step)
String seq_melo_key0_8 =  "E_E_A_A_C_C_D_D_";
String seq_melo_oct0_8 =  "0202020202020202";
String seq_melo_key1_8 =  "E___A___C___D___";  
String seq_melo_oct1_8 =  "0101010101010101";
String seq_melo_key2_8 =  "E_G_A_G_C_B_D_C_";
String seq_melo_oct2_8 =  "0303030303030303";
String seq_melo_key3_8 =  "_E_G_A_C_A_C_D_E";
String seq_melo_oct3_8 =  "0303030303030303";

// Melody display strings (16-step)
String seq_melo_key0_16 = "E_E_A_A_C_C_D_D_E_E_A_A_C_C_D_D_";
String seq_melo_oct0_16 = "02020202020202020202020202020202";
String seq_melo_key1_16 = "E___A___C___D___E___A___C___D___";  
String seq_melo_oct1_16 = "01010101010101010101010101010101";
String seq_melo_key2_16 = "E_G_A_G_C_B_D_C_E_G_A_G_C_B_D_C_";
String seq_melo_oct2_16 = "03030303030303030303030303030303";
String seq_melo_key3_16 = "_E_G_A_C_A_C_D_E_E_G_A_C_A_C_D_E";
String seq_melo_oct3_16 = "03030303030303030303030303030303";

// ADSR settings for electropop (robotic sound)
int attack_time = 1;     // Instant attack (1ms)
int decay_time = 50;     // Short decay (50ms)
int sustain_time = 80;   // Short sustain (80ms)
int release_time = 20;   // Short release (20ms)
