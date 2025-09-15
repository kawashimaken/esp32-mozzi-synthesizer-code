// K-POP style song_structure.cpp
// Modern pop music composition structure

#include "structure.h"

// K-POP style song structure (which patterns to play in order)
const int kpop_song_structure[NUM_PATTERNS] = {
  0,  // Intro 1 - minimal
  1,  // Intro 2 - add harmony
  2,  // Pre-verse - characteristic K-POP
  3,  // Verse 1 - clean
  
  4,  // Verse 2 - variation
  5,  // Pre-chorus - build tension
  6,  // Drop preparation - suspense
  7,  // Verse 3 - development
  8,  // Chorus 1 - powerful (melody focus)
  9,  // Chorus 2 - full arrangement
  10, // Chorus 3 - climax
  11, // Bridge 1 - melody emphasis
  12, // Bridge 2 - build up
  13, // Final chorus - full power
  14, // Outro 1 - fade out start
  15  // Outro 2 - complete fade out
};