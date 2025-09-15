#include "web_server.h"
#include "web_ui.h"

// Declare external drum trigger functions from audio_engine.cpp
extern void trigger_kick();
extern void trigger_snare1();
extern void trigger_snare2();
extern void trigger_hihat1();
extern void trigger_hihat2();
extern void trigger_clap();
extern void trigger_water();
extern void trigger_snap();

WebServer server(80);

// Web sequence storage (16 steps)
bool web_sequence[NUM_DRUM_TRACKS][16];
bool web_sequence_playing = false;
int web_current_step = 0;
int web_bpm = 120;

// High precision timing using hardware timer
hw_timer_t * sequenceTimer = NULL;
volatile bool timer_triggered = false;

// Timer interrupt handler (IRAM_ATTR required)
void IRAM_ATTR onSequenceTimer() {
  timer_triggered = true;
}

// Update timer interval when BPM changes
void update_timer_interval() {
  if (sequenceTimer) {
    // Calculate 16th note interval in microseconds
    // 60 seconds / BPM / 4 (16th notes) * 1,000,000 (microseconds)
    uint64_t interval_us = (60 * 1000000) / (web_bpm * 4);
    
    timerAlarmWrite(sequenceTimer, interval_us, true); // Auto-reload enabled
    
    Serial.print("Timer interval updated: ");
    Serial.print(interval_us);
    Serial.println(" microseconds");
  }
}

// High precision timer initialization
void init_precision_timer() {
  Serial.println("Initializing precision timer...");
  
  // Hardware timer initialization
  // Timer 0, prescaler 80 (1MHz = 1μs precision), count up
  sequenceTimer = timerBegin(0, 80, true);
  
  // Set timer interrupt handler
  timerAttachInterrupt(sequenceTimer, &onSequenceTimer, true);
  
  // Set initial interval (120BPM = 125ms interval)
  update_timer_interval();
  
  Serial.println("Precision timer initialized");
}

void web_server_init() {
  Serial.println("Initializing Web Server...");
  
  // Initialize web sequence - all false
  for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
    for (int step = 0; step < 16; step++) {
      web_sequence[track][step] = false;
    }
  }
  
  Serial.println("Web sequence cleared - all steps = false");
  
  setup_wifi();
  
  // Setup routes
  server.on("/", HTTP_GET, handle_root);
  server.on("/trigger", HTTP_POST, handle_drum_trigger);
  server.on("/sequence", HTTP_POST, handle_sequence_update);
  server.on("/transport", HTTP_POST, handle_transport_control);
  server.on("/status", HTTP_GET, handle_status);
  server.on("/bpm", HTTP_POST, handle_bpm_update);
  server.onNotFound(handle_not_found);
  
  server.begin();
  Serial.println("Web server started");
  Serial.print("Access drum machine at: http://");
  Serial.println(WiFi.softAPIP());
  
  // Initialize high precision timer
  init_precision_timer();
}

void setup_wifi() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("DrumMachine-AP", "drum1234");
  
  Serial.println("WiFi Access Point started");
  Serial.println("AP SSID: DrumMachine-AP");
  Serial.println("Password: drum1234");
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Connect to this network and visit http://192.168.4.1");
}

void web_server_update() {
  server.handleClient();
  
  // High precision playback using hardware timer interrupt
  if (web_sequence_playing && timer_triggered) {
    timer_triggered = false; // Reset flag
    
    Serial.print("Step ");
    Serial.print(web_current_step);
    Serial.print(": ");
    
    bool any_triggered = false;
    
    // Trigger drums for current step
    for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
      if (web_sequence[track][web_current_step]) {
        trigger_drum_sample(track);
        any_triggered = true;
        Serial.print("T");
        Serial.print(track);
        Serial.print(" ");
      }
    }
    
    if (!any_triggered) {
      Serial.print("(silent)");
    }
    Serial.println();
    
    // Advance to next step
    web_current_step = (web_current_step + 1) % 16;
  }
}

