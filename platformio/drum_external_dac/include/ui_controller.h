#ifndef UI_CONTROLLER_H
#define UI_CONTROLLER_H

#include <Arduino.h>

// Existing function declarations
void ui_init();
void ui_task_init();
void ui_update();
void drum_seq_disp();
void melo_seq_disp_12();
void melo_seq_disp_34();

// Additional function declarations
void drawHexagon(int x, int y, int size, bool filled);
void drawDiamond(int x, int y, int size, bool filled);
void drawPulse(int x, int y, int width, bool active);
void drawNote(int x, int y, int octave, bool active);
bool checkBeat(String sequence, int step);
void drum_seq_disp_improved();
void melo_seq_disp_12_improved();
void melo_seq_disp_34_improved();

#endif