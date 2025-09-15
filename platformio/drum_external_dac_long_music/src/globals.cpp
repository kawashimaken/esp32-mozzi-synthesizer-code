#include "config.h"

// Song control
int master_count = 0;
int pattern_count = 0;
int current_section = SECTION_INTRO;
int section_progress = 0;
bool song_playing = true;
bool song_finished = false;
int tempo = 0;


// ADSR settings
int attack_time = 2;
int decay_time = 30;
int sustain_time = 150;
int release_time = 100;