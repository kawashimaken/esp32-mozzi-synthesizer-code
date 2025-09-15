#include "ui_controller.h"
#include "sequencer.h"
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/22, /* data=*/21, /* cs=*/2, /* dc=*/15, /* reset=*/17);

// Variables for waveform display
static int wave_amplitude[128];  // Amplitude for each X coordinate
static int wave_decay[128];      // Decay counter for each X coordinate
static unsigned long last_beat_time = 0;
static int beat_intensity = 0;

void ui_init() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R0);
  u8g2.setFlipMode(1);   
  u8g2.setBusClock(400000000);
  Wire.setClock(400000);
  u8g2.setFontMode(1);
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_b10_t_japanese1);
  u8g2.setFontDirection(0);
  
  // Initialize waveform arrays
  for (int i = 0; i < 128; i++) {
    wave_amplitude[i] = 0;
    wave_decay[i] = 0;
  }
}

void ui_task_init() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R0);
  u8g2.setFlipMode(1);   
}

// Function to check String and determine if beat is set
bool checkBeat(String sequence, int step) {
  if (step >= sequence.length()) return false;
  char c = sequence.charAt(step);
  return (c == '1' || c == 'X' || c == 'x' || c == '*');
}

// Check if there is active drum beat at current step
bool hasActiveDrumBeat() {
  int current_step = master_count % 16;
  return (checkBeat(seq_drum_kick, current_step) ||
          checkBeat(seq_drum_snare3, current_step) ||
          checkBeat(seq_drum_snare4, current_step) ||
          checkBeat(seq_drum_hihat1, current_step) ||
          checkBeat(seq_drum_hihat2, current_step) ||
          checkBeat(seq_drum_clap1, current_step) ||
          checkBeat(seq_drum_water1, current_step) ||
          checkBeat(seq_drum_snap1, current_step));
}

// Calculate beat intensity (determined by which drums are playing)
int calculateBeatIntensity() {
  int current_step = master_count % 16;
  int intensity = 0;
  
  if (checkBeat(seq_drum_kick, current_step)) intensity += 8;    // Kick: strong
  if (checkBeat(seq_drum_snare3, current_step)) intensity += 6; // Snare: medium-strong
  if (checkBeat(seq_drum_snare4, current_step)) intensity += 6;
  if (checkBeat(seq_drum_clap1, current_step)) intensity += 4;  // Clap: medium
  if (checkBeat(seq_drum_hihat1, current_step)) intensity += 2; // Hi-hat: light
  if (checkBeat(seq_drum_hihat2, current_step)) intensity += 2;
  if (checkBeat(seq_drum_water1, current_step)) intensity += 3; // Sound effects: medium-light
  if (checkBeat(seq_drum_snap1, current_step)) intensity += 3;
  
  return min(intensity, 15); // Limit to maximum 15
}

// Update dynamic waveform (revised version)
void updateDynamicWaveform() {
  unsigned long current_time = millis();
  static bool initialized = false;
  
  // Generate default waveform for initial startup or when no beats
  if (!initialized) {
    // Display basic waveform at initial startup
    for (int i = 0; i < 128; i++) {
      wave_amplitude[i] = 3 + sin((float)i * 0.1) * 2; // Small basic waveform
      wave_decay[i] = 1; // Set to 1 for continuous display
    }
    initialized = true;
  }
  
  // Generate waveform when beat is playing
  if (hasActiveDrumBeat() && (current_time - last_beat_time > 50)) { // Update limit at 50ms intervals
    beat_intensity = calculateBeatIntensity();
    last_beat_time = current_time;
    
    // Set waveform amplitude (add random elements for dynamic feel)
    for (int i = 0; i < 128; i++) {
      int base_amplitude = beat_intensity * sin((float)i * 0.1) * 0.5;
      int random_factor = random(-2, 3); // Random value from -2 to 2
      wave_amplitude[i] = abs(base_amplitude + random_factor);
      wave_decay[i] = 20 + random(0, 10); // Decay in 20-30 frames
    }
  }
  // Even when no beats, occasionally update waveform for movement effect
  else if ((current_time % 500) < 50) { // Display light waveform for 50ms every 500ms
    for (int i = 0; i < 128; i++) {
      int base_amplitude = 2 * sin((float)i * 0.05 + current_time * 0.01);
      wave_amplitude[i] = max(1, abs(base_amplitude));
      wave_decay[i] = 5; // Short decay
    }
  }
  
  // Waveform decay processing
  for (int i = 0; i < 128; i++) {
    if (wave_decay[i] > 0) {
      wave_decay[i]--;
      if (wave_decay[i] == 0) {
        wave_amplitude[i] = max(1, wave_amplitude[i] / 2); // Don't go completely to 0, leave a little
        wave_decay[i] = 1; // Maintain basic level
      } else {
        // Decay curve
        wave_amplitude[i] = wave_amplitude[i] * 0.95;
      }
    }
  }
}

