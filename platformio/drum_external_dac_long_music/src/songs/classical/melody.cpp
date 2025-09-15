#include "melody.h"

// Classical/Mozart Style 16-pattern melody pattern library
// Based on "Eine kleine Nachtmusik" K.525 with modern electronic arrangement
const int classical_melo_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH] = {
    // Pattern 0: Intro - Gentle statement of main motif
    {
        {67, 0, 0, 0, 67, 0, 0, 0, 67, 0, 0, 0, 67, 0, 0, 0}, // Bass - G major foundation
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},     // Bass harmony
        {79, 0, 0, 0, 83, 0, 0, 0, 79, 0, 0, 0, 86, 0, 0, 0}, // Chord - G major triad hints
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}      // Lead - silence
    },
    // Pattern 1: Theme entrance - First phrase of Eine kleine Nachtmusik
    {
        {67, 0, 0, 0, 67, 0, 0, 0, 62, 0, 0, 0, 62, 0, 0, 0},     // Bass - G to D
        {74, 0, 0, 0, 74, 0, 0, 0, 69, 0, 0, 0, 69, 0, 0, 0},     // Bass harmony - thirds
        {79, 0, 83, 0, 86, 0, 83, 0, 74, 0, 78, 0, 81, 0, 78, 0}, // Chord - arpeggiated accompaniment
        {91, 0, 91, 0, 95, 0, 91, 0, 86, 0, 86, 0, 90, 0, 86, 0}  // Lead - main melody (G-G-D-G, D-D-A-D)
    },
    // Pattern 2: Development - Second phrase
    {
        {67, 0, 71, 0, 74, 0, 71, 0, 67, 0, 71, 0, 74, 0, 71, 0},         // Bass - walking pattern
        {74, 0, 78, 0, 81, 0, 78, 0, 74, 0, 78, 0, 81, 0, 78, 0},         // Bass harmony - parallel motion
        {79, 83, 86, 90, 93, 90, 86, 83, 79, 83, 86, 90, 93, 90, 86, 83}, // Chord - continuous arpeggios
        {91, 95, 98, 95, 91, 88, 91, 95, 91, 95, 98, 95, 91, 88, 91, 95}  // Lead - flowing melody
    },
    // Pattern 3: Menuet character - Dance-like elegance
    {
        {67, 0, 0, 74, 0, 0, 67, 0, 0, 74, 0, 0, 67, 0, 0, 0},            // Bass - waltz-like pattern
        {79, 0, 0, 86, 0, 0, 79, 0, 0, 86, 0, 0, 79, 0, 0, 0},            // Bass harmony - waltz thirds
        {91, 86, 83, 91, 86, 83, 91, 86, 83, 91, 86, 83, 91, 86, 83, 79}, // Chord - descending scales
        {103, 0, 98, 103, 0, 98, 103, 0, 98, 103, 0, 98, 103, 98, 95, 91} // Lead - high melody
    },
    // Pattern 4: Variation theme - Ornamented version
    {
        {67, 69, 71, 72, 74, 72, 71, 69, 67, 69, 71, 72, 74, 72, 71, 69},     // Bass - scale passages
        {74, 76, 78, 79, 81, 79, 78, 76, 74, 76, 78, 79, 81, 79, 78, 76},     // Bass harmony - parallel scales
        {79, 83, 86, 90, 93, 95, 98, 95, 93, 90, 86, 83, 79, 83, 86, 90},     // Chord - ascending/descending
        {91, 93, 95, 96, 98, 100, 101, 103, 101, 100, 98, 96, 95, 93, 91, 88} // Lead - virtuosic passage
    },
    // Pattern 5: Development section - Contrapuntal texture
    {
        {67, 0, 74, 0, 71, 0, 78, 0, 74, 0, 81, 0, 78, 0, 74, 0},                  // Bass - jumping intervals
        {79, 0, 74, 0, 83, 0, 78, 0, 86, 0, 81, 0, 90, 0, 86, 0},                  // Bass harmony - counterpoint
        {91, 88, 95, 91, 98, 95, 102, 98, 95, 91, 88, 95, 91, 88, 95, 91},         // Chord - interwoven lines
        {103, 100, 98, 103, 100, 98, 105, 103, 100, 98, 105, 103, 100, 98, 95, 91} // Lead - elaborate counterpoint
    },
    // Pattern 6: Fugue-like - Multiple voice entries
    {
        {67, 0, 67, 71, 74, 0, 74, 78, 81, 0, 81, 74, 71, 67, 71, 74}, // Bass - fugue subject
        {0, 0, 79, 0, 79, 83, 86, 0, 86, 90, 93, 0, 93, 86, 83, 79},   // Bass harmony - second entry
        {0, 0, 0, 0, 91, 0, 91, 95, 98, 0, 98, 102, 105, 0, 105, 98},  // Chord - third entry
        {0, 0, 0, 0, 0, 0, 103, 0, 103, 107, 110, 0, 110, 114, 117, 0} // Lead - fourth entry (stretto)
    },
    // Pattern 7: Modulation to dominant - Building tension
    {
        {67, 69, 71, 72, 74, 76, 78, 79, 81, 83, 84, 86, 88, 89, 91, 93},             // Bass - ascending sequence
        {74, 76, 78, 79, 81, 83, 84, 86, 88, 90, 91, 93, 95, 96, 98, 100},            // Bass harmony - parallel ascent
        {79, 83, 86, 90, 93, 95, 98, 102, 105, 107, 110, 114, 117, 119, 122, 126},    // Chord - climbing harmony
        {91, 95, 98, 102, 105, 107, 110, 114, 117, 119, 122, 126, 129, 131, 134, 138} // Lead - soaring melody
    },
    // Pattern 8: D major - Establishing the key
    {
        {74, 0, 0, 0, 74, 0, 0, 0, 69, 0, 0, 0, 69, 0, 0, 0},     // Bass - D major foundation
        {81, 0, 0, 0, 81, 0, 0, 0, 76, 0, 0, 0, 76, 0, 0, 0},     // Bass harmony - dominant harmony
        {86, 0, 90, 0, 93, 0, 90, 0, 81, 0, 85, 0, 88, 0, 85, 0}, // Chord - D major arpeggios
        {98, 0, 98, 0, 102, 0, 98, 0, 93, 0, 93, 0, 97, 0, 93, 0} // Lead - melody in D major
    },
    // Pattern 9: Variation in dominant - Elegant development
    {
        {74, 0, 78, 0, 81, 0, 78, 0, 74, 0, 78, 0, 81, 0, 78, 0},                      // Bass - D major walking
        {81, 0, 85, 0, 88, 0, 85, 0, 81, 0, 85, 0, 88, 0, 85, 0},                      // Bass harmony - supporting
        {86, 90, 93, 97, 100, 97, 93, 90, 86, 90, 93, 97, 100, 97, 93, 90},            // Chord - flowing arpeggios
        {98, 102, 105, 109, 112, 109, 105, 102, 98, 102, 105, 109, 112, 109, 105, 102} // Lead - elaborate melody
    },
    // Pattern 10: Recapitulation - Return to G major
    {
        {67, 0, 0, 0, 67, 0, 0, 0, 62, 0, 0, 0, 62, 0, 0, 0},     // Bass - return to opening
        {74, 0, 0, 0, 74, 0, 0, 0, 69, 0, 0, 0, 69, 0, 0, 0},     // Bass harmony - familiar pattern
        {79, 0, 83, 0, 86, 0, 83, 0, 74, 0, 78, 0, 81, 0, 78, 0}, // Chord - original accompaniment
        {91, 0, 91, 0, 95, 0, 91, 0, 86, 0, 86, 0, 90, 0, 86, 0}  // Lead - main theme returns
    },
    // Pattern 11: Final development - Building to climax
    {
        {67, 71, 74, 78, 81, 74, 78, 82, 86, 82, 78, 85, 88, 85, 82, 90},             // Bass - virtuosic passage
        {74, 78, 81, 85, 88, 81, 85, 89, 93, 89, 85, 92, 95, 92, 89, 97},             // Bass harmony - parallel
        {79, 83, 86, 90, 93, 95, 98, 102, 105, 107, 110, 114, 117, 119, 122, 126},    // Chord - ascending scales
        {91, 95, 98, 102, 105, 107, 110, 114, 117, 119, 122, 126, 129, 131, 134, 138} // Lead - brilliant ascent
    },
    // Pattern 12: Climax - Full orchestral power
    {
        {67, 74, 81, 88, 67, 74, 81, 88, 67, 74, 81, 88, 67, 74, 81, 88},                // Bass - powerful arpeggios
        {79, 86, 93, 100, 79, 86, 93, 100, 79, 86, 93, 100, 79, 86, 93, 100},            // Bass harmony - octave higher
        {91, 98, 105, 112, 91, 98, 105, 112, 91, 98, 105, 112, 91, 98, 105, 112},        // Chord - brilliant texture
        {103, 110, 117, 124, 103, 110, 117, 124, 103, 110, 117, 124, 103, 110, 117, 124} // Lead - triumphant climax
    },
    // Pattern 13: Resolution - Satisfying conclusion
    {
        {67, 0, 71, 0, 74, 0, 71, 0, 67, 0, 71, 0, 67, 0, 0, 0}, // Bass - resolving to tonic
        {74, 0, 78, 0, 81, 0, 78, 0, 74, 0, 78, 0, 74, 0, 0, 0}, // Bass harmony - following
        {79, 0, 83, 0, 86, 0, 83, 0, 79, 0, 83, 0, 79, 0, 0, 0}, // Chord - simple resolution
        {91, 0, 95, 0, 98, 0, 95, 0, 91, 0, 88, 0, 91, 0, 0, 0}  // Lead - melodic resolution
    },
    // Pattern 14: Coda preparation - Classical wind down
    {
        {67, 0, 0, 0, 71, 0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0}, // Bass - gentle movement
        {74, 0, 0, 0, 78, 0, 0, 0, 74, 0, 0, 0, 0, 0, 0, 0}, // Bass harmony - following
        {79, 0, 0, 0, 83, 0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0}, // Chord - sparse texture
        {91, 0, 0, 0, 88, 0, 0, 0, 91, 0, 0, 0, 0, 0, 0, 0}  // Lead - final phrase
    },
    // Pattern 15: Final coda - Perfect authentic cadence
    {
        {67, 0, 0, 0, 0, 0, 0, 0, 67, 0, 0, 0, 0, 0, 0, 0}, // Bass - final tonic
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   // Bass harmony - silence
        {79, 0, 0, 0, 0, 0, 0, 0, 79, 0, 0, 0, 0, 0, 0, 0}, // Chord - final chord
        {91, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}   // Lead - final note
    }};

