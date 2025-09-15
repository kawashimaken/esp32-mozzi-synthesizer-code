// song_structure.cpp - Multi-song support version
#include "song_structure.h"
#include "song_library.h"

// Extended sequence arrays (256 steps) - defined only here
boolean seq_drum[NUM_DRUM_TRACKS][SEQUENCE_LENGTH];
int seq_melo[NUM_MELO_TRACKS][SEQUENCE_LENGTH];
boolean seq_melo_trig[NUM_MELO_TRACKS][SEQUENCE_LENGTH];

// Song management function implementation
void init_long_song() {
  // Get current song data
  const SongInfo* song = get_current_song_info();
  
  // Build 256-step sequence from current song's pattern library
  for (int pattern_idx = 0; pattern_idx < NUM_PATTERNS; pattern_idx++) {
    int current_pattern = song->structure[pattern_idx];
    int start_step = pattern_idx * PATTERN_LENGTH;
    
    // Copy drum patterns from current song
    for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
      for (int step = 0; step < PATTERN_LENGTH; step++) {
        seq_drum[track][start_step + step] = song->drum_patterns[current_pattern][track][step];
      }
    }
    
    // Copy melody patterns from current song
    for (int track = 0; track < NUM_MELO_TRACKS; track++) {
      for (int step = 0; step < PATTERN_LENGTH; step++) {
        seq_melo[track][start_step + step] = song->melo_patterns[current_pattern][track][step];
        seq_melo_trig[track][start_step + step] = song->melo_trig_patterns[current_pattern][track][step];
      }
    }
  }
  
  // Initialize playback state
  master_count = 0;
  pattern_count = 0;
  current_section = SECTION_INTRO;
  section_progress = 0;
  song_playing = true;
  song_finished = false;
}

void update_long_song() {
  // Advance master count
  master_count++;
  
  // Check if reached end of sequence
  if (master_count >= SEQUENCE_LENGTH) {
    song_finished = true;
    song_playing = false;
    master_count = SEQUENCE_LENGTH - 1; // Stop at last step
    return;
  }
  
  // Calculate current pattern number
  pattern_count = master_count / PATTERN_LENGTH;
  
  // Section determination
  if (pattern_count < INTRO_PATTERNS) {
    current_section = SECTION_INTRO;
    section_progress = pattern_count;
  } else if (pattern_count < INTRO_PATTERNS + VERSE_PATTERNS) {
    current_section = SECTION_VERSE;
    section_progress = pattern_count - INTRO_PATTERNS;
  } else if (pattern_count < INTRO_PATTERNS + VERSE_PATTERNS + CHORUS_PATTERNS) {
    current_section = SECTION_CHORUS;
    section_progress = pattern_count - INTRO_PATTERNS - VERSE_PATTERNS;
  } else {
    current_section = SECTION_OUTRO;
    section_progress = pattern_count - INTRO_PATTERNS - VERSE_PATTERNS - CHORUS_PATTERNS;
  }
}

int get_current_pattern() {
  return pattern_count;
}

bool is_song_finished() {
  return song_finished;
}

void start_song() {
  init_long_song();
}

void stop_song() {
  song_playing = false;
  master_count = 0;
}

void reset_song() {
  master_count = 0;
  pattern_count = 0;
  current_section = SECTION_INTRO;
  section_progress = 0;
  song_playing = true;
  song_finished = false;
}

const char* get_current_section_name() {
  switch(current_section) {
    case SECTION_INTRO:  return "INTRO";
    case SECTION_VERSE:  return "VERSE";
    case SECTION_CHORUS: return "CHORUS";
    case SECTION_OUTRO:  return "OUTRO";
    default: return "UNKNOWN";
  }
}

float get_song_progress_percent() {
  return (float)master_count / SEQUENCE_LENGTH * 100.0;
}

int get_section_progress() {
  return section_progress;
}

// Song switching functionality
void switch_to_song(int song_id) {
  // Stop current playback
  stop_song();
  
  // Switch to new song
  set_current_song(song_id);
  
  // Restart with new song data
  start_song();
}

int get_current_song_id() {
  return current_song_id;
}