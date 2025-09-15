// Hip-Hop Style main program
// American rap groove and beat-focused

#include "config.h"
#include "audio_engine.h"
#include "sequencer.h"
#include "song_structure.h"
#include "song_library.h"
#include "ui_controller.h"

void TaskSongProgress(void *pvParameters);
void TaskGrooveMonitor(void *pvParameters);
void TaskUIUpdate(void *pvParameters);

void setup()
{
  Serial.begin(115200);
  delay(2000);

  // Audio initialization
  audio_init();

  // Song library initialization
  init_song_library();
  // set_current_song(SONG_EUROBEAT);  // Set default song
  // set_current_song(SONG_HIPHOP);  // Set default song
  set_current_song(SONG_CLASSICAL); // Set default song

  // Hip-Hop Sequencer initialization
  sequencer_init();

  // UI initialization
  ui_init();

  // Progress monitor task
  xTaskCreatePinnedToCore(
      TaskSongProgress, "HipHopProgress",
      8192,
      NULL, 2,
      NULL, 1);

  // Groove monitor task
  xTaskCreatePinnedToCore(
      TaskGrooveMonitor, "GrooveMonitor",
      4096,
      NULL, 1,
      NULL, 0);

  // UI update task
  xTaskCreatePinnedToCore(
      TaskUIUpdate, "UIUpdate",
      4096,
      NULL, 1,
      NULL, 1); // Run on Core 1
}

void updateControl()
{
  sequencer_update();
}

int updateAudio()
{
  return audio_update();
}

// UI update task
void TaskUIUpdate(void *pvParameters)
{
  (void)pvParameters;

  for (;;)
  {
    ui_update();
    vTaskDelay(50); // 20FPS update (50ms interval)
  }
}

void TaskSongProgress(void *pvParameters)
{
  (void)pvParameters;

  unsigned long last_report = 0;
  const unsigned long REPORT_INTERVAL = 6000; // Every 6 seconds (hip-hop relaxed tempo)

  for (;;)
  {
    unsigned long now = millis();

    if (now - last_report >= REPORT_INTERVAL)
    {
      last_report = now;
    }

    if (is_song_finished())
    {
      int next_song = (get_current_song_id() + 1) % get_song_count();
      set_current_song(next_song);
      start_song();
      vTaskDelay(1500);
    }
    vTaskDelay(100);
  }
}

void TaskGrooveMonitor(void *pvParameters)
{
  (void)pvParameters;

  unsigned long last_groove_check = 0;
  const unsigned long GROOVE_INTERVAL = 8000; // Every 8 seconds

  for (;;)
  {
    unsigned long now = millis();

    if (now - last_groove_check >= GROOVE_INTERVAL)
    {
      // Check rhythm state at current step
      int current_step = master_count % SEQUENCE_LENGTH;
      bool kick_hits = false;
      bool snare_hits = false;
      bool bass_active = false;

      // Kick drum state
      if (seq_drum[0][current_step])
      {
        kick_hits = true;
      }

      // Snare state
      if (seq_drum[1][current_step] || seq_drum[2][current_step])
      {
        snare_hits = true;
      }

      // Bassline state
      if (seq_melo_trig[0][current_step] || seq_melo_trig[1][current_step])
      {
        bass_active = true;
      }

      last_groove_check = now;
    }

    vTaskDelay(1000);
  }
}

void loop()
{
  audio_hook_wrapper();
}