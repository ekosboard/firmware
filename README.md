# Smart Paper

Smart Paper is an open-source project designed to control an e-paper display using an ESP32-S3 microcontroller. The display can be accessed over Wi-Fi and is controllable through a RESTful API.  
This repository focuses on the ESP32 firmware that drives the e-paper display and handles communication with the mobile app.  

## Features

- Control e-paper display via a RESTful API.  
- Wi-Fi configuration for network communication.  
- Support for partial and full refresh of the e-paper screen.  
- Flexible screen content updates, including text, QR codes, and other graphical elements.  
- Modular design for future display types and resolutions.  

## Hardware

- **Microcontroller**: ESP32-S3 N16R8 (16 MB flash, 8 MB PSRAM).  
- **[Display](#supported-displays)**: E-paper display (EPD) driven by a custom driver integrated into the ESP32 firmware.  

## Getting Started

### Prerequisites

- **ESP32-S3 Development Board**: Make sure you have the ESP32-S3 N16R8 variant.  
- **ESP-IDF**: Ensure that the ESP-IDF (v5.1.4 or higher) is installed on your machine. You can find installation instructions [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/get-started/index.html#installation).  
- **Toolchain**: The necessary toolchain for compiling ESP32 projects should be installed as part of the ESP-IDF setup.  

### Installation

1. Clone this repository:  
    ```bash
    git clone https://github.com/yourusername/smart-paper.git
    cd smart-paper
    ```

2. Set up the ESP-IDF environment:  
    ```bash
    . $HOME/esp/esp-idf/export.sh
    ```

3. Configure the project:  
    ```bash
    idf.py set-target esp32s3
    idf.py menuconfig
    ```
   Be sure to set your display and other [configurations](#configuration) to suit your environment.  

4. Compile and flash the firmware:  
    ```bash
    idf.py build
    idf.py flash
    ```

5. Monitor the ESP32 for output logs:  
    ```bash
    idf.py monitor
    ```

6. Compile, flash and monitor  
    ```bash
    idf.py flash monitor
    ```

### Configuration

```bash
idf.py menuconfig
```

#### 1. Display

```markdown
Select your display:

    Main menu -> Display Configuration
```

#### 2. LVGL

```markdown
LVGL configuration:

    Main menu -> Component config -> LVGL configuration

Color depth:

    Color Settings -> Color depth -> 
        - [x] 1 byte per pixel (for monochrome display)
        - [ ] 8 RGB232 (for 4 grayscale display)
        - [ ] 16 RGB565 (for 16 grayscale display)

HAL Settings:
Font Usage:

    Font Usage -> Enable built-in fonts ->
        - [x] Montserrat 14
        - [x] Montserrat 20
        - [x] Montserrat 24
        - [x] Montserrat 30

Widget Usage:
Themes:

3rd Party Libraries:

    3rd Party Libraries ->
        - [x] QR code library
```

#### 3. CPU

```markdown
CPU frequency:

    Main menu -> Component config -> ESP System Settings ->
        - CPU frequency ->
            - [x] 240 MHz
```

#### 4. PSRAM

```markdown
PSRAM configuration:

    Main menu -> Component config -> ESP PSRAM ->
        - [x] Support for external, SPI-connected RAM

        -> SPI RAM config ->
        - Mode of SPI RAM ->
            - [x] Octal
        - Type of SPIRAM chip in use ->
            - [x] Auto-detect
        - [x] Initialize SPI RAM during startup
        - SPI RAM access method ->
            - [x] Make RAM allocatable using malloc() as well
        - [x] Run memory test on SPI RAM initialization
        - [x] Try to allocate WiFi and LWIP in SPIRAM firstly
        - [x] Allow .bss segment placed in external memory
```

#### 5. SPI Flash

```markdown
SPI Flash configuration:

    Main menu -> Serial flasher config ->
        - [x] Choose flash mode automatically
        - Flash SPI mode ->
            - [x] DIO
        - Flash Sampling Mode ->
            - [x] STR Mode
        - Flash SPI speed ->
            - [x] 80 MHz
        - Flash size ->
            - [x] 16 MB
        - [x] Detect flash size when flashing bootloader
```

#### 6. FreeRTOS

```markdown
FreeRTOS configuration:

    Main menu -> Component config -> FreeRTOS -> Kernel ->
        - configTICK_RATE_HZ ->
            - 1000
        - configMAX_TASK_NAME_LEN ->
            - 32
```

#### 7. Partition Table

```markdown
Partition Table configuration:

    Main menu -> Partition Table -> Partition Table ->
        - [x] Custom partition
        - Custom partition CSV file ->
            - partitions.csv
        - Offset of partition table ->
            - 0x8000
        - [x] Generate an MD5 checksum for the partition table
```

#### 8. FAT filesystem

```markdown
Fat filesystem configuration:

    Main menu -> Component config -> FAT filesystem support ->
        - Long filename support ->
            - Long filename buffer in heap
        - Max long filename length ->
            - 255
```

## API Reference

### RESTful Endpoints

OpenAPI specification file (Swagger) soon available.  

## Usage

Once the firmware is running on your ESP32-S3 device, it will initially broadcast its own Wi-Fi network. A QR code will be displayed on the e-paper screen, which you can scan to connect your mobile device to the ESP32's network. From there, you will be able to provide the credentials to your local Wi-Fi network.  

After the ESP32 successfully connects to your Wi-Fi network, it will expose a RESTful API. You can then use this API to send commands from a mobile app or any HTTP client to control the e-paper display.  

## Supported Displays

Here are the supported e-paper displays compatible with the Smart Paper project:  

- GDEY042T81 (4.2-inch, 400x300, black, white, and 4 grayscale levels)  
- Additional models coming soon...  


## Contributing

## License

---

### Future Sections

- **Display Driver**: Details about the e-paper driver integration.  
- **LVGL Integration**: Documentation on how LVGL is used to manage the screen's graphical elements.  