// Draw dynamic waveform
void drawDynamicWaveform() {
  int center_y = 32; // Screen center
  
  for (int x = 0; x < 127; x++) {
    if (wave_amplitude[x] > 0) {
      // Draw upward and downward waveforms
      int amp = wave_amplitude[x];
      u8g2.drawLine(x, center_y, x, center_y - amp);
      u8g2.drawLine(x, center_y, x, center_y + amp);
    }
  }
  
  // Draw center line
  u8g2.drawHLine(0, center_y, 128);
  
  // Display current beat position
  int beat_pos = (master_count % 16) * 8;
  u8g2.drawBox(beat_pos, center_y - 1, 2, 3);
}

// Function to draw diamond shape
void drawDiamond(int x, int y, int size, bool filled) {
  if (filled) {
    u8g2.drawTriangle(x, y - size, x + size, y, x, y + size);
    u8g2.drawTriangle(x, y - size, x - size, y, x, y + size);
  }
}

// Function to draw pulse waveform
void drawPulse(int x, int y, int width, bool active) {
  if (active) {
    u8g2.drawLine(x, y + 3, x + 2, y + 3);
    u8g2.drawLine(x + 2, y + 3, x + 2, y - 3);
    u8g2.drawLine(x + 2, y - 3, x + 4, y - 3);
    u8g2.drawLine(x + 4, y - 3, x + 4, y + 3);
    u8g2.drawLine(x + 4, y + 3, x + 6, y + 3);
  }
}

void ui_update() {
  // Update waveform
  updateDynamicWaveform();
  
  cursor_select = map(analogRead(A1_meter), 0, 4095, 0, 3); // Expand choices to 3
  switch (cursor_select) {
    case 0:
      drum_seq_disp();
      break;
    case 1:
      melo_seq_disp_12();
      break;
    case 2:
      melo_seq_disp_34();
      break;
    case 3:
      waveform_disp(); // New waveform display mode
      break;
  }
}

