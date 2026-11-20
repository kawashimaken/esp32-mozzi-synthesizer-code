#include <Arduino.h>
#include <BluetoothA2DPSink.h>

namespace {
// Same I2S wiring as drum_external_dac_long_music.
// GPIO6-11 are reserved for flash on common ESP32 modules.
constexpr int I2S_BCLK_PIN = 26;
constexpr int I2S_LRC_PIN = 25;
constexpr int I2S_DOUT_PIN = 5;
constexpr char BT_DEVICE_NAME[] = "ESP32 Speaker";

BluetoothA2DPSink a2dp_sink;

void on_connection_state_changed(esp_a2d_connection_state_t state, void *) {
    if (state == ESP_A2D_CONNECTION_STATE_CONNECTED) {
        Serial.println("[BT] Connected!");
    } else if (state == ESP_A2D_CONNECTION_STATE_DISCONNECTED) {
        Serial.println("[BT] Disconnected.");
    }
}
}  // namespace

void setup() {
    Serial.begin(115200);
    Serial.println("ESP32 BT Speaker starting...");

    i2s_config_t i2s_config = {};
    i2s_config.mode = static_cast<i2s_mode_t>(I2S_MODE_MASTER | I2S_MODE_TX);
    i2s_config.sample_rate = 44100;
    i2s_config.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
    i2s_config.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
    i2s_config.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    i2s_config.intr_alloc_flags = ESP_INTR_FLAG_LEVEL1;
    i2s_config.dma_buf_count = 8;
    i2s_config.dma_buf_len = 1024;
    i2s_config.use_apll = false;
    i2s_config.tx_desc_auto_clear = true;
    i2s_config.fixed_mclk = 0;

    i2s_pin_config_t pin_config = {};
    pin_config.mck_io_num = I2S_PIN_NO_CHANGE;
    pin_config.bck_io_num = I2S_BCLK_PIN;
    pin_config.ws_io_num = I2S_LRC_PIN;
    pin_config.data_out_num = I2S_DOUT_PIN;
    pin_config.data_in_num = I2S_PIN_NO_CHANGE;

    a2dp_sink.set_i2s_config(i2s_config);
    a2dp_sink.set_pin_config(pin_config);
    a2dp_sink.set_on_connection_state_changed(on_connection_state_changed);
    a2dp_sink.start(BT_DEVICE_NAME);

    Serial.printf("Bluetooth name: \"%s\"\n", BT_DEVICE_NAME);
    Serial.println("Waiting for connection...");
}

void loop() {
    // Bluetooth reception and I2S playback run in background tasks.
    delay(1000);
}
