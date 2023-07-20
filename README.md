# OpenPDM: Programmable Power Distribution Module for Your Car Project

**Disclaimer: This project is a work in progress! Don't blow up your stuff**

OpenPDM is an open-source, programmable Power Distribution Module for car enthusiast and electronics aficionados. It is being developed by me, as my undergrad thesis. Designed to cater to the needs of electronics lovers, car enthusiasts, and tinkerers alike, OpenPDM aims to bring cheaply programmable fusebox capabilities to your project car.

## Features
- Utilizes the STM32 Blue Pill Board as the core controller
- Provides 4 high-side outputs capable of handling up to 10 Amps and 4 outputs supporting up to 20 Amps.
- Current sensing using INA180s.
- Equipped with 8 generic inputs that support signals up to 15 V, enabling seamless integration with your custom setups.
- CAN communication with an Arduino-style module (MCP2515).
- [NOT WORKING] Utilizes the internal CAN controller of the STM32F103C8T6 to provide an additional CAN channel.
- Programmable by editing a file at core/src/pdm_cfg.c.
- Auto-resetable outputs, inrush current time configuration

## What is working
- Tested CAN Arduino module for reliable sending and receiving of data.
- Verified activation of output channels based on configured conditions.
- Conducted tests to disable outputs in case of overcurrent, overvoltage and undervoltage situations.
- Verified the functionality of input channels as analog inputs.

## Hardware rambling
The PCB is a 100x100mm 4 layer board using 1 Oz copper for the outer layers and 0.5 Oz copper for the inner layers (the cheapest specs from JLCPCB). Parallel layers where used to distribute the current density, allowing for a greater current capability of the thin layers used.
MOSFETs were used instead of those smart switches, like the Infineon ones, because it is cheaper.  

### PCB summary
- Manufactured by JLCPCB
- $40.00 including shipping to Brazil
- 4 Layer, 1 Oz external and 0.5 internal copper thickness.
- Single [IRFR7440TRPBF](https://www.infineon.com/dgdl/Infineon-IRFR7440-DataSheet-v01_01-EN.pdf?fileId=5546d462533600a4015356359e662117) for 10A outputs, double for 20A outputs.
- INA180A2 and A3 with 3mΩ shunt resistor for current sensing
- Simple voltage divider for input sensing

### The Bad
The PCB is the weakest point on this project version. I've designed it in 1 week as needed it to help me develop the software. The time budget for developing this project was also only 3-4months. I've made a lot of cost cutting, because I'm a broke college student, this version of the PDM costs around $40.00 including shipping from LCSC and the PCB from JLCPCB, which isn't so much of a feature, more like there are missing redudancy and filtering stuff.

## Disclaimer
Please note that OpenPDM is still in the early stages of development and has not been thoroughly tested with nominal current or in an automotive environment. Therefore, it is not even in a "ready-to-blow-up-your-car" stage. 
<!--stackedit_data:
eyJoaXN0b3J5IjpbMjEzMTU2Mzk0NiwtMTYwNDgxNDAwMywtMT
g3MDAwMjM5MV19
-->