// Classical Style melody trigger patterns
const boolean classical_melo_trig_patterns[NUM_PATTERNS][NUM_MELO_TRACKS][PATTERN_LENGTH] = {
    // Pattern 0: Intro - Minimal triggers
    {
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Bass harmony
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Chord
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Lead
    },
    // Pattern 1: Theme entrance
    {
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass harmony
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Chord
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}  // Lead
    },
    // Pattern 2: Development
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 3: Menuet character
    {
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}, // Bass
        {1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 4: Variation theme
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 5: Development section
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 6: Fugue-like
    {
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1}, // Bass
        {0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1}, // Bass harmony
        {0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1}, // Chord
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0}  // Lead
    },
    // Pattern 7: Modulation
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 8: Dominant key
    {
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass harmony
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Chord
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}  // Lead
    },
    // Pattern 9: Variation in dominant
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 10: Recapitulation
    {
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, // Bass harmony
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, // Chord
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}  // Lead
    },
    // Pattern 11: Final development
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 12: Climax
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Bass harmony
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // Chord
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}  // Lead
    },
    // Pattern 13: Resolution
    {
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // Bass
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // Bass harmony
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0}, // Chord
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0}  // Lead
    },
    // Pattern 14: Coda preparation
    {
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Bass
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Bass harmony
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Chord
        {1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}  // Lead
    },
    // Pattern 15: Final coda
    {
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Bass
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Bass harmony
        {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // Chord
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Lead
    }};