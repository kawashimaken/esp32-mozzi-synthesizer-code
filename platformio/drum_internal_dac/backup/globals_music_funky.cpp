#include "config.h"
// funky music style globals

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

// Funky drum loop + groovy bassline
// Tempo: 100-110 BPM (medium tempo suitable for funk)

// Funk drum sequence (1=ON, 0=OFF)
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH] = {
  { 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 },  // Kick
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },  // Snare3
  { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1 },  // Snare4
  { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },  // Hihat1
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },  // Hihat2
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },  // Clap
  { 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },  // Water1
  { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 }   // Snap1
};

// Funky bass + melody sequence (MIDI note numbers)
// Standard funk chord progression: Am7-D7-G-C
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 45, 0, 0, 45, 0, 47, 0, 0, 43, 0, 0, 43, 0, 48, 0, 0 },  // Track1: bassline
  { 0, 57, 0, 0, 0, 0, 59, 0, 0, 55, 0, 0, 0, 0, 60, 0 },    // Track2: octave bass
  { 0, 0, 69, 0, 0, 0, 74, 0, 0, 0, 67, 0, 0, 0, 72, 0 },    // Track3: chord strokes
  { 0, 0, 0, 81, 0, 0, 0, 79, 0, 0, 0, 77, 0, 0, 0, 76 }     // Track4: lead melody
};

// Trigger sequences (groove timing)
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH] = {
  { 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0 }, // Track1: bass groove
  { 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0 }, // Track2: offbeat support
  { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 }, // Track3: chord strokes
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 }  // Track4: lead syncopation
};

// Funk ADSR settings
int attack_time = 1;     // very short attack (1ms)
int decay_time = 50;     // short decay (50ms)
int sustain_time = 100;  // short sustain (100ms)
int release_time = 80;   // short release (80ms)

// Recommended tempo (funk groove)
 // tempo = 105; // BPM

// Note and octave names
String note_name[] = { "C_", "C#", "D_", "D#", "E_", "F_", "F#", "G_", "G#", "A_", "A#", "B_" };
String oct_name[] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };

// Display strings for drums (funk pattern)
String seq_drum_kick    = "---X--X--X----X-";
String seq_drum_snare3  = "----X-------X---";
String seq_drum_snare4  = "--X---X--X-X-X-X";
String seq_drum_hihat1  = "X-X-X-X-X-X-X-X-";
String seq_drum_hihat2  = "-----X------X---";
String seq_drum_clap1   = "-----------X----";
String seq_drum_water1  = "-X-------X------";
String seq_drum_snap1   = "--------X------X";

// Melody display strings (8-step)
String seq_melo_key0_8 =  "A___B___G___C___";
String seq_melo_oct0_8 =  "0200020002000300";
String seq_melo_key1_8 =  "_A_____B___C____";  
String seq_melo_oct1_8 =  "0300030003000400";
String seq_melo_key2_8 =  "__A___D___G___C_";
String seq_melo_oct2_8 =  "0004000400040004";
String seq_melo_key3_8 =  "___A___G___F_E__";
String seq_melo_oct3_8 =  "0005000500050005";

// Melody display strings (16-step)
String seq_melo_key0_16 = "A___B___G___C___A___B___G___C___";
String seq_melo_oct0_16 = "020002000200030002000200020003000";
String seq_melo_key1_16 = "_A_____B___C____A_____B___C____";  
String seq_melo_oct1_16 = "030003000300040003000300030004000";
String seq_melo_key2_16 = "__A___D___G___C___A___D___G___C_";
String seq_melo_oct2_16 = "000400040004000400040004000400040";
String seq_melo_key3_16 = "___A___G___F_E____A___G___F_E__";
String seq_melo_oct3_16 = "000500050005000500050005000500050";
