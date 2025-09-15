#include "config.h" 
// EventDelay instance is defined in audio_engine.cpp

// Global variable definitions
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

// Modern Trap/Electronic sequence data
// Tempo: 140-150 BPM (energetic, modern)

boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 },  // Kick - Strong 4/4 with syncopation
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1 },  // Snare3 - Classic backbeat with fills
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 },  // Snare4 - Ghost notes
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },  // Hihat1 - Consistent 8th notes
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },  // Hihat2 - Offbeat 16th notes
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // Clap - Accent on beat 13
  { 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0 },  // Water1 - Rhythmic texture
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 }   // Snap1 - Sparse accents
};

// Modern melody sequences (MIDI note numbers) - Pentatonic/Minor scales for catchiness
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 36, 0, 38, 0, 36, 0, 41, 0, 36, 0, 38, 0, 43, 0, 36, 0 }, // Track 1: Bass line (E minor pentatonic)
  { 60, 0, 0, 67, 0, 65, 0, 0, 60, 0, 0, 67, 0, 65, 0, 62 }, // Track 2: Lead melody (C major)
  { 0, 72, 0, 0, 79, 0, 0, 77, 0, 72, 0, 0, 79, 0, 77, 0 }, // Track 3: High arp (countermelody)
  { 48, 0, 52, 0, 55, 0, 52, 0, 48, 0, 52, 0, 55, 0, 59, 0 }  // Track 4: Chord stabs
};

// Melody trigger arrays - More dynamic triggering
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Track 1: Bass line - steady
  { 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1 }, // Track 2: Lead melody - syncopated
  { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0 }, // Track 3: High arp - offbeat
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }  // Track 4: Chord stabs - rhythmic
};

// Note and octave name arrays
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Drum display strings - Updated patterns
String seq_drum_kick =    "X---X---X---X-X-";
String seq_drum_snare3 =  "----X---X---X--X";
String seq_drum_snare4 =  "--X---X---X---X-";
String seq_drum_hihat1 =  "X-X-X-X-X-X-X-X-";
String seq_drum_hihat2 =  "-X-X-X-X-X-X-X-X";
String seq_drum_clap1 =   "------------X---";
String seq_drum_water1 =  "X--X--X--X--X---";
String seq_drum_snap1 =   "-----X----X---X";

// Melody display (8-step) - Updated for new melody
String seq_melo_key0_8 =  "C_D_C_F_C_D_G_C_";
String seq_melo_oct0_8 =  "0202020302020203";
String seq_melo_key1_8 =  "C___G_F_C___G_D_";   
String seq_melo_oct1_8 =  "0505040505050504";
String seq_melo_key2_8 =  "_C___G___F_C___G";
String seq_melo_oct2_8 =  "0606060606060606";
String seq_melo_key3_8 =  "C_E_G_E_C_E_G_B_";
String seq_melo_oct3_8 =  "0303030303030303";

// Melody display (16-step) - Updated for new melody
String seq_melo_key0_16 = "C___D___C___F___C___D___G___C___";
String seq_melo_oct0_16 = "020202020202030302020202020203030";
String seq_melo_key1_16 = "C_______G___F_______C_______G___D___";   
String seq_melo_oct1_16 = "050505050404050505050505050405040";
String seq_melo_key2_16 = "_C_____G_______F___C_____G___";
String seq_melo_oct2_16 = "060606060606060606060606060606060";
String seq_melo_key3_16 = "C___E___G___E___C___E___G___B___";
String seq_melo_oct3_16 = "030303030303030303030303030303030";

// ADSR settings for modern electronic sound
int attack_time = 50;    // Quick attack (ms) - punchy sound
int decay_time = 200;    // Short decay (ms) - crisp
int sustain_time = 300;  // Moderate sustain (ms) - groove
int release_time = 150;  // Short release (ms) - tight sound