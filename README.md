# EKOS Firmware

> The open-source firmware powering EKOS.  
> A calm, open, and long-lasting connected e-paper display — designed to respect your space and your time.

![EKOS Device](https://ekosboard.com/assets/desktop_DSCF7619-CdRnGBlO.avif)

---

## What is EKOS?

EKOS is an open-source connected e-paper display powered by an ESP32-S3.  

It is designed to show essential information without notifications, feeds, or distractions.  
Low power, always visible, and fully under your control.

More about the project:  
> https://ekosboard.com

---

## Mobile App

EKOS can be used with the official mobile application, available on iOS and Android.

The app makes device setup and widget management easier, but it is completely optional.  
The firmware exposes a local REST API for full standalone control.

Download the app:
- iOS → Coming soon
- Android → Coming soon

---

## About This Repository

This repository contains the official firmware running on EKOS devices.

It is responsible for:

- Display rendering (LVGL-based UI)
- Widget management
- Wi-Fi provisioning
- File storage (LittleFS)
- Power management

The firmware is fully open-source and designed to be extended.

---

## Key Features

- ESP32-S3 based architecture  
- Modular widget system  
- Structured JSON widget templates  
- Local REST API  
- No cloud dependency  
- Designed for low power consumption  

---

## Quick Start

### Requirements

- ESP32-S3 (N16R8 recommended)
- ESP-IDF v5.x
- Supported e-paper display

### Build & Flash

```bash
git clone https://github.com/ekosboard/firmware.git
cd firmware

idf.py set-target esp32s3
idf.py build
idf.py flash monitor
```

For full configuration and advanced setup, see the documentation.

---

## Documentation

Complete documentation is available at:
> https://doc.ekosboard.com

---

## Hardware

Official hardware files (PCB, enclosure, schematics) are available here:
> https://github.com/ekosboard/hardware

---

## Community

Join the EKOS community:
- Reddit → https://reddit.com/r/ekosboard
- Discord → https://discord.gg/vARyTqtA6H

Feedback, ideas and contributions are welcome.

---

## Buy a Board

Official EKOS devices will be available at:
> https://buy.ekosboard.com

---

## Contributing

Contributions are welcome.

If you would like to:
- Improve the firmware
- Create new widgets
- Fix bugs
- Propose enhancements

Please open an issue or submit a pull request.  
Before contributing, make sure to read the documentation.

---

## License

This project is licensed under the GNU General Public License v3.0 (GPL-3.0).

You are free to use, modify and distribute this software.
If you distribute modified versions, you must also release your changes under GPLv3.

See the `LICENSE` file for full details.
