#include "config.h"
#include "audio_engine.h"
#include "sequencer.h"
#include "ui_controller.h"
#include "input_handler.h"

void TaskBlink(void *pvParameters);

void setup() {
  // UI initialization
  ui_init();
  
  // Audio initialization
  audio_init();
  
  // Input initialization
  input_init();
  
  // Sequencer initialization
  sequencer_init();

  // Task creation
  xTaskCreatePinnedToCore(
    TaskBlink, "TaskBlink",
    16384,
    NULL, 2,
    NULL, 0);
}

void updateControl() {
  // Input processing
  input_update();
  
  // Sequencer update
  sequencer_update();
}

int updateAudio() {
  return audio_update();
}

void TaskBlink(void *pvParameters) {
  (void)pvParameters;

  ui_task_init();
  input_task_init();

  for (;;) {
    ui_update();
    vTaskDelay(10);
  }
}

void loop() {
  // Use wrapper function instead of direct call since audioHook is defined in audio_engine.cpp
  audio_hook_wrapper();
}