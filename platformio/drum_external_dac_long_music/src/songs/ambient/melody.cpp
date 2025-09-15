#include "melody.h"

// Ambient/Training Style 16-pattern melody pattern library  
// Gentle, flowing melodies for concentration and relaxation
const int ambient_melo_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH] = {
  // Pattern 0: Intro - Gentle pad
  {
    { 60, 0, 0, 0, 60, 0, 0, 0, 60, 0, 0, 0, 60, 0, 0, 0 }, // Bass pad - C
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },     // Bass harmony
    { 0, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0, 72, 0, 0, 0 },   // Chord - soft C major
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }      // Lead - silence
  },
  // Pattern 1: Gentle movement
  {
    { 60, 0, 0, 0, 60, 0, 0, 0, 62, 0, 0, 0, 60, 0, 0, 0 }, // Bass - C to D and back
    { 0, 0, 67, 0, 0, 0, 69, 0, 0, 0, 67, 0, 0, 0, 65, 0 }, // Bass harmony - gentle movement
    { 72, 0, 0, 0, 76, 0, 0, 0, 72, 0, 0, 0, 79, 0, 0, 0 }, // Chord - C major progression
    { 0, 0, 0, 0, 0, 0, 84, 0, 0, 0, 0, 0, 0, 0, 86, 0 }    // Lead - subtle melody
  },
  // Pattern 2: Steady flow
  {
    { 60, 0, 62, 0, 60, 0, 58, 0, 60, 0, 62, 0, 60, 0, 58, 0 }, // Bass - flowing pattern
    { 67, 0, 69, 0, 67, 0, 65, 0, 67, 0, 69, 0, 67, 0, 65, 0 }, // Bass harmony - parallel
    { 72, 0, 76, 0, 79, 0, 76, 0, 72, 0, 76, 0, 79, 0, 76, 0 }, // Chord - arpeggiated
    { 84, 0, 86, 0, 84, 0, 81, 0, 84, 0, 86, 0, 84, 0, 81, 0 }  // Lead - gentle melody
  },
  // Pattern 3: Meditative harmony
  {
    { 60, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0 }, // Bass - minimal
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Bass harmony - silence
    { 72, 0, 0, 0, 76, 0, 0, 0, 79, 0, 0, 0, 76, 0, 0, 0 }, // Chord - slow progression
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }    // Lead - silence
  },
  // Pattern 4: Training rhythm
  {
    { 60, 0, 60, 0, 62, 0, 62, 0, 64, 0, 64, 0, 62, 0, 60, 0 }, // Bass - stepping pattern
    { 67, 0, 67, 0, 69, 0, 69, 0, 71, 0, 71, 0, 69, 0, 67, 0 }, // Bass harmony - supporting
    { 72, 0, 76, 0, 79, 0, 81, 0, 84, 0, 81, 0, 79, 0, 76, 0 }, // Chord - ascending/descending
    { 84, 0, 0, 0, 86, 0, 0, 0, 88, 0, 0, 0, 86, 0, 84, 0 }    // Lead - motivational
  },
  // Pattern 5: Flow state
  {
    { 60, 62, 64, 65, 60, 62, 64, 65, 60, 62, 64, 65, 60, 62, 64, 65 }, // Bass - continuous flow
    { 67, 69, 71, 72, 67, 69, 71, 72, 67, 69, 71, 72, 67, 69, 71, 72 }, // Bass harmony - flowing
    { 72, 0, 76, 0, 79, 0, 81, 0, 72, 0, 76, 0, 79, 0, 81, 0 }, // Chord - steady progression
    { 84, 0, 86, 0, 88, 0, 89, 0, 91, 0, 89, 0, 88, 0, 86, 0 }  // Lead - flowing melody
  },
  // Pattern 6: Deep focus
  {
    { 60, 0, 0, 0, 65, 0, 0, 0, 60, 0, 0, 0, 67, 0, 0, 0 }, // Bass - wide intervals
    { 0, 0, 72, 0, 0, 0, 76, 0, 0, 0, 72, 0, 0, 0, 79, 0 }, // Bass harmony - sparse
    { 72, 76, 79, 84, 0, 0, 0, 0, 72, 76, 79, 84, 0, 0, 0, 0 }, // Chord - block chords
    { 0, 0, 0, 0, 0, 0, 96, 0, 0, 0, 0, 0, 0, 0, 94, 0 }    // Lead - high and sparse
  },
  // Pattern 7: Transition
  {
    { 60, 0, 62, 0, 64, 0, 65, 0, 67, 0, 65, 0, 64, 0, 62, 0 }, // Bass - scale passage
    { 67, 0, 69, 0, 71, 0, 72, 0, 74, 0, 72, 0, 71, 0, 69, 0 }, // Bass harmony - parallel
    { 72, 76, 79, 84, 86, 84, 79, 76, 72, 76, 79, 84, 86, 84, 79, 76 }, // Chord - arpeggiated
    { 84, 86, 88, 89, 91, 93, 94, 96, 94, 93, 91, 89, 88, 86, 84, 81 }  // Lead - ascending/descending
  },
  // Pattern 8: Active training
  {
    { 60, 0, 64, 0, 67, 0, 64, 0, 60, 0, 64, 0, 67, 0, 64, 0 }, // Bass - triad pattern
    { 72, 0, 76, 0, 79, 0, 76, 0, 72, 0, 76, 0, 79, 0, 76, 0 }, // Bass harmony - octave higher
    { 84, 0, 88, 0, 91, 0, 88, 0, 84, 0, 88, 0, 91, 0, 88, 0 }, // Chord - another octave
    { 96, 0, 94, 0, 91, 0, 89, 0, 91, 0, 94, 0, 96, 0, 98, 0 }  // Lead - energetic but controlled
  },
  // Pattern 9: Calm intensity
  {
    { 60, 0, 0, 0, 67, 0, 0, 0, 60, 0, 0, 0, 67, 0, 0, 0 }, // Bass - perfect fifth
    { 64, 0, 0, 0, 71, 0, 0, 0, 64, 0, 0, 0, 71, 0, 0, 0 }, // Bass harmony - major third and seventh
    { 72, 76, 79, 0, 79, 76, 72, 0, 72, 76, 79, 0, 79, 76, 72, 0 }, // Chord - rolling pattern
    { 84, 0, 86, 88, 89, 0, 91, 0, 89, 0, 88, 86, 84, 0, 86, 0 }    // Lead - gentle waves
  },
  // Pattern 10: Breathing space
  {
    { 60, 0, 0, 0, 0, 0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0 }, // Bass - breath rhythm
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Bass harmony - silence
    { 72, 0, 0, 0, 0, 0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0 }, // Chord - minimal
    { 0, 0, 0, 0, 96, 0, 0, 0, 0, 0, 0, 0, 94, 0, 0, 0 }  // Lead - breathing accents
  },
  // Pattern 11: Building energy
  {
    { 60, 0, 60, 62, 64, 0, 64, 65, 67, 0, 67, 69, 71, 72, 74, 76 }, // Bass - accelerating
    { 67, 0, 67, 69, 71, 0, 71, 72, 74, 0, 74, 76, 78, 79, 81, 83 }, // Bass harmony - parallel build
    { 72, 0, 76, 79, 81, 0, 84, 86, 88, 0, 91, 93, 94, 96, 98, 100 }, // Chord - ascending
    { 84, 0, 86, 88, 89, 0, 91, 93, 94, 0, 96, 98, 100, 101, 103, 105 } // Lead - soaring
  },
  // Pattern 12: Peak focus
  {
    { 60, 64, 67, 72, 60, 64, 67, 72, 60, 64, 67, 72, 60, 64, 67, 72 }, // Bass - steady arpeggios
    { 72, 76, 79, 84, 72, 76, 79, 84, 72, 76, 79, 84, 72, 76, 79, 84 }, // Bass harmony - octave higher
    { 84, 88, 91, 96, 84, 88, 91, 96, 84, 88, 91, 96, 84, 88, 91, 96 }, // Chord - consistent pattern
    { 96, 98, 100, 101, 103, 101, 100, 105, 103, 101, 100, 108, 105, 103, 101, 110 } // Lead - peak melody
  },
  // Pattern 13: Wind down preparation
  {
    { 60, 0, 64, 0, 67, 0, 64, 0, 60, 0, 64, 0, 60, 0, 0, 0 }, // Bass - slowing down
    { 72, 0, 76, 0, 79, 0, 76, 0, 72, 0, 76, 0, 72, 0, 0, 0 }, // Bass harmony - following
    { 84, 0, 88, 0, 91, 0, 88, 0, 84, 0, 88, 0, 84, 0, 0, 0 }, // Chord - decreasing activity
    { 96, 0, 94, 0, 91, 0, 89, 0, 88, 0, 86, 0, 84, 0, 0, 0 }  // Lead - descending
  },
  // Pattern 14: Cool down
  {
    { 60, 0, 0, 0, 62, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0 }, // Bass - minimal movement
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },   // Bass harmony - silence
    { 72, 0, 0, 0, 76, 0, 0, 0, 72, 0, 0, 0, 0, 0, 0, 0 }, // Chord - sparse
    { 84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }    // Lead - fading away
  },
  // Pattern 15: Complete rest
  {
    { 60, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass - final note
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },  // Bass harmony - silence
    { 72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Chord - final chord
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }   // Lead - silence
  }
};

