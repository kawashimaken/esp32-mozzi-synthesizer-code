#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ADC pin definitions (restored from original config.h)
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

// Basic audio settings
#define CONTROL_RATE 256
#define AUDIO_RATE 16384
#define SECONDS 4

// Extended sequencer settings (long song support)
#define NUM_DRUM_TRACKS 8
#define NUM_MELO_TRACKS 4
#define SEQUENCE_LENGTH 256  // Extended from 16 to 256
#define PATTERN_LENGTH 16    // Length of 1 pattern
#define NUM_PATTERNS 16      // Number of patterns (composed of 16 patterns)
#define TOTAL_SECTIONS 4     // Number of sections

// Section definitions
#define SECTION_INTRO 0
#define SECTION_VERSE 1
#define SECTION_CHORUS 2
#define SECTION_OUTRO 3

// Section lengths (number of patterns)
#define INTRO_PATTERNS 2      // Intro: 2 patterns (8 seconds)
#define VERSE_PATTERNS 6      // Verse: 6 patterns (24 seconds)
#define CHORUS_PATTERNS 6     // Chorus: 6 patterns (24 seconds)
#define OUTRO_PATTERNS 2      // Outro: 2 patterns (8 seconds)

// Global variable declarations
extern int master_count;
extern int pattern_count;
extern int current_section;
extern int section_progress;
extern bool song_playing;
extern bool song_finished;

extern int tempo;

// UI related
extern int cursor_x_drum;
extern int cursor_y_drum;
extern int cursor_x_melo_12;
extern int cursor_y_melo_12;
extern int cursor_x_melo_34;
extern int cursor_y_melo_34;
extern int cursor_select;

// ADSR settings
extern int attack_time;
extern int decay_time;
extern int sustain_time;
extern int release_time;

// Note names
extern String note_name[];
extern String oct_name[];

// Sequencer data (for split structure)
extern boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH];
extern int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH];
extern boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH];

// Pattern-based data (defined in each pattern library)
extern boolean drum_patterns[NUM_PATTERNS][NUM_DRUM_TRACKS][PATTERN_LENGTH];
extern int melo_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH];
extern boolean melo_trig_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH];

// Song structure
extern int song_structure[NUM_PATTERNS];

// Display strings (defined in drum_patterns.cpp and melody_patterns.cpp)
extern String seq_drum_kick;
extern String seq_drum_snare3;
extern String seq_drum_snare4;
extern String seq_drum_hihat1;
extern String seq_drum_hihat2;
extern String seq_drum_clap1;
extern String seq_drum_water1;
extern String seq_drum_snap1;

extern String seq_melo_key0_8;
extern String seq_melo_oct0_8;
extern String seq_melo_key1_8;
extern String seq_melo_oct1_8;
extern String seq_melo_key2_8;
extern String seq_melo_oct2_8;
extern String seq_melo_key3_8;
extern String seq_melo_oct3_8;

extern String seq_melo_key0_16;
extern String seq_melo_oct0_16;
extern String seq_melo_key1_16;
extern String seq_melo_oct1_16;
extern String seq_melo_key2_16;
extern String seq_melo_oct2_16;
extern String seq_melo_key3_16;
extern String seq_melo_oct3_16;

// Function prototypes (implemented in song_structure.cpp)
void init_long_song();
void update_long_song();
int get_current_pattern();
bool is_song_finished();
void start_song();
void stop_song();
const char* get_current_section_name();
float get_song_progress_percent();

// Song library configuration
#define MAX_SONGS 5
#define SONG_EUROBEAT 0
#define SONG_HIPHOP 1
#define SONG_KPOP 2
#define SONG_AMBIENT 3
#define SONG_CLASSICAL 4

// Global variables for song management
extern int current_song_id;

#endif // CONFIG_H