# GHero20 Wireless BLE

*Handwired, fully customizable, 3D printed, wireless BLE, and modular guitar controller for clone hero. 20% keyboard (10 fret buttons, strum up/down, 4 macro buttons, and a rotary volume encoder).*

* Keyboard Maintainer: [bryan065](https://github.com/yourusername)
* Hardware Supported: Adafruit Feather 32u4 Bluefruit LE (https://learn.adafruit.com/adafruit-feather-32u4-bluefruit-le)

Make example for this keyboard (after setting up your build environment):

    make GHero20:default

Flashing example for this keyboard:

    make GHero20:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

# Features
- Wirless BLE / Wired USB Modes
- Wireless Qi charging / MagSafe compatible
- 5 normal frets (mechanical)
- 5 quick frets (mouse microswitch)
- customizable, tunable strum bar (mechanical)
- 4 programmable macro keys (start/select/star power/etc)
- Accelerometer for tilt star power

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available

## Wiring

![Alt text](/keyboards/handwired/GHero20/Layout-Wiring.png?raw=true "")

## To-do

- [ ] Accelerometer / Gyroscope for tilt control (star power)
    - MPU-9250
- [ ] OLED Display
    - Used for info display such as battery life
- [ ] Additional ground breakouts for WS2812, MPU-9250, and OLED.
- [ ] Update Bluefruit code to enable BT battery service (AT+BLEBATTEN)
- [ ] Update strum part to enable tuning
    - [x]  Tension
    - [ ]  Actuation distance/angle
    - [ ]  Shock absorbtion (bottoming out strum bar so you don't crush the switch)
- [x] Hotswap switch sockets
    - [x] Strum switches
    - [x] Macro switches
    - [x] ~~Fret switches~~ *(Not enough clearance in neck for sockets)*
        - *Upper neck would have to be redesigned to have a removable PCB part like the lower neck to accommodate something like Kailh low profile switches to make room for hotswap sockets.*
- [ ] Upload STL's for guitar components
- [ ] WS2812 RGB's
