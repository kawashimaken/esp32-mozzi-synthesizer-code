// sequencer.cpp - Proper tempo control version
// K-POP style playback at BPM 120

#include "sequencer.h"
#include "song_library.h"

// Tempo control variables
static unsigned long step_counter = 0;
static unsigned long tempo_divider = 0;

// UI cursor position variable definitions
int cursor_select = 0;
int cursor_x_drum = 0, cursor_y_drum = 0;
int cursor_x_melo_12 = 0, cursor_y_melo_12 = 0;
int cursor_x_melo_34 = 0, cursor_y_melo_34 = 0;

// Drum sequence String variable definitions
String seq_drum_kick = "";
String seq_drum_snare3 = "";
String seq_drum_snare4 = "";
String seq_drum_hihat1 = "";
String seq_drum_hihat2 = "";
String seq_drum_clap1 = "";
String seq_drum_water1 = "";
String seq_drum_snap1 = "";

// Melody sequence String variable definitions
String seq_melo_oct0_8 = "";
String seq_melo_key0_8 = "";
String seq_melo_oct1_8 = "";
String seq_melo_key1_8 = "";
String seq_melo_oct0_16 = "";
String seq_melo_key0_16 = "";
String seq_melo_oct1_16 = "";
String seq_melo_key1_16 = "";
String seq_melo_oct2_8 = "";
String seq_melo_key2_8 = "";
String seq_melo_oct3_8 = "";
String seq_melo_key3_8 = "";
String seq_melo_oct2_16 = "";
String seq_melo_key2_16 = "";
String seq_melo_oct3_16 = "";
String seq_melo_key3_16 = "";

void sequencer_init() {
  Serial.println("=== K-POP Style Sequencer Initialization ===");
  
  // K-POP suitable tempo setting
  // CONTROL_RATE = 128Hz
  // BPM 120 = 2 beats/sec = 8 beats/sec (16th notes)
  // 128Hz / 8 = 16 → 16 control cycles per 16th note
  tempo = 32;  // 16th note tempo
  tempo_divider = 0;
  step_counter = 0;
  
  Serial.print("Setting tempo to: ");
  Serial.print(tempo);
  Serial.println(" (BPM ~120)");
  
  // Initialize long song
  init_long_song();
  
  // Set audio sample frequencies
  set_freq();
  
  Serial.println("K-POP sequencer initialized:");
  Serial.print("- Tempo divider: ");
  Serial.println(tempo);
  Serial.print("- Master count: ");
  Serial.println(master_count);
  Serial.print("- Song playing: ");
  Serial.println(song_playing ? "YES" : "NO");
  Serial.println("- Expected BPM: ~120");
}

void sequencer_update() {
  // Proper tempo control
  tempo_divider++;
  
  // Advance step when tempo is reached
  if (tempo_divider >= tempo) {
    tempo_divider = 0;
    step_counter++;
    
    // Update long song progress (increment master_count)
    update_long_song();
    
    // Debug output (first 32 steps, then every 32 steps)
    if (master_count < 32 || master_count % 32 == 0) {
      Serial.print("♪ Step: ");
      Serial.print(master_count);
      Serial.print("/256 | Pattern: ");
      Serial.print(get_current_pattern());
      Serial.print(" | Section: ");
      Serial.print(get_current_section_name());
      Serial.print(" | Progress: ");
      Serial.print(get_song_progress_percent(), 1);
      Serial.println("%");
    }
    
    // K-POP style drum and melody processing
    long_song_drum_part();
    long_song_melo_part();
    
    // Dynamic processing based on current section
    dynamic_section_processing();
  }
}

void long_song_drum_part() {
  // K-POP style drum processing
  if (song_playing && !song_finished) {
    drum_part();
  }
}

void long_song_melo_part() {
  // K-POP style melody processing
  if (song_playing && !song_finished) {
    melo_part();
  }
}

void dynamic_section_processing() {
  // Dynamic processing based on section
  // Dynamically adjust ADSR parameters
  int section_type = get_current_section_type();
  
  switch(current_section) {
    case SECTION_INTRO:
      // Intro: Clean and minimal
      attack_time = 3;
      decay_time = 35;
      sustain_time = 180;
      release_time = 120;
      break;
      
    case SECTION_VERSE:
      // Verse: Tight groove
      attack_time = 2;
      decay_time = 30;
      sustain_time = 200;
      release_time = 100;
      break;
      
    case SECTION_CHORUS:
      // Chorus: Full energy
      attack_time = 1;
      decay_time = 25;
      sustain_time = 250;
      release_time = 140;
      break;
      
    case SECTION_OUTRO:
      // Outro: Fade out
      attack_time = 4;
      decay_time = 40;
      sustain_time = 150;
      release_time = 180;
      break;
  }
}

float get_section_volume_multiplier() {
  // Volume adjustment based on section
  switch(current_section) {
    case SECTION_INTRO:  return 0.8f;
    case SECTION_VERSE:  return 0.9f;
    case SECTION_CHORUS: return 1.0f;
    case SECTION_OUTRO:  return 0.7f;
    default: return 1.0f;
  }
}