void drum_seq_disp() {
  u8g2.clearBuffer();
  set_drum_seq();
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);
  
  // Highlight current playback position
  int current_step = master_count % 16;
  u8g2.drawFrame(current_step * 8, 0, 8, 64);
  
  // Display beats for each drum track
  for (int step = 0; step < 16; step++) {
    int x = step * 8 + 4;
    
    if (checkBeat(seq_drum_kick, step)) {
      u8g2.drawDisc(x, 8, 2);
    } else {
      u8g2.drawPixel(x, 8);
    }
    
    if (checkBeat(seq_drum_snare3, step)) {
      u8g2.drawBox(x - 2, 14, 4, 4);
    } else {
      u8g2.drawPixel(x, 16);
    }
    
    if (checkBeat(seq_drum_snare4, step)) {
      drawDiamond(x, 24, 2, true);
    } else {
      u8g2.drawPixel(x, 24);
    }
    
    if (checkBeat(seq_drum_hihat1, step)) {
      u8g2.drawTriangle(x, 30, x - 2, 34, x + 2, 34);
    } else {
      u8g2.drawPixel(x, 32);
    }
    
    if (checkBeat(seq_drum_hihat2, step)) {
      u8g2.drawTriangle(x - 2, 38, x + 2, 38, x, 42);
    } else {
      u8g2.drawPixel(x, 40);
    }
    
    if (checkBeat(seq_drum_clap1, step)) {
      u8g2.drawDisc(x, 48, 2);
    } else {
      u8g2.drawPixel(x, 48);
    }
    
    if (checkBeat(seq_drum_water1, step)) {
      u8g2.drawLine(x - 2, 54, x - 1, 52);
      u8g2.drawLine(x - 1, 52, x, 54);
      u8g2.drawLine(x, 54, x + 1, 52);
      u8g2.drawLine(x + 1, 52, x + 2, 54);
    } else {
      u8g2.drawPixel(x, 54);
    }
    
    if (checkBeat(seq_drum_snap1, step)) {
      drawPulse(x - 2, 60, 4, true);
    } else {
      u8g2.drawPixel(x, 60);
    }
  }
  
  u8g2.sendBuffer();
}

// New enhanced waveform drawing function
void drawDynamicWaveform_Enhanced() {
  int center_y = 32; // Screen center
  unsigned long current_time = millis();
  
  // Always call updateDynamicWaveform() to update arrays
  updateDynamicWaveform();
  
  // Normal waveform when beats are active
  if (hasActiveDrumBeat()) {
    for (int x = 0; x < 127; x++) {
      if (wave_amplitude[x] > 0) {
        int amp = wave_amplitude[x];
        u8g2.drawLine(x, center_y, x, center_y - amp);
        u8g2.drawLine(x, center_y, x, center_y + amp);
      }
    }
  }
  // Even when no beats, use arrays updated by updateDynamicWaveform()
  else {
    for (int x = 0; x < 127; x++) {
      if (wave_amplitude[x] > 0) {
        int amp = wave_amplitude[x];
        u8g2.drawLine(x, center_y, x, center_y - amp);
        u8g2.drawLine(x, center_y, x, center_y + amp);
      }
    }
  }
  
  // Draw center line
  u8g2.drawHLine(0, center_y, 128);
  
  // Display current beat position
  int beat_pos = (master_count % 16) * 8;
  u8g2.drawBox(beat_pos, center_y - 1, 2, 3);
}

void waveform_disp() {
  u8g2.clearBuffer();
  // Update drum sequence data (this is important!)
  set_drum_seq();
  
  // Display section information at top
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setCursor(0, 10);
  u8g2.print("BEAT: ");
  u8g2.print(get_current_section_name());
  u8g2.print(" ");
  u8g2.print(master_count);
  
  // Always draw waveform (startup compatible version)
  drawDynamicWaveform_Enhanced();
  
  // Current pattern information at bottom (abbreviated version)
  u8g2.setCursor(0, 60);
  u8g2.print("Pat:");
  u8g2.print(get_current_pattern());
  u8g2.print(" Prog:");
  u8g2.print((int)get_song_progress_percent());
  u8g2.print("%");
  
  u8g2.sendBuffer();
}

