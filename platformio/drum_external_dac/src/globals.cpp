#include "config.h"
// EventDelay instance definition is done in audio_engine.cpp

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

// 80s disco dance music (high tempo, drum-emphasized)
// Tempo: 130-140 BPM (disco dance specification)

// Jazz disco complex drum sequence (1=ON, 0=OFF)
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  // Kick (four-on-the-floor + jazz-style syncopation)
  { 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },  //kick
  
  // Snare3 (beats 2 & 4 + jazz-style off-beat)
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },  //snare3
  
  // Snare4 (complex ghost notes + fill-ins)
  { 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1 },  //snare4
  
  // Hihat1 (jazz-style swing hi-hat)
  { 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1 },  //hihat1
  
  // Hihat2 (open hi-hat for accent enhancement)
  { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 },  //hihat2
  
  // Clap (jazz-style complex clap pattern)
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },  //clap1
  
  // Water1 (disabled - not used)
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  //water1
  
  // Snap1 (jazz-style rim shot effect)
  { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 }   //snap1
};

// Jazz disco melody sequence (MIDI note numbers - low range)
// Dm7-G7-CM7-Am7 jazz progression in disco arrangement
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  // Track 1: Jazz bass line (low range - octave down)
  { 38, 0, 38, 41, 36, 0, 36, 39, 36, 0, 36, 40, 33, 0, 33, 36 },
  
  // Track 2: Walking bass (jazz-style)
  { 0, 38, 0, 0, 0, 36, 0, 0, 0, 36, 0, 0, 0, 33, 0, 0 },
  
  // Track 3: Jazz chord comping (mid range)
  { 62, 0, 0, 0, 59, 0, 0, 0, 60, 0, 0, 0, 57, 0, 0, 0 },
  
  // Track 4: Jazz lead melody (mid-high range)
  { 0, 67, 0, 65, 0, 64, 0, 62, 0, 64, 0, 67, 0, 69, 0, 65 }
};

// Disco dance trigger array (groove-focused)
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  // Track 1: Bass line eighth note pattern
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
  
  // Track 2: Bass harmony (off-beat)
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
  
  // Track 3: Strings (quarter notes for grandeur)
  { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
  
  // Track 4: Lead synth (sixteenth notes for brilliance)
  { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }
};

// note_name and oct_name array definitions
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Jazz disco display strings
String seq_drum_kick =    "X--XX---X-X-X--X";
String seq_drum_snare3 =  "----X-X-----X-X-";
String seq_drum_snare4 =  "-X--X-X-X-X---X";
String seq_drum_hihat1 =  "X-XX-X-XX-XX-X-X";
String seq_drum_hihat2 =  "------X-------X-";
String seq_drum_clap1 =   "----X--X----X---";
String seq_drum_water1 =  "----------------";  // not used
String seq_drum_snap1 =   "--X------X---X--";

// Melody display (8-step version)
String seq_melo_key0_8 =  "D_DA_C_CG_C_CE_A";
String seq_melo_oct0_8 =  "0201020101010201";
String seq_melo_key1_8 =  "_D___C___C___A__";  
String seq_melo_oct1_8 =  "0201020102020201";
String seq_melo_key2_8 =  "D___B___C___A___";
String seq_melo_oct2_8 =  "0303030303030303";
String seq_melo_key3_8 =  "_G_F_E_D_E_G_A_F";
String seq_melo_oct3_8 =  "0403040304030403";

// Melody display (16-step version)
String seq_melo_key0_16 = "A_A_F_F_C_C_G_G_A_A_F_F_C_C_G_G_";
String seq_melo_oct0_16 = "02020202020202020202020202020202";
String seq_melo_key1_16 = "_E_E_C_C_G_G_D_D_E_E_C_C_G_G_D_D";  
String seq_melo_oct1_16 = "03030303030303030303030303030303";
String seq_melo_key2_16 = "A___F___C___G___A___F___C___G___";
String seq_melo_oct2_16 = "04040404040404040404040404040404";
String seq_melo_key3_16 = "_A_G_F_E_D_C_D_E_A_G_F_E_D_C_D_E";
String seq_melo_oct3_16 = "05050505050505050505050505050505";

// Disco dance ADSR settings (actual settings)
int attack_time = 2;     // Short attack (2ms) - disco punch
int decay_time = 30;     // Short decay (30ms) - crisp sound
int sustain_time = 150;  // Medium sustain (150ms) - optimal for dance
int release_time = 100;  // Release (100ms) - flow to next sound