int get_current_section_type() {
  return (int)current_section;
}

bool should_play_water_track() {
  // Minimize water track in K-POP style
  if (current_section == SECTION_CHORUS) {
    return false; // Disabled in chorus
  }
  return (master_count % 8 == 0); // Only once every 8 steps
}

bool is_long_song_active() {
  return song_playing && !song_finished;
}

int mozzi_analog_read_wrapper(unsigned char pin) {
  return mozzi_analog_read(pin);
}

void set_drum_seq() {
  // Get current pattern and song data
  int current_pattern = get_current_pattern();
  const SongInfo* song = get_current_song_info();
  
  seq_drum_kick = "";
  seq_drum_snare3 = "";
  seq_drum_snare4 = "";
  seq_drum_hihat1 = "";
  seq_drum_hihat2 = "";
  seq_drum_clap1 = "";
  seq_drum_water1 = "";
  seq_drum_snap1 = "";
  
  // Convert from current song pattern to String format
  for (int i = 0; i < PATTERN_LENGTH; i++) {
    seq_drum_kick += (song->drum_patterns[current_pattern][0][i] ? "1" : "0");
    seq_drum_snare3 += (song->drum_patterns[current_pattern][1][i] ? "1" : "0");
    seq_drum_snare4 += (song->drum_patterns[current_pattern][2][i] ? "1" : "0");
    seq_drum_hihat1 += (song->drum_patterns[current_pattern][3][i] ? "1" : "0");
    seq_drum_hihat2 += (song->drum_patterns[current_pattern][4][i] ? "1" : "0");
    seq_drum_clap1 += (song->drum_patterns[current_pattern][5][i] ? "1" : "0");
    seq_drum_water1 += (song->drum_patterns[current_pattern][6][i] ? "1" : "0");
    seq_drum_snap1 += (song->drum_patterns[current_pattern][7][i] ? "1" : "0");
  }
}

void set_melo_seq_12() {
  // Get current pattern and song data
  int current_pattern = get_current_pattern();
  const SongInfo* song = get_current_song_info();
  
  seq_melo_oct0_8 = "";
  seq_melo_key0_8 = "";
  seq_melo_oct1_8 = "";
  seq_melo_key1_8 = "";
  seq_melo_oct0_16 = "";
  seq_melo_key0_16 = "";
  seq_melo_oct1_16 = "";
  seq_melo_key1_16 = "";
  
  // Convert melody data to String format
  for (int i = 0; i < 8; i++) {
    seq_melo_oct0_8 += String(song->melo_patterns[current_pattern][0][i]);
    seq_melo_key0_8 += (song->melo_trig_patterns[current_pattern][0][i] ? "1" : "0");
    seq_melo_oct1_8 += String(song->melo_patterns[current_pattern][1][i]);
    seq_melo_key1_8 += (song->melo_trig_patterns[current_pattern][1][i] ? "1" : "0");
  }
  
  for (int i = 8; i < 16; i++) {
    seq_melo_oct0_16 += String(song->melo_patterns[current_pattern][0][i]);
    seq_melo_key0_16 += (song->melo_trig_patterns[current_pattern][0][i] ? "1" : "0");
    seq_melo_oct1_16 += String(song->melo_patterns[current_pattern][1][i]);
    seq_melo_key1_16 += (song->melo_trig_patterns[current_pattern][1][i] ? "1" : "0");
  }
}

void set_melo_seq_34() {
  // Get current pattern and song data
  int current_pattern = get_current_pattern();
  const SongInfo* song = get_current_song_info();
  
  // Clear String variables
  seq_melo_oct2_8 = "";
  seq_melo_key2_8 = "";
  seq_melo_oct3_8 = "";
  seq_melo_key3_8 = "";
  seq_melo_oct2_16 = "";
  seq_melo_key2_16 = "";
  seq_melo_oct3_16 = "";
  seq_melo_key3_16 = "";
  
  // Convert first 8 steps of melody tracks 2,3 to String format
  for (int i = 0; i < 8; i++) {
    seq_melo_oct2_8 += String(song->melo_patterns[current_pattern][2][i]);
    seq_melo_key2_8 += (song->melo_trig_patterns[current_pattern][2][i] ? "1" : "0");
    seq_melo_oct3_8 += String(song->melo_patterns[current_pattern][3][i]);
    seq_melo_key3_8 += (song->melo_trig_patterns[current_pattern][3][i] ? "1" : "0");
  }
  
  // Convert last 8 steps of melody tracks 2,3 to String format
  for (int i = 8; i < 16; i++) {
    seq_melo_oct2_16 += String(song->melo_patterns[current_pattern][2][i]);
    seq_melo_key2_16 += (song->melo_trig_patterns[current_pattern][2][i] ? "1" : "0");
    seq_melo_oct3_16 += String(song->melo_patterns[current_pattern][3][i]);
    seq_melo_key3_16 += (song->melo_trig_patterns[current_pattern][3][i] ? "1" : "0");
  }
}