void handle_root() {
  server.send(200, "text/html", getWebUIHTML());
}

void handle_drum_trigger() {
  if (server.hasArg("drum")) {
    int drum_id = server.arg("drum").toInt();
    trigger_drum_sample(drum_id);
    server.send(200, "application/json", "{\"status\":\"ok\",\"drum\":" + String(drum_id) + "}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing drum parameter\"}");
  }
}

void handle_sequence_update() {
  if (server.hasArg("track") && server.hasArg("step") && server.hasArg("active")) {
    int track = server.arg("track").toInt();
    int step = server.arg("step").toInt();
    bool active = server.arg("active") == "true";
    
    if (track >= 0 && track < NUM_DRUM_TRACKS && step >= 0 && step < 16) {
      bool old_value = web_sequence[track][step];
      web_sequence[track][step] = active;
      
      // Force value confirmation and setting
      if (active) {
        web_sequence[track][step] = true;
      } else {
        web_sequence[track][step] = false;
      }
      
      // Re-confirm setting was applied
      bool final_value = web_sequence[track][step];
      
      Serial.print("Sequence update: Track ");
      Serial.print(track);
      Serial.print(" Step ");
      Serial.print(step);
      Serial.print(" changed from ");
      Serial.print(old_value ? "true" : "false");
      Serial.print(" to ");
      Serial.print(final_value ? "true" : "false");
      Serial.println();
      
      if (final_value == active) {
        server.send(200, "application/json", "{\"status\":\"ok\",\"track\":" + String(track) + ",\"step\":" + String(step) + ",\"active\":" + (active ? "true" : "false") + "}");
      } else {
        Serial.println("ERROR: Failed to set sequence value!");
        server.send(500, "application/json", "{\"error\":\"Failed to update sequence\"}");
      }
    } else {
      server.send(400, "application/json", "{\"error\":\"Invalid parameters\"}");
    }
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing parameters\"}");
  }
}

void handle_transport_control() {
  if (server.hasArg("action")) {
    String action = server.arg("action");
    
    if (action == "play") {
      web_play();
    } else if (action == "stop") {
      web_stop();
    } else if (action == "reset") {
      web_reset();
    } else {
      server.send(400, "application/json", "{\"error\":\"Invalid action\"}");
      return;
    }
    
    server.send(200, "application/json", "{\"status\":\"ok\",\"action\":\"" + action + "\"}");
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing action parameter\"}");
  }
}

void handle_status() {
  server.send(200, "application/json", get_current_status_json());
}

void handle_not_found() {
  server.send(404, "text/plain", "Not found");
}

// BPM update handler with high precision timer support
void handle_bpm_update() {
  if (server.hasArg("bpm")) {
    int new_bpm = server.arg("bpm").toInt();
    if (new_bpm >= 60 && new_bpm <= 180) {
      web_bpm = new_bpm;
      
      // Update hardware timer interval
      update_timer_interval();
      
      Serial.print("BPM updated to: ");
      Serial.print(web_bpm);
      Serial.println(" with hardware timer precision");
      
      server.send(200, "application/json", "{\"status\":\"ok\",\"bpm\":" + String(web_bpm) + "}");
    } else {
      server.send(400, "application/json", "{\"error\":\"Invalid BPM range\"}");
    }
  } else {
    server.send(400, "application/json", "{\"error\":\"Missing BPM parameter\"}");
  }
}

void trigger_drum_sample(int drum_id) {
  // Direct trigger using audio_engine functions
  switch (drum_id) {
    case 0: trigger_kick(); Serial.println("KICK triggered"); break;
    case 1: trigger_snare1(); Serial.println("SNARE1 triggered"); break;
    case 2: trigger_snare2(); Serial.println("SNARE2 triggered"); break;
    case 3: trigger_hihat1(); Serial.println("HIHAT1 triggered"); break;
    case 4: trigger_hihat2(); Serial.println("HIHAT2 triggered"); break;
    case 5: trigger_clap(); Serial.println("CLAP triggered"); break;
    case 6: trigger_water(); Serial.println("WATER triggered"); break;
    case 7: trigger_snap(); Serial.println("SNAP triggered"); break;
    default:
      Serial.println("Invalid drum ID: " + String(drum_id));
      break;
  }
}

