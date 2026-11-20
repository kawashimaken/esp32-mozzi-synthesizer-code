# ESP32 Bluetooth speaker (PlatformIO)

Arduinoスケッチを通常のESP32向けに変換した、
MAX98357Aで音声を出力するBluetooth A2DP受信機です。
元のArduinoスケッチは削除し、このPlatformIOプロジェクトに統合しています。

## 対応ボード

- ESP32-WROOM-32などの通常のESP32（PlatformIOの `esp32dev`）
- ESP32-S3 / S2 / C3などは対象外です。Classic Bluetoothが必要です。
- Mozziやシンセサイザー機能は使用しない、独立したスピーカープロジェクトです。

## 配線

`drum_external_dac_long_music` と同じピン配置です。以下の配線に合わせてください。
通常のESP32でフラッシュに使われるGPIO7は使用しません。

| MAX98357A | ESP32 |
| --- | --- |
| BCLK | GPIO26 |
| LRC / WS | GPIO25 |
| DIN | GPIO5 |
| GND | GND（電源と共通） |
| VIN | 使用するMAX98357Aモジュール仕様に合う電源 |

スピーカーはMAX98357AのSPK+ / SPK-間へ接続してください。
モジュールにSD / EN端子がある場合は、モジュール仕様に従って有効にしてください。
ピン番号とBluetooth名は `src/main.cpp` 冒頭で変更できます。

## ビルド・書き込み

VS CodeのPlatformIOで、このフォルダー（`platformio/bluetooth_speaker`）を開きます。
CLIの場合は、このフォルダーで次を実行してください。

```sh
pio run
pio run --target upload
pio device monitor
```

PCやスマートフォンで `ESP32 Speaker` とペアリングし、音声の出力先に選択します。
シリアルモニターは115200 baudです。

## 依存関係

`platformio.ini` でバージョンを固定しています。初回ビルド時に自動取得されます。

- Espressif32 6.10.0（Arduino-ESP32 2.0.17）
- [ESP32-A2DP v1.8.8](https://github.com/pschatzmann/ESP32-A2DP/tree/v1.8.8)

元のスケッチのI2S設定を維持するため、Arduino 2.xのI2Sドライバーを使用しています。
接続通知はA2DP用の `set_on_connection_state_changed()` に修正しています。
Arduino 3.xへ更新する場合はI2S出力方式も見直してください。
