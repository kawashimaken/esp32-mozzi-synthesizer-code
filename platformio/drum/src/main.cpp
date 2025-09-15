#include "config.h"
#include "audio_engine.h"
#include "sequencer.h"
#include "ui_controller.h"
#include "input_handler.h"
// MozziGuts.h is only included in audio_engine.cpp

void TaskBlink(void *pvParameters);

void setup() {
  // Initialize UI
  ui_init();
  
  // Initialize audio
  audio_init();
  
  // Initialize input
  input_init();
  
  // Initialize sequencer
  sequencer_init();

  // Create task
  xTaskCreatePinnedToCore(
    TaskBlink, "TaskBlink",
    16384,
    NULL, 2,
    NULL, 0);
}

void updateControl() {
  // Handle input
  input_update();
  
  // Update sequencer
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
  // Since audioHook is defined in audio_engine.cpp,
  // use the wrapper function instead of calling it directly
  audio_hook_wrapper();
}
