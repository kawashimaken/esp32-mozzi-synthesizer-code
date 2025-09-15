#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "config.h"
#include "audio_engine.h"
#include "song_structure.h"
#include "song_library.h"

// Main function prototypes
void sequencer_init();
void sequencer_update();

void long_song_drum_part();
void long_song_melo_part();
void dynamic_section_processing();

// Section management functions
float get_section_volume_multiplier();
int get_current_section_type();
bool should_play_water_track();  // 追加

// Status check
bool is_long_song_active();

// Legacy sequencer functions (kept for compatibility)
void set_drum_seq();
void set_melo_seq_12();
void set_melo_seq_34();

// Analog read function
int mozzi_analog_read_wrapper(unsigned char pin);

// Cursor position variables for UI
extern int cursor_select;
extern int cursor_x_drum, cursor_y_drum;
extern int cursor_x_melo_12, cursor_y_melo_12;
extern int cursor_x_melo_34, cursor_y_melo_34;

// Drum sequence String variables (for UI display)
extern String seq_drum_kick, seq_drum_snare3, seq_drum_snare4;
extern String seq_drum_hihat1, seq_drum_hihat2, seq_drum_clap1;
extern String seq_drum_water1, seq_drum_snap1;

// Melody sequence String variables (for UI display)
extern String seq_melo_oct0_8, seq_melo_key0_8, seq_melo_oct1_8, seq_melo_key1_8;
extern String seq_melo_oct0_16, seq_melo_key0_16, seq_melo_oct1_16, seq_melo_key1_16;
extern String seq_melo_oct2_8, seq_melo_key2_8, seq_melo_oct3_8, seq_melo_key3_8;
extern String seq_melo_oct2_16, seq_melo_key2_16, seq_melo_oct3_16, seq_melo_key3_16;

#endif