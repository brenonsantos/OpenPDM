# OpenPDM: Programmable Power Distribution Module for Your Car Project

**Disclaimer: This project is a work in progress! Don't blow up your stuff**
If you want to contribute, discuss something or chit-chat, please message me: brenonsantos96@gmail.com

OpenPDM is an open-source, programmable Power Distribution Module for car enthusiast and electronics aficionados. It is being developed by me, as my undergrad thesis. Designed to cater to the needs of electronics lovers, car enthusiasts, and tinkerers alike, OpenPDM aims to bring cheaply programmable fusebox capabilities to your project car.

![pcb_3dview](../assets/Imgs/pcb_top_bottom_3dview.png)

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

## How can I contribute
As this project is still in its early stage, contributing with work may be challenging (but I'm open to it, there is a lot to do!). Please message me first to discuss alignment and potential tasks.
More importantly, your experience, tips, or suggestions are highly welcome! If you have expertise in automotive electronics, have participated in SAE competitions, or have real-world experience, I'd love to have a conversation. ~~My experience is watching a lot of YouTube and daily driving some old shitboxes.~~

## Disclaimer
Please note that OpenPDM is still in the early stages of development and has not been thoroughly tested with nominal current or in an automotive environment. Therefore, it is not even in a "ready-to-blow-up-your-car" stage. 

## Hardware Rambling

![pcb_final](../assets/Imgs/pcb_final.png)

The PCB design features a 100x100mm 4-layer board using 1 Oz copper for the outer layers and 0.5 Oz copper for the inner layers (the cheapest specs from JLCPCB). Parallel layers were used to distribute the current density, allowing for a greater current capability of the thin layers used. MOSFETs were chosen instead of more advanced smart switches (like Infineon ones) to keep the project cost-effective. 

![pcb_interfaces](../assets/Imgs/pcb_interfaces.png)

### PCB Summary
- Manufactured by JLCPCB
- $40.00 including shipping to Brazil
- 4 Layer, 1 Oz external and 0.5 internal copper thickness.
- Single [IRFR7440TRPBF](https://www.infineon.com/dgdl/Infineon-IRFR7440-DataSheet-v01_01-EN.pdf?fileId=5546d462533600a4015356359e662117) for 10A outputs, double for 20A outputs.
- [INA180A2 and A3](https://www.ti.com/lit/ds/symlink/ina180.pdf) with 3mΩ shunt resistor for current sensing
- Simple voltage divider for input sensing

### The Bad
The current PCB design is a weak point in this version of the project. It was created in a week to support software development, and due to budget constraints, some cost-cutting measures were taken. As a result, there is missing redundancy and filtering components. I'll learn more about PCB design and scrap this version, and any help or expertise in this area would be greatly appreciated. 

## Software Rambling
The software architecture was based on AUTOSAR because we thought it would be cool. Problem is, I didn't knew anything about AUTOSAR before starting this project, so it is kind of messy. For the next version I'll simplify the architecture and port the code to C++. 
The configuration of the PDM is done by modifying a single file at core/src/pdm_cfg.c. [More about this](Software/stm32f103c8t6_v0.1/README.md).



<!--stackedit_data:
eyJoaXN0b3J5IjpbODMzMDEwOTMwLDIwNDU0MDk3NzUsMTY2OT
k3MjYwOCwtMTg0NTQzMzg3MCwxMzY0ODYzNTMzLC0xNjA0ODE0
MDAzLC0xODcwMDAyMzkxXX0=
-->