void melo_seq_disp_12() {
  u8g2.clearBuffer();
  set_melo_seq_12();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  // Highlight current playback position
  int current_step = master_count % 16;
  if (current_step < 8) {
    // First 8 steps - surround top 3 rows
    u8g2.drawFrame(current_step * 16, 2, 8, 31);
  } else {
    // Last 8 steps - surround bottom 3 rows
    u8g2.drawFrame((current_step - 8) * 16, 32, 8, 31);
  }
  
  // Place characters for first 8 steps (0-7) individually - top 3 rows
  for (int i = 0; i < 8; i++) {
    int x_pos = i * 16 + 2; // 16 pixel spacing, centered
    
    // Row 1: seq_melo_oct0_8 characters
    if (i < seq_melo_oct0_8.length()) {
      u8g2.setCursor(x_pos, 10);
      u8g2.print(seq_melo_oct0_8.charAt(i));
    }
    
    // Row 2: seq_melo_key0_8 characters
    if (i < seq_melo_key0_8.length()) {
      u8g2.setCursor(x_pos, 20);
      u8g2.print(seq_melo_key0_8.charAt(i));
    }
    
    // Row 3: seq_melo_oct1_8 characters
    if (i < seq_melo_oct1_8.length()) {
      u8g2.setCursor(x_pos, 30);
      u8g2.print(seq_melo_oct1_8.charAt(i));
    }
  }
  
  // Place characters for last 8 steps (8-15) individually - bottom 3 rows
  for (int i = 0; i < 8; i++) {
    int x_pos = i * 16 + 2; // 16 pixel spacing, centered
    
    // Row 4: seq_melo_key1_8 characters
    if (i < seq_melo_key1_8.length()) {
      u8g2.setCursor(x_pos, 42);
      u8g2.print(seq_melo_key1_8.charAt(i));
    }
    
    // Row 5: seq_melo_oct0_16 characters
    if (i < seq_melo_oct0_16.length()) {
      u8g2.setCursor(x_pos, 52);
      u8g2.print(seq_melo_oct0_16.charAt(i));
    }
    
    // Row 6: seq_melo_key0_16 characters
    if (i < seq_melo_key0_16.length()) {
      u8g2.setCursor(x_pos, 62);
      u8g2.print(seq_melo_key0_16.charAt(i));
    }
  }
  
  u8g2.sendBuffer();
}

void melo_seq_disp_34() {
  u8g2.clearBuffer();
  set_melo_seq_34();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  // Highlight current playback position
  int current_step = master_count % 16;
  if (current_step < 8) {
    // First 8 steps
    u8g2.drawFrame(current_step * 16, 2, 8, 31);
  } else {
    // Last 8 steps
    u8g2.drawFrame((current_step - 8) * 16, 32, 8, 31);
  }
  
  // Place characters for first 8 steps (0-7) individually
  for (int i = 0; i < 8; i++) {
    int x_pos = i * 16 + 2; // 16 pixel spacing, centered
    
    // seq_melo_oct2_8 characters
    if (i < seq_melo_oct2_8.length()) {
      u8g2.setCursor(x_pos, 10);
      u8g2.print(seq_melo_oct2_8.charAt(i));
    }
    
    // seq_melo_key2_8 characters
    if (i < seq_melo_key2_8.length()) {
      u8g2.setCursor(x_pos, 20);
      u8g2.print(seq_melo_key2_8.charAt(i));
    }
    
    // seq_melo_oct3_8 characters
    if (i < seq_melo_oct3_8.length()) {
      u8g2.setCursor(x_pos, 30);
      u8g2.print(seq_melo_oct3_8.charAt(i));
    }
    
    // seq_melo_key3_8 characters
    if (i < seq_melo_key3_8.length()) {
      u8g2.setCursor(x_pos, 42);
      u8g2.print(seq_melo_key3_8.charAt(i));
    }
  }
  
  // Place characters for last 8 steps (8-15) individually
  for (int i = 0; i < 8; i++) {
    int x_pos = i * 16 + 2; // 16 pixel spacing, centered
    
    // seq_melo_oct2_16 characters
    if (i < seq_melo_oct2_16.length()) {
      u8g2.setCursor(x_pos, 52);
      u8g2.print(seq_melo_oct2_16.charAt(i));
    }
    
    // seq_melo_oct3_16 characters
    if (i < seq_melo_oct3_16.length()) {
      u8g2.setCursor(x_pos, 62);
      u8g2.print(seq_melo_oct3_16.charAt(i));
    }
  }
  
  u8g2.sendBuffer();
}