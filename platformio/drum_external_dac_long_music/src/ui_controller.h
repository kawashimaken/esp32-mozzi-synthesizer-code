#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <Arduino.h>

// UI initialization functions
void ui_init();
void ui_task_init();

// UI update function
void ui_update();

// Screen display functions
void drum_seq_disp();
void melo_seq_disp_12();
void melo_seq_disp_34();
void waveform_disp();  // New waveform display mode

// Helper functions
bool checkBeat(String sequence, int step);
bool hasActiveDrumBeat();
int calculateBeatIntensity();
void updateDynamicWaveform();
void drawDynamicWaveform();
void drawDiamond(int x, int y, int size, bool filled);
void drawPulse(int x, int y, int width, bool active);

// External variables (variables defined in sequencer.h)
extern int cursor_select;
extern int cursor_x_drum, cursor_y_drum;
extern int cursor_x_melo_12, cursor_y_melo_12;
extern int cursor_x_melo_34, cursor_y_melo_34;
extern int master_count;

// String variables used from sequencer
extern String seq_drum_kick, seq_drum_snare3, seq_drum_snare4;
extern String seq_drum_hihat1, seq_drum_hihat2, seq_drum_clap1;
extern String seq_drum_water1, seq_drum_snap1;
extern String seq_melo_oct0_8, seq_melo_key0_8, seq_melo_oct1_8, seq_melo_key1_8;
extern String seq_melo_oct0_16, seq_melo_key0_16, seq_melo_oct1_16, seq_melo_key1_16;
extern String seq_melo_oct2_8, seq_melo_key2_8, seq_melo_oct3_8, seq_melo_key3_8;
extern String seq_melo_oct2_16, seq_melo_key2_16, seq_melo_oct3_16, seq_melo_key3_16;

// Sequencer set functions
extern void set_drum_seq();
extern void set_melo_seq_12();
extern void set_melo_seq_34();

// song_structure functions
extern const char* get_current_section_name();
extern int get_current_pattern();
extern float get_song_progress_percent();

#endif