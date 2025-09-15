#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "config.h"

// Initialize sequencer
void sequencer_init();

// Update sequencer
void sequencer_update();

// Set drum sequence
void set_drum_seq();

// Set melody sequence for tracks 1 and 2
void set_melo_seq_12();

// Set melody sequence for tracks 3 and 4
void set_melo_seq_34();

#endif // SEQUENCER_H
