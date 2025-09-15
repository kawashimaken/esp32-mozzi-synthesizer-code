#include "config.h"
// upbeat music style globals

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

// Upbeat sequence data (tempo: medium to fast, 120-140 BPM)

// Drum sequence (1=ON, 0=OFF)
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0 },  // kick
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1 },  // snare3
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },  // snare4
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  // hihat1
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },  // hihat2
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // clap1
  { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },  // water1
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 }   // snap1
};

// Melody sequence (MIDI note numbers)
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 60, 0, 64, 0, 67, 0, 72, 0, 69, 0, 65, 0, 62, 0, 60, 0 },  // main melody
  { 0, 64, 0, 67, 0, 71, 0, 76, 0, 72, 0, 69, 0, 65, 0, 64 },  // harmony
  { 48, 0, 0, 0, 55, 0, 0, 0, 52, 0, 0, 0, 50, 0, 0, 0 },      // bass line
  { 0, 0, 72, 0, 0, 74, 0, 76, 0, 0, 77, 0, 0, 74, 0, 72 }     // lead line
};

// Trigger array (when notes are played)
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },  // main melody
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  // harmony
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },  // bass
  { 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 }   // lead
};

// Recommended ADSR values
int attack_time = 5;     
int decay_time = 100;    
int sustain_time = 200;  
int release_time = 150;  

// Recommended tempo
// tempo = 130; // BPM (set according to your system)

// Display strings for debugging/UI
String seq_drum_kick =    "X---X-X-X---X-X-";
String seq_drum_snare3 =  "----X--X----X--X";
String seq_drum_snare4 =  "----------X-----";
String seq_drum_hihat1 =  "-X-X-X-X-X-X-X-X";
String seq_drum_hihat2 =  "--X---X---X---X-";
String seq_drum_clap1 =   "------------X---";
String seq_drum_water1 =  "---X-------X----";
String seq_drum_snap1 =   "---------X-----X";

// Melody display strings (8-step)
String seq_melo_key0_8 =  "C_E_G_C_A_F_D_C_";
String seq_melo_oct0_8 =  "0404050705040204";
String seq_melo_key1_8 =  "_E_G_B_E_C_A_F_E";  
String seq_melo_oct1_8 =  "0404050705040204";
String seq_melo_key2_8 =  "C_____G___E_D___";
String seq_melo_oct2_8 =  "0300050302020300";
String seq_melo_key3_8 =  "__C___D_E_F_D_C_";
String seq_melo_oct3_8 =  "0005050505050505";

// Melody display strings (16-step)
String seq_melo_key0_16 = "C_E_G_C_A_F_D_C_C_E_G_C_A_F_D_C_";
String seq_melo_oct0_16 = "04040507050402040404050705040204";
String seq_melo_key1_16 = "_E_G_B_E_C_A_F_E_E_G_B_E_C_A_F_E";  
String seq_melo_oct1_16 = "04040507050402040404050705040204";
String seq_melo_key2_16 = "C_____G___E_D___C_____G___E_D___";
String seq_melo_oct2_16 = "03000503020203000300050302020300";
String seq_melo_key3_16 = "__C___D_E_F_D_C___C___D_E_F_D_C_";
String seq_melo_oct3_16 = "00050505050505050005050505050505";

// Note and octave names (for error prevention)
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