// web_play() function using high precision timer
void web_play() {
  Serial.println("=== STARTING PRECISION PLAYBACK ===");
  Serial.println("Current sequence state:");
  
  // Detailed log output of current sequence state
  for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
    Serial.print("Track ");
    Serial.print(track);
    Serial.print(" (");
    if (track < 8) {
      const char* track_names[] = {"KICK", "SNARE1", "SNARE2", "HIHAT1", "HIHAT2", "CLAP", "WATER", "SNAP"};
      Serial.print(track_names[track]);
    }
    Serial.print("): ");
    
    bool has_active_steps = false;
    for (int step = 0; step < 16; step++) {
      Serial.print(web_sequence[track][step] ? "1" : "0");
      if (web_sequence[track][step]) {
        has_active_steps = true;
      }
    }
    Serial.print(" -> ");
    Serial.println(has_active_steps ? "HAS ACTIVE STEPS" : "NO ACTIVE STEPS");
  }
  
  web_sequence_playing = true;
  web_current_step = 0;
  timer_triggered = false;
  
  // Enable hardware timer
  timerAlarmEnable(sequenceTimer);
  
  Serial.println("Precision playback started!");
  Serial.println("========================");
}

// web_stop() function using high precision timer
void web_stop() {
  web_sequence_playing = false;
  
  // Disable hardware timer
  if (sequenceTimer) {
    timerAlarmDisable(sequenceTimer);
  }
  
  Serial.println("Precision playback stopped");
}

void web_reset() {
  web_stop();
  web_current_step = 0;
  
  // Clear sequence completely
  for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
    for (int step = 0; step < 16; step++) {
      web_sequence[track][step] = false;
    }
  }
  
  Serial.println("Web sequence reset - ALL steps cleared");
  Serial.println("Sequence state after reset:");
  for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
    Serial.print("Track ");
    Serial.print(track);
    Serial.print(": ");
    for (int step = 0; step < 16; step++) {
      Serial.print(web_sequence[track][step] ? "1" : "0");
    }
    Serial.println();
  }
}

String get_current_status_json() {
  DynamicJsonDocument doc(1024);
  
  doc["playing"] = web_sequence_playing;
  // Return current playing step accurately
  // When playing, return the next step to be played (to match current UI)
  doc["current_step"] = web_sequence_playing ? web_current_step : 0;
  doc["bpm"] = web_bpm;
  
  // Add sequence data with error checking
  JsonArray sequence = doc.createNestedArray("sequence");
  for (int track = 0; track < NUM_DRUM_TRACKS; track++) {
    JsonArray track_data = sequence.createNestedArray();
    for (int step = 0; step < 16; step++) {
      track_data.add(web_sequence[track][step]);
    }
  }
  
  String output;
  serializeJson(doc, output);
  
  // Detailed debug log for sync confirmation
  static unsigned long last_debug_time = 0;
  if (millis() - last_debug_time > 3000) { // Detailed log every 3 seconds
    last_debug_time = millis();
    Serial.println("=== SYNC STATUS DEBUG ===");
    Serial.print("Playing: ");
    Serial.println(web_sequence_playing ? "true" : "false");
    Serial.print("Current Step (server): ");
    Serial.println(web_current_step);
    Serial.print("BPM: ");
    Serial.println(web_bpm);
    
    if (web_sequence_playing) {
      Serial.print("Next audio trigger on step: ");
      Serial.println(web_current_step);
    }
    
    Serial.println("=========================");
  }
  
  return output;
}