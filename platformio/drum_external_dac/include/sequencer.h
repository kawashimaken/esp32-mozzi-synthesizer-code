#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "config.h"

// Sequencer initialization
void sequencer_init();

// Sequencer update
void sequencer_update();

// Drum sequence setup
void set_drum_seq();

// Melody sequence setup
void set_melo_seq_12();
void set_melo_seq_34();

#endif // SEQUENCER_H