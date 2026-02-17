# Digital Oil Lamp Project

This project controls a set of LEDs (simulating oil lamps) via a web interface hosted on an ESP32. The system consists of an **ESP32** acting as the web server and controller, communicating via Serial UART with an **Arduino Mega** which handles the physical LED hardware.

## Features

- **Web Interface**: A responsive HTML page hosted on the ESP32 allows users to toggle individual lamps on/off.
- **Visual Feedback**: The interface displays images of oil lamps (lit/unlit) updated in real-time.
- **Hardware Control**: The Arduino Mega drives up to 16 LEDs.
- **Animation**: LEDs blink 3 times before switching states (ON/OFF) for a visual effect.
- **Communication**: ESP32 and Arduino Mega communicate via Serial (UART).

## Hardware Requirements

1.  **ESP32 Development Board**: Handles Wi-Fi and the web server.
2.  **Arduino Mega 2560**: Handles the GPIO control for the LEDs.
3.  **LEDs (x16)**: To simulate the lamps.
4.  **Resistors**: Appropriate current-limiting resistors for the LEDs.
5.  **Jumper Wires**: For connections.
6.  **Power Supply**: Adequate power for both boards and LEDs.

## Pinout & Wiring

### ESP32 to Arduino Mega Connection
| ESP32 Pin | Arduino Mega Pin | Function |
| :--- | :--- | :--- |
| GPIO 18 (TX) | Pin 10 (RX) | Serial Data (ESP -> Mega) |
| GPIO 19 (RX) | Pin 11 (TX) | Serial Data (Mega -> ESP) |
| GND | GND | Common Ground |

*Note: The Arduino Mega uses `SoftwareSerial` on pins 10 and 11 to communicate with the ESP32.*

### Arduino Mega LED Connections
The LEDs are connected to the following pins on the Arduino Mega:
`22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 2, 3, 4, 5, 6, 7`

## Software Setup

### Prerequisites
- [Arduino IDE](https://www.arduino.cc/en/software) installed.
- **ESP32 Board Package** installed in Arduino IDE.
- **Libraries**:
  - `WiFi` (Standard ESP32 lib)
  - `WebServer` (Standard ESP32 lib)
  - `FS` & `SPIFFS` (Standard ESP32 libs)
  - `SoftwareSerial` (Standard Arduino lib)

### Configuration

1.  **WiFi Credentials**:
    Open `Oil_Lamp_ESP32.ino` and update the following lines with your network details:
    ```cpp
    const char *ssid = "YOUR_WIFI_SSID";
    const char *password = "YOUR_WIFI_PASSWORD";
    ```

2.  **Change Background Image (Optional)**:
    - Go to [oillamp.inovoid.me](https://oillamp.inovoid.me).
    - Sign up and log in.
    - Upload your picture.
    - Copy the image URL and paste it into `Oil_Lamp_ESP32.ino` under:
      ```css
      background-image: url('YOUR_IMAGE_URL');
      ```

3.  **Upload to ESP32**:
    - Select your ESP32 board in Arduino IDE.
    - Connect the ESP32 via USB.
    - Upload `Oil_Lamp_ESP32.ino`.
    - *Optional*: If you want to serve local files, ensure you upload the SPIFFS filesystem data (though the current code pulls images from the web).

3.  **Upload to Arduino Mega**:
    - Select "Arduino Mega or Mega 2560" in Arduino IDE.
    - Connect the Mega via USB.
    - Upload `Oil_Lamp_Arduino_Mega.ino`.

## Usage

1.  Power on both the ESP32 and Arduino Mega.
2.  Open the Serial Monitor for the ESP32 (Baud 115200) to check the connection status.
3.  Once connected, the ESP32 will print the **IP Address** assigned to it (e.g., `192.168.1.100`).
4.  Open a web browser on a device connected to the same network and navigate to that IP Address.
5.  You will see a grid of oil lamp images. Click any lamp to toggle it ON or OFF.
    - **ON**: The corresponding LED on the Mega will blink 3 times and then stay lit.
    - **OFF**: The corresponding LED will blink 3 times and then turn off.

## Notes
- The Web Interface currently generates buttons for 20 lamps, but the Arduino Mega code is configured to handle the first 16.
- The web page images are loaded from an external Supabase storage URL, so the device viewing the page needs internet access.

## Gallery

### 1. Web Interface
*(Add a screenshot of your web interface here)*
![Web Interface Placeholder](https://via.placeholder.com/600x400?text=Web+Interface+Screenshot)

### 2. Oil Lamp
![Oil Lamp](https://prhayvjhhvikyogvygja.supabase.co/storage/v1/object/public/images/3e267225-3d4a-4ca5-af36-e959ec9009ae/00ed7cce-4792-41b3-8e33-42235e2ac2da.jpeg)
