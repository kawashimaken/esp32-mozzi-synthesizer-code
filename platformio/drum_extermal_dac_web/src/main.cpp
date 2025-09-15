// Pure Drum Machine - No Songs, No Melody
// Web UI Only

#include "config.h"
#include "audio_engine.h"
#include "web_server.h"

void TaskWebServer(void *pvParameters);

void setup()
{
  Serial.begin(115200);
  delay(2000);

  Serial.println("=== ESP32 Pure Drum Machine ===");

  // Audio initialization only
  audio_init();

  // Set audio sample frequencies
  set_freq();

  // Web server initialization
  web_server_init();

  Serial.println("=== Pure Drum Machine Ready ===");
  Serial.println("No songs, no melody - drums only!");

  // Single web server task
  xTaskCreatePinnedToCore(
      TaskWebServer, "WebServer",
      8192,
      NULL, 1,
      NULL, 0);

  Serial.println("=== Setup complete ===");
}

void updateControl()
{
  // Minimal control - no sequencer
}

int updateAudio()
{
  return audio_update();
}

void TaskWebServer(void *pvParameters)
{
  (void)pvParameters;
  Serial.println("Web Server Task started");

  for (;;)
  {
    web_server_update();
    vTaskDelay(50);
  }
}

void loop()
{
  audio_hook_wrapper();
  delayMicroseconds(10);
}