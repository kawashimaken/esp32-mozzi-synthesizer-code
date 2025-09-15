#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include "config.h"

struct SongInfo {
  const char* title;
  const char* style;
  int bpm;
  const int* structure;
  const boolean (*drum_patterns)[NUM_DRUM_TRACKS][PATTERN_LENGTH];
  const int (*melo_patterns)[NUM_MELO_TRACKS][PATTERN_LENGTH];
  const boolean (*melo_trig_patterns)[NUM_MELO_TRACKS][PATTERN_LENGTH];
};

void init_song_library();
void set_current_song(int song_id);
const SongInfo* get_current_song_info();
int get_song_count();

#endif