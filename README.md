# esp32-mozzi-synthesizer-code

Code for a tiny synthesizer built with an ESP32, running the Mozzi library. It's simple, compact, and powerful.

You can find the info of the Hardware here :https://www.pcbway.com/project/shareproject/ESP32_Mozzi_synthesizer_3a3e8f1a.html

## Project Overview

This project implements a versatile drum machine and synthesizer using the ESP32 microcontroller and the Mozzi audio synthesis library. The codebase includes multiple implementations showcasing different audio output methods and feature sets, from basic internal DAC output to advanced web-controlled drum machines with external DACs.

## Folder Structure

### `platformio/drum_internal_dac/`
Basic drum machine implementation using ESP32's built-in 8-bit DAC for audio output.

### `platformio/drum_external_dac/`
Basic drum machine implementation using ESP32's external DAC for audio output.

### `platformio/drum_external_dac_long_music/`
Drum machine with external DAC support for higher quality audio output and playing long music.

### `platformio/drum_external_dac_web/`
Web-controlled drum machine with external DAC and modern web interface:
- WiFi-enabled browser control
- Real-time step sequencer with retro Mac-style UI
- Connect to `DrumMachine-AP` WiFi and visit `http://192.168.4.1`

## Getting Started

1. Install [PlatformIO](https://platformio.org/) for VS Code
2. Open desired project folder
3. Build and upload: `pio run --target upload`
4. For web versions: Connect to WiFi AP and open browser to IP address

### Configuration
- Each project includes a `platformio.ini` file with ESP32-specific settings
- Modify `config_wifi.h` for custom WiFi settings (web versions)
- Audio output pins and DAC settings can be adjusted in the respective configuration files

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Test thoroughly on hardware
4. Submit a pull request with clear description

## License

This project is open source. Please check individual file headers for specific license information.
