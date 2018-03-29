# PSOC 5: FlySky iBus to USB joystick bridge

![device photo](https://raw.githubusercontent.com/kejran/PSoC-USB-iBus-Bridge/master/device.png)

This project aims to create a simple, inexpensive device for connecting FlySky iBus receivers to any USB host machine. The bridge registers as a generic HID joystick, allowing for usage of the transmitter in any game or simulator.

## Required components:
  - CY8CKIT-059 PSoC® 5LP Prototyping Kit _or a compatible, usb-capable board_
  - Any modern FlySky transmitter/receiver combo
  - Connectors 

## Capabilities

### Physical
  - 6 analog axes _(two gimbals, two pots)_
  - four digital buttons _(top switches)_

### Features
  - regular joystick emulation mode
  - inverse Y axis _(currently not working)_ 
  - positive range mode for compability with simulators _(see notes)_

## Compability
The device was tested with:
  - Windows 10 desktop pc
  - [CY8CKIT-059 PSoC® 5LP Prototyping Kit](http://www.cypress.com/documentation/development-kitsboards/cy8ckit-059-psoc-5lp-prototyping-kit-onboard-programmer-and)
  - [FlySky i6x transmitter](https://www.banggood.com/Flysky-FS-i6X-2_4GHz-10CH-AFHDS-2A-RC-Transmitter-With-X6B-i-BUS-Receiver-p-1090406.html)
  - [FlySky x6b receiver](https://www.banggood.com/Flysky-X6B-2_4G-6CH-i-BUS-PPM-PWM-Receiver-for-AFHDS-i6s-i6-i6x-Transmitter-p-1101513.html)
  - [FPV Freerider](https://fpv-freerider.itch.io/fpv-freerider)
  - Flying Model Simulator
## Notes
    
FPV Freerider requires all axes to be [0, 1] instead of [-1, 1]. I am unsure if this is caused by the HID descriptor or something else, but a new compability mode was added to address this.