// Ambient Style melody trigger patterns
const boolean ambient_melo_trig_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH] = {
  // Pattern 0: Intro - Minimal triggers
  {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Bass pad
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass harmony
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // Lead
  },
  // Pattern 1: Gentle movement
  {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Bass
    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 }, // Bass harmony
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }  // Lead
  },
  // Pattern 2: Steady flow
  {
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass harmony
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Chord
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }  // Lead
  },
  // Pattern 3: Meditative
  {
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, // Bass
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass harmony
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // Lead
  },
  // Pattern 4: Training rhythm
  {
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass harmony
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Chord
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0 }  // Lead
  },
  // Pattern 5: Flow state
  {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Bass
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Bass harmony
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Chord
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }  // Lead
  },
  // Pattern 6: Deep focus
  {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Bass
    { 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0 }, // Bass harmony
    { 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }  // Lead
  },
  // Pattern 7: Transition
  {
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass harmony
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Chord
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // Lead
  },
  // Pattern 8: Active training
  {
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Bass harmony
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }, // Chord
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }  // Lead
  },
  // Pattern 9: Calm intensity
  {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Bass
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 }, // Bass harmony
    { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0 }, // Chord
    { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0 }  // Lead
  },
  // Pattern 10: Breathing space
  {
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, // Bass
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass harmony
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 }  // Lead
  },
  // Pattern 11: Building energy
  {
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }, // Bass
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }, // Bass harmony
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }, // Chord
    { 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }  // Lead
  },
  // Pattern 12: Peak focus
  {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Bass
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Bass harmony
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, // Chord
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }  // Lead
  },
  // Pattern 13: Wind down preparation
  {
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 }, // Bass
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 }, // Bass harmony
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 }, // Chord
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0 }  // Lead
  },
  // Pattern 14: Cool down
  {
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, // Bass
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass harmony
    { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, // Chord
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // Lead
  },
  // Pattern 15: Complete rest
  {
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Bass harmony
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, // Chord
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }  // Lead
  }
};