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
}

void ui_task_init() {
  u8g2.begin();
  u8g2.setDisplayRotation(U8G2_R0);
  u8g2.setFlipMode(1);   
}

// Check if beat is set in sequence string
bool checkBeat(String sequence, int step) {
  if (step >= sequence.length()) return false;
  char c = sequence.charAt(step);
  return (c == '1' || c == 'X' || c == 'x' || c == '*');
}

// Draw diamond shape
void drawDiamond(int x, int y, int size, bool filled) {
  if (filled) {
    u8g2.drawTriangle(x, y - size, x + size, y, x, y + size);
    u8g2.drawTriangle(x, y - size, x - size, y, x, y + size);
  }
}

// Draw pulse waveform
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
  cursor_select = map(analogRead(A1_meter), 0, 4095, 0, 2);
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
  }
}

void drum_seq_disp() {
  u8g2.clearBuffer();
  set_drum_seq();
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);
  u8g2.drawFrame(master_count * 8, 0, 8, 8);
  u8g2.drawFrame(master_count * 8, 7, 8, 8);
  u8g2.drawFrame(master_count * 8, 15, 8, 8);
  u8g2.drawFrame(master_count * 8, 23, 8, 8);
  u8g2.drawFrame(master_count * 8, 31, 8, 8);
  u8g2.drawFrame(master_count * 8, 39, 8, 8);
  u8g2.drawFrame(master_count * 8, 47, 8, 8);
  u8g2.drawFrame(master_count * 8, 53, 8, 8);

  u8g2.drawFrame(cursor_x_drum * 8, cursor_y_drum * 8, 8, 8);
  
  for (int step = 0; step < 16; step++) {
    int x = step * 8 + 4;
    
    // KICK - large circle
    if (checkBeat(seq_drum_kick, step)) {
      u8g2.drawDisc(x, 4, 2);
    } else {
      u8g2.drawPixel(x, 4);
    }
    
    // SNARE3 - square
    if (checkBeat(seq_drum_snare3, step)) {
      u8g2.drawBox(x - 2, 9, 4, 4);
    } else {
      u8g2.drawPixel(x, 11);
    }
    
    // SNARE4 - diamond
    if (checkBeat(seq_drum_snare4, step)) {
      drawDiamond(x, 19, 2, true);
    } else {
      u8g2.drawPixel(x, 19);
    }
    
    // HIHAT1 - triangle
    if (checkBeat(seq_drum_hihat1, step)) {
      u8g2.drawTriangle(x, 25, x - 2, 29, x + 2, 29);
    } else {
      u8g2.drawPixel(x, 27);
    }
    
    // HIHAT2 - inverted triangle
    if (checkBeat(seq_drum_hihat2, step)) {
      u8g2.drawTriangle(x - 2, 33, x + 2, 33, x, 37);
    } else {
      u8g2.drawPixel(x, 35);
    }
    
    // CLAP - circle
    if (checkBeat(seq_drum_clap1, step)) {
      u8g2.drawDisc(x, 43, 2);
    } else {
      u8g2.drawPixel(x, 43);
    }
    
    // WATER - waveform
    if (checkBeat(seq_drum_water1, step)) {
      u8g2.drawLine(x - 2, 51, x - 1, 49);
      u8g2.drawLine(x - 1, 49, x, 51);
      u8g2.drawLine(x, 51, x + 1, 49);
      u8g2.drawLine(x + 1, 49, x + 2, 51);
    } else {
      u8g2.drawPixel(x, 51);
    }
    
    // SNAP - pulse waveform
    if (checkBeat(seq_drum_snap1, step)) {
      drawPulse(x - 2, 59, 4, true);
    } else {
      u8g2.drawPixel(x, 59);
    }
  }
  
  u8g2.sendBuffer();
}

void melo_seq_disp_12() {
  u8g2.clearBuffer();
  set_melo_seq_12();
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);
  if (master_count < 8) {
    u8g2.drawFrame(master_count * 16, 0, 8, 8);
    u8g2.drawFrame(master_count * 16, 7, 8, 8);
    u8g2.drawFrame(master_count * 16, 15, 8, 8);
    u8g2.drawFrame(master_count * 16, 23, 8, 8);
  }
  if (master_count >= 8) {
    u8g2.drawFrame((master_count - 8) * 16, 31, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 39, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 47, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 53, 8, 8);
  }
  u8g2.drawFrame(cursor_x_melo_12 * 16, cursor_y_melo_12 * 16, 8, 8);
  
  u8g2.setCursor(0, 7);
  u8g2.print(seq_melo_oct0_8);
  u8g2.setCursor(0, 15);
  u8g2.print(seq_melo_key0_8);
  u8g2.setCursor(0, 23);
  u8g2.print(seq_melo_oct1_8);
  u8g2.setCursor(0, 31);
  u8g2.print(seq_melo_key1_8);
  u8g2.setCursor(0, 39);
  u8g2.print(seq_melo_oct0_16);
  u8g2.setCursor(0, 47);
  u8g2.print(seq_melo_key0_16);
  u8g2.setCursor(0, 53);
  u8g2.print(seq_melo_oct1_16);
  u8g2.setCursor(0, 63);
  u8g2.print(seq_melo_key1_16);
  u8g2.sendBuffer();
}

void melo_seq_disp_34() {
  u8g2.clearBuffer();
  set_melo_seq_34();
  u8g2.setFont(u8g2_font_amstrad_cpc_extended_8f);
  if (master_count < 8) {
    u8g2.drawFrame(master_count * 16, 0, 8, 8);
    u8g2.drawFrame(master_count * 16, 7, 8, 8);
    u8g2.drawFrame(master_count * 16, 15, 8, 8);
    u8g2.drawFrame(master_count * 16, 23, 8, 8);
  }
  if (master_count >= 8) {
    u8g2.drawFrame((master_count - 8) * 16, 31, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 39, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 47, 8, 8);
    u8g2.drawFrame((master_count - 8) * 16, 53, 8, 8);
  }
  u8g2.drawFrame(cursor_x_melo_34 * 16, cursor_y_melo_34 * 16, 8, 8);
  
  u8g2.setCursor(0, 7);
  u8g2.print(seq_melo_oct2_8);
  u8g2.setCursor(0, 15);
  u8g2.print(seq_melo_key2_8);
  u8g2.setCursor(0, 23);
  u8g2.print(seq_melo_oct3_8);
  u8g2.setCursor(0, 31);
  u8g2.print(seq_melo_key3_8);
  u8g2.setCursor(0, 39);
  u8g2.print(seq_melo_oct2_16);
  u8g2.setCursor(0, 47);
  u8g2.print(seq_melo_key2_16);
  u8g2.setCursor(0, 53);
  u8g2.print(seq_melo_oct3_16);
  u8g2.setCursor(0, 63);
  u8g2.print(seq_melo_key3_16);
  u8g2.sendBuffer();
}