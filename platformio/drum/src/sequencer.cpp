// sequencer.cpp - Version with debounce processing added

#include "sequencer.h"
#include "audio_engine.h"
#include "input_handler.h"

// Global variables for debouncing
unsigned long last_button_time = 0;
const unsigned long debounce_delay = 150; // 150ms debounce time

// Record previous button states
bool prev_up = false;
bool prev_down = false;
bool prev_left = false;
bool prev_right = false;
bool prev_confirm = false;
bool prev_cancel = false;

// Function to detect rising edge of button state
bool button_pressed(int pin, bool &prev_state) {
  bool current_state = digitalRead(pin);
  bool pressed = (!prev_state && current_state);
  prev_state = current_state;
  return pressed;
}

void sequencer_init() {
  // Sequence data initialization is already done in config.h
}

void sequencer_update() {
  // Read envelope parameters
  sustain_time = map(mozzi_analog_read(A3_meter), 0, 4095, 500, 5);
  decay_time = map(mozzi_analog_read(A4_meter), 0, 4095, 500, 5);
  attack_time = map(mozzi_analog_read(A5_meter), 0, 4095, 500, 5);
  release_time = map(mozzi_analog_read(A2_meter), 0, 4095, 500, 5);

  if (trigger_delay_ready()) {
    set_freq();
    digitalRead(run_stop);
    digitalWrite(clock_out, LOW);

    if ((digitalRead(run_stop))) {
      melo_part();
      drum_part();
      master_count += 1;
      tempo += 1;
    }

    if (master_count == 16) {
      master_count = 0;
    }

    if (tempo == 2) {
      tempo = 0;
      digitalWrite(clock_out, HIGH);
    }

    trigger_delay_start(map(mozzi_analog_read(A0_meter), 0, 4096, 10, 500));
  }
}

void set_drum_seq() {
  unsigned long current_time = millis();
  
  // Check debounce time
  if (current_time - last_button_time >= debounce_delay) {
    // Process buttons with rising edge detection
    if (button_pressed(cross_button_up, prev_up)) {
      cursor_y_drum = max(0, cursor_y_drum - 1);
      last_button_time = current_time;
    }
    if (button_pressed(cross_button_down, prev_down)) {
      cursor_y_drum = min(7, cursor_y_drum + 1);
      last_button_time = current_time;
    }
    if (button_pressed(cross_button_right, prev_right)) {
      cursor_x_drum = min(15, cursor_x_drum + 1);
      last_button_time = current_time;
    }
    if (button_pressed(cross_button_left, prev_left)) {
      cursor_x_drum = max(0, cursor_x_drum - 1);
      last_button_time = current_time;
    }
    if (button_pressed(button_confirm, prev_confirm)) {
      seq_drum[cursor_y_drum][cursor_x_drum] = true;
      last_button_time = current_time;
    }
    if (button_pressed(button_cancel, prev_cancel)) {
      seq_drum[cursor_y_drum][cursor_x_drum] = false;
      last_button_time = current_time;
    }
  } else {
    // Update previous states even within debounce time
    prev_up = digitalRead(cross_button_up);
    prev_down = digitalRead(cross_button_down);
    prev_left = digitalRead(cross_button_left);
    prev_right = digitalRead(cross_button_right);
    prev_confirm = digitalRead(button_confirm);
    prev_cancel = digitalRead(button_cancel);
  }

  // Same as original code below (sequence string generation)
  seq_drum_kick = "";
  seq_drum_snare3 = "";
  seq_drum_snare4 = "";
  seq_drum_hihat1 = "";
  seq_drum_hihat2 = "";
  seq_drum_clap1 = "";
  seq_drum_water1 = "";
  seq_drum_snap1 = "";

  for (int i = 0; i < 16; i++) {
    if (seq_drum[0][i]) {
      seq_drum_kick += "X";
    } else if (seq_drum[0][i] == 0) {
      seq_drum_kick += ".";
    }

    if (seq_drum[1][i]) {
      seq_drum_snare3 += "X";
    } else if (seq_drum[1][i] == 0) {
      seq_drum_snare3 += "-";
    }

    if (seq_drum[2][i]) {
      seq_drum_snare4 += "X";
    } else if (seq_drum[2][i] == 0) {
      seq_drum_snare4 += ".";
    }
    if (seq_drum[3][i]) {
      seq_drum_hihat1 += "X";
    } else if (seq_drum[3][i] == 0) {
      seq_drum_hihat1 += "-";
    }
    if (seq_drum[4][i]) {
      seq_drum_hihat2 += "X";
    } else if (seq_drum[4][i] == 0) {
      seq_drum_hihat2 += ".";
    }
    if (seq_drum[5][i]) {
      seq_drum_clap1 += "X";
    } else if (seq_drum[5][i] == 0) {
      seq_drum_clap1 += "-";
    }
    if (seq_drum[6][i]) {
      seq_drum_water1 += "X";
    } else if (seq_drum[6][i] == 0) {
      seq_drum_water1 += ".";
    }
    if (seq_drum[7][i]) {
      seq_drum_snap1 += "X";
    } else if (seq_drum[7][i] == 0) {
      seq_drum_snap1 += "-";
    }
  }
}

