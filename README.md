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
- Conducted tests to disable outputs in case of overcurrent, overvoltage and undercurrent situations.
- Verified the functionality of input channels as analog inputs.

## Hardware rambling
The PCB is the weakest point on this project version. I've designed it in 2 weeks 

## Disclaimer
Please note that OpenPDM is still in the early stages of development and has not been thoroughly tested with nominal current or in an automotive environment. Therefore, it is not even in a "ready-to-blow-up-your-car" stage. 
<!--stackedit_data:
eyJoaXN0b3J5IjpbMzYwNTQ2MzI4XX0=
-->