#include "web_ui.h"
#include "web_js.h"
#include "retro_styles.h"  

const char* drum_names[] = {
  "KICK", "SNARE1", "SNARE2", "HIHAT1", "HIHAT2", "CLAP", "WATER", "SNAP"
};

const char* drum_colors[] = {
  "#ff4444", "#44ff44", "#4444ff", "#ffff44", "#ff44ff", "#44ffff", "#88ff88", "#ff8844"
};

String getWebUIHTML() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<meta charset=\"UTF-8\">";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<title>ESP32 Drum Machine</title>";
  html += "<style>" + getCSS() + "</style>";  // Use integrated CSS function
  html += "</head><body>";
  html += "<div class=\"container\">";
  html += "<header><h1>ESP32 Drum Machine</h1></header>";
  html += "<main>";
  html += getDrumPadHTML();
  html += getTransportHTML();
  html += getSequencerHTML();
  html += getStatusHTML();
  html += "</main></div>";
  html += "<script>" + getDrumMachineJS() + "</script>";
  html += "</body></html>";
  return html;
}

String getDrumPadHTML() {
  String html = "<section class=\"section\"><h2>Drum Pads</h2>";
  html += "<div class=\"drum-pads\">";
  for (int i = 0; i < 8; i++) {
    // Add colored accent to drum pads
    html += "<button class=\"drum-pad\" style=\"border-left:6px solid " + String(drum_colors[i]) + "\" onclick=\"triggerDrum(" + String(i) + ")\">";
    html += String(drum_names[i]) + "</button>";
  }
  html += "</div></section>";
  return html;
}

String getTransportHTML() {
  String html = "<section class=\"section\"><h2>Transport Controls</h2>";
  html += "<div class=\"transport-controls\">";
  html += "<button class=\"transport-btn play-btn\" onclick=\"transportControl('play')\">▶ PLAY</button>";
  html += "<button class=\"transport-btn stop-btn\" onclick=\"transportControl('stop')\">⏹ STOP</button>";
  html += "<button class=\"transport-btn reset-btn\" onclick=\"transportControl('reset')\">🔄 RESET</button>";
  html += "</div>";
  html += "<div class=\"bpm-control\">";
  html += "<label for=\"bpmSlider\">BPM:</label> ";
  html += "<input type=\"range\" id=\"bpmSlider\" min=\"60\" max=\"180\" value=\"120\" onchange=\"updateBPM(this.value)\"> ";
  html += "<span id=\"bpmValue\">120</span>";
  html += "</div></section>";
  return html;
}

String getSequencerHTML() {
  String html = "<section class=\"section\"><h2>16-Step Sequencer</h2>";
  html += "<div class=\"sequence-container\">";
  html += "<div class=\"sequence-grid\" id=\"sequenceGrid\">";
  
  // Header row - step numbers
  html += "<div class=\"track-label\">TRACK</div>";
  for (int step = 0; step < 16; step++) {
    html += "<div class=\"track-label\">" + String(step + 1) + "</div>";
  }
  
  // Track rows - each drum track
  for (int track = 0; track < 8; track++) {
    // Add colored accent to track labels
    html += "<div class=\"track-label\" style=\"background:linear-gradient(135deg,var(--mac-gray) 0%,var(--mac-light-gray) 100%);";
    html += "border-left:4px solid " + String(drum_colors[track]) + ";color:var(--mac-black);font-weight:bold\">";
    html += String(drum_names[track]) + "</div>";
    
    // Step buttons
    for (int step = 0; step < 16; step++) {
      html += "<button class=\"step-button\" ";
      html += "id=\"step_" + String(track) + "_" + String(step) + "\" ";
      html += "onclick=\"toggleStep(" + String(track) + "," + String(step) + ")\" ";
      html += "aria-label=\"Track " + String(drum_names[track]) + " Step " + String(step + 1) + "\" ";
      html += "data-track=\"" + String(track) + "\" data-step=\"" + String(step) + "\" ";
      html += "style=\"border-color:" + String(drum_colors[track]) + "20\">";  // Light color for border
      html += "</button>";
    }
  }
  
  html += "</div></div>";
  
  // Instructions - improved for better visibility
  html += "<div style=\"font-family:Monaco,Consolas,monospace;";
  html += "background:var(--mac-white);";
  html += "color:var(--mac-black);";
  html += "border:2px inset var(--mac-gray);";
  html += "padding:clamp(8px,2vw,12px);";
  html += "text-align:center;";
  html += "font-size:clamp(11px,2vw,14px);";
  html += "margin-top:10px;";
  html += "box-shadow:inset 1px 1px 2px rgba(0,0,0,0.1);\">";
  html += "💡 Tap to select steps | Horizontal scroll available | Green = Active";
  html += "</div>";
  
  html += "</section>";
  return html;
}

String getStatusHTML() {
  String html = "<section class=\"section\"><h2>System Status</h2>";
  html += "<div class=\"status-info\">";
  html += "<p>🎵 Playing: <span id=\"playStatus\">Stopped</span></p>";
  html += "<p>📍 Step: <span id=\"currentStep\">-</span>/16</p>";
  html += "<p>⚡ BPM: <span id=\"currentBPM\">120</span></p>";
  html += "<p>🔊 Volume: <span id=\"volumeLevel\">100%</span></p>";
  html += "</div>";
  html += "</section>";
  return html;
}