// Functions for melo series also need similar debounce processing
// Debounce variables for melody sequences
unsigned long last_melo_button_time = 0;
bool prev_melo_up = false;
bool prev_melo_down = false;
bool prev_melo_left = false;
bool prev_melo_right = false;
bool prev_melo_confirm = false;
bool prev_melo_cancel = false;

void set_melo_seq_12() {
  unsigned long current_time = millis();
  
  // Check debounce time (for melody)
  if (current_time - last_melo_button_time >= debounce_delay) {
    // Cursor movement (only when confirm button is not pressed)
    if (button_pressed(cross_button_up, prev_melo_up) && !digitalRead(button_confirm)) {
      cursor_y_melo_12 = max(0, cursor_y_melo_12 - 1);
      last_melo_button_time = current_time;
    }
    if (button_pressed(cross_button_down, prev_melo_down) && !digitalRead(button_confirm)) {
      cursor_y_melo_12 = min(3, cursor_y_melo_12 + 1);
      last_melo_button_time = current_time;
    }
    if (button_pressed(cross_button_right, prev_melo_right) && !digitalRead(button_confirm)) {
      cursor_x_melo_12 = min(7, cursor_x_melo_12 + 1);
      last_melo_button_time = current_time;
    }
    if (button_pressed(cross_button_left, prev_melo_left) && !digitalRead(button_confirm)) {
      cursor_x_melo_12 = max(0, cursor_x_melo_12 - 1);
      last_melo_button_time = current_time;
    }
  } else {
    // Update previous states even within debounce time
    prev_melo_up = digitalRead(cross_button_up);
    prev_melo_down = digitalRead(cross_button_down);
    prev_melo_left = digitalRead(cross_button_left);
    prev_melo_right = digitalRead(cross_button_right);
    prev_melo_confirm = digitalRead(button_confirm);
    prev_melo_cancel = digitalRead(button_cancel);
  }

  // Pitch change processing (same as original logic)
  if (cursor_y_melo_12 < 2) {
    if (digitalRead(button_confirm) && digitalRead(cross_button_up)) {
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] += 1;
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] = constrain(seq_melo[cursor_y_melo_12][cursor_x_melo_12], 0, 128);
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_down)) {
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] += -1;
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] = constrain(seq_melo[cursor_y_melo_12][cursor_x_melo_12], 0, 128);
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_right)) {
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] += 12;
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] = constrain(seq_melo[cursor_y_melo_12][cursor_x_melo_12], 0, 128);
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_left)) {
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] += -12;
      seq_melo[cursor_y_melo_12][cursor_x_melo_12] = constrain(seq_melo[cursor_y_melo_12][cursor_x_melo_12], 0, 128);
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = true;
    }
    if (digitalRead(button_cancel)) {
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = false;
    }
    if (digitalRead(button_confirm)) {
      seq_melo_trig[cursor_y_melo_12][cursor_x_melo_12] = true;
    }
  } else {
    // Processing for 16th step (same as original logic)
    if (digitalRead(button_confirm) && digitalRead(cross_button_up)) {
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] += 1;
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = constrain(seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_down)) {
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] += -1;
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = constrain(seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_right)) {
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] += 12;
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = constrain(seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_left)) {
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] += -12;
      seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = constrain(seq_melo[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = true;
    }
    if (digitalRead(button_cancel)) {
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = false;
    }
    if (digitalRead(button_confirm)) {
      seq_melo_trig[cursor_y_melo_12 - 2][cursor_x_melo_12 + 8] = true;
    }
  }

  // String generation processing (same as original code)
  seq_melo_oct0_8 = "";
  seq_melo_key0_8 = "";
  seq_melo_oct1_8 = "";
  seq_melo_key1_8 = "";

  seq_melo_oct0_16 = "";
  seq_melo_key0_16 = "";
  seq_melo_oct1_16 = "";
  seq_melo_key1_16 = "";

  for (int i = 0; i < 16; i++) {
    if (i < 8) {
      if (seq_melo_trig[0][i]) {
        seq_melo_oct0_8 += oct_name[(int)seq_melo[0][i] / 12];
      } else if (seq_melo_trig[0][i] == 0) {
        seq_melo_oct0_8 += "__";
      }
      if (seq_melo_trig[0][i]) {
        seq_melo_key0_8 += note_name[(int)seq_melo[0][i] % 12];
      } else if (seq_melo_trig[0][i] == 0) {
        seq_melo_key0_8 += "__";
      }

      if (seq_melo_trig[1][i]) {
        seq_melo_oct1_8 += oct_name[(int)seq_melo[1][i] / 12];
      } else if (seq_melo_trig[1][i] == 0) {
        seq_melo_oct1_8 += "__";
      }
      if (seq_melo_trig[1][i]) {
        seq_melo_key1_8 += note_name[(int)seq_melo[1][i] % 12];
      } else if (seq_melo_trig[1][i] == 0) {
        seq_melo_key1_8 += "__";
      }
    } else {
      if (seq_melo_trig[0][i]) {
        seq_melo_oct0_16 += oct_name[(int)seq_melo[0][i] / 12];
      } else if (seq_melo_trig[0][i] == 0) {
        seq_melo_oct0_16 += "__";
      }
      if (seq_melo_trig[0][i]) {
        seq_melo_key0_16 += note_name[(int)seq_melo[0][i] % 12];
      } else if (seq_melo_trig[0][i] == 0) {
        seq_melo_key0_16 += "__";
      }

      if (seq_melo_trig[1][i]) {
        seq_melo_oct1_16 += oct_name[(int)seq_melo[1][i] / 12];
      } else if (seq_melo_trig[1][i] == 0) {
        seq_melo_oct1_16 += "__";
      }
      if (seq_melo_trig[1][i]) {
        seq_melo_key1_16 += note_name[(int)seq_melo[1][i] % 12];
      } else if (seq_melo_trig[1][i] == 0) {
        seq_melo_key1_16 += "__";
      }
    }
  }
}

// Debounce variables for melody sequences 34
unsigned long last_melo34_button_time = 0;
bool prev_melo34_up = false;
bool prev_melo34_down = false;
bool prev_melo34_left = false;
bool prev_melo34_right = false;
bool prev_melo34_confirm = false;
bool prev_melo34_cancel = false;

void set_melo_seq_34() {
  unsigned long current_time = millis();
  
  // Check debounce time (for melody 34)
  if (current_time - last_melo34_button_time >= debounce_delay) {
    // Cursor movement (only when confirm button is not pressed)
    if (button_pressed(cross_button_up, prev_melo34_up) && !digitalRead(button_confirm)) {
      cursor_y_melo_34 = max(0, cursor_y_melo_34 - 1);
      last_melo34_button_time = current_time;
    }
    if (button_pressed(cross_button_down, prev_melo34_down) && !digitalRead(button_confirm)) {
      cursor_y_melo_34 = min(3, cursor_y_melo_34 + 1);
      last_melo34_button_time = current_time;
    }
    if (button_pressed(cross_button_right, prev_melo34_right) && !digitalRead(button_confirm)) {
      cursor_x_melo_34 = min(7, cursor_x_melo_34 + 1);
      last_melo34_button_time = current_time;
    }
    if (button_pressed(cross_button_left, prev_melo34_left) && !digitalRead(button_confirm)) {
      cursor_x_melo_34 = max(0, cursor_x_melo_34 - 1);
      last_melo34_button_time = current_time;
    }
  } else {
    // Update previous states even within debounce time
    prev_melo34_up = digitalRead(cross_button_up);
    prev_melo34_down = digitalRead(cross_button_down);
    prev_melo34_left = digitalRead(cross_button_left);
    prev_melo34_right = digitalRead(cross_button_right);
    prev_melo34_confirm = digitalRead(button_confirm);
    prev_melo34_cancel = digitalRead(button_cancel);
  }

  // Pitch change processing (same as original logic)
  if (cursor_y_melo_34 < 2) {
    if (digitalRead(button_confirm) && digitalRead(cross_button_up)) {
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] += 1;
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] = constrain(seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34], 0, 128);
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_down)) {
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] += -1;
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] = constrain(seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34], 0, 128);
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_right)) {
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] += 12;
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] = constrain(seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34], 0, 128);
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_left)) {
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] += -12;
      seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34] = constrain(seq_melo[cursor_y_melo_34 + 2][cursor_x_melo_34], 0, 128);
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = true;
    }
    if (digitalRead(button_cancel)) {
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = false;
    }
    if (digitalRead(button_confirm)) {
      seq_melo_trig[cursor_y_melo_34 + 2][cursor_x_melo_34] = true;
    }
  } else {
    // Processing for 16th step (same as original logic)
    if (digitalRead(button_confirm) && digitalRead(cross_button_up)) {
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] += 1;
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] = constrain(seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_down)) {
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] += -1;
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] = constrain(seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_right)) {
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] += 12;
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] = constrain(seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = true;
    }
    if (digitalRead(button_confirm) && digitalRead(cross_button_left)) {
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] += -12;
      seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8] = constrain(seq_melo[cursor_y_melo_34][cursor_x_melo_34 + 8], 0, 128);
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = true;
    }
    if (digitalRead(button_cancel)) {
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = false;
    }
    if (digitalRead(button_confirm)) {
      seq_melo_trig[cursor_y_melo_34][cursor_x_melo_34 + 8] = true;
    }
  }

  // String generation processing (same as original code)
  seq_melo_oct2_8 = "";
  seq_melo_key2_8 = "";
  seq_melo_oct3_8 = "";
  seq_melo_key3_8 = "";

  seq_melo_oct2_16 = "";
  seq_melo_key2_16 = "";
  seq_melo_oct3_16 = "";
  seq_melo_key3_16 = "";

  for (int i = 0; i < 16; i++) {
    if (i < 8) {
      if (seq_melo_trig[2][i]) {
        seq_melo_oct2_8 += oct_name[(int)seq_melo[2][i] / 12];
      } else if (seq_melo_trig[2][i] == 0) {
        seq_melo_oct2_8 += "__";
      }
      if (seq_melo_trig[2][i]) {
        seq_melo_key2_8 += note_name[(int)seq_melo[2][i] % 12];
      } else if (seq_melo_trig[2][i] == 0) {
        seq_melo_key2_8 += "__";
      }

      if (seq_melo_trig[3][i]) {
        seq_melo_oct3_8 += oct_name[(int)seq_melo[3][i] / 12];
      } else if (seq_melo_trig[3][i] == 0) {
        seq_melo_oct3_8 += "__";
      }
      if (seq_melo_trig[3][i]) {
        seq_melo_key3_8 += note_name[(int)seq_melo[3][i] % 12];
      } else if (seq_melo_trig[3][i] == 0) {
        seq_melo_key3_8 += "__";
      }
    } else {
      if (seq_melo_trig[2][i]) {
        seq_melo_oct2_16 += oct_name[(int)seq_melo[2][i] / 12];
      } else if (seq_melo_trig[2][i] == 0) {
        seq_melo_oct2_16 += "__";
      }
      if (seq_melo_trig[2][i]) {
        seq_melo_key2_16 += note_name[(int)seq_melo[2][i] % 12];
      } else if (seq_melo_trig[2][i] == 0) {
        seq_melo_key2_16 += "__";
      }

      if (seq_melo_trig[3][i]) {
        seq_melo_oct3_16 += oct_name[(int)seq_melo[3][i] / 12];
      } else if (seq_melo_trig[3][i] == 0) {
        seq_melo_oct3_16 += "__";
      }
      if (seq_melo_trig[3][i]) {
        seq_melo_key3_16 += note_name[(int)seq_melo[3][i] % 12];
      } else if (seq_melo_trig[3][i] == 0) {
        seq_melo_key3_16 += "__";
      }
    }
  }
}