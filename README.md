# Multi-Input Motor Control System for a Arm Support for Wheelchair Users

The following code is part of a project that aims to create an arm support device designed for wheelchair users. The system allows the user to uplift his arm with motorized assistance in order to drink, eat and access his face. 

This project is an Arduino-based motor control system that supports multiple input methods:
- 🎮 Joystick
- 📏 Flex Sensor that can be fixed on a finger

The system supports **dynamic control mode switching**. This code was developed in order to implement easily sensor based control, having always the possibility to switch to joystick control. At the end you can found a simple procedure to add another input method is needed.

NOTE: For the Assistive Technologies Challenge, the user cannot use the flex sensor and the joystick was used as the only input method.


## 🎯 Features

- **Two Control Modes:**
  - Joystick
  - Flex Sensor
- **Dynamic Control Switching:** Seamless switching between control modes
- **PWM Ramping:** Smooth acceleration and deceleration of the motor
- **Battery Monitoring:** Checks battery voltage and indicates low battery status
- **LED Indicators:** Visual feedback for battery status
- **Modular Design:** Easy to add new control methods
- **Verbose Debug Output:** Controlled via a `verbose` flag in the `constants.h` file

## 🛠️ Usage

1. **Power On**: Connect the battery to the system.
2. **Control Mode**:

    IF Control Mode is set to **Flex Sensor**: 
    - By default, the system starts in Flex Sensor mode.
    - Press the switch button to toggle between Joystick and Flex Sensor Control modes.

    IF Control Mode is set to **Joystick**:
    - The system works in Joystick Control mode.
4. **Joystick Control MODE**:
    - Move the joystick up to lift the arm.
    - Move the joystick down to lower the arm.
5. **Flex Sensor Control MODE**:
    - Bend the flex sensor to lift the arm.
    - Straighten the flex sensor to lower the arm.
6. **Battery Monitoring**:
    - The system monitors battery voltage.
    - If the battery is low, the red LED will light up.
    - If the battery is medium, the blue LED will light up.
    - If the battery is full, the green LED will light up.


## 📁 Project Structure

```
├── include/
│ ├── config.h # Hardware definitions
│ ├── constants.h # Constants definition
│ ├── types.h # Type definitions and enums
│ ├── control.h # Core control logic
│ ├── joystick.h # Joystick interface
│ ├── motor.h # Motor control interface
│ ├── flexsensor.h # Flex sensor interface
│ ├── battery.h # Battery interface
│ ├── switch.h # Switch button interface
│ ├── led.h # LED interface
├── src/
│ ├── main.cpp # Main logic loop
│ ├── control.cpp # Control functions
│ ├── joystick.cpp # Joystick handling
│ ├── motor.cpp # Motor ramping
│ ├── flexsensor.cpp # Flex sensor angle detection
│ ├── battery.cpp # Battery voltage monitoring
│ ├── switch.cpp # Switch button handling
│ ├── led.cpp # LED indicator handling
├── lib/ # External libraries 
├── test/
├── platformio.ini # PlatformIO build configuration
├── .gitignore # Git ignore file
└── README.md # Project documentation
```

## 📝 Overview of the code

The code is structured to handle two control modes: Joystick and Flex Sensor. The main logic is in `main.cpp`, which initializes the system, sets up the control mode, and enters the main loop.

The control logic is modular, allowing for easy addition of new control methods. The `control.cpp` file contains the core logic for handling state changes based on the selected control mode. Each control method (joystick and flex sensor) has its own implementation in separate files (`joystick.cpp` and `flexsensor.cpp`). The switch button is handled in `switch.cpp`, allowing the user to toggle between control modes.

The motor control is handled in `motor.cpp`, which implements PWM ramping for smooth acceleration and deceleration. The battery monitoring is done in `battery.cpp`, which checks the battery voltage and updates the LED indicators accordingly using `led.cpp`.

To change the control mode, the user can modify the `DEFAULT_CONTROL` constant in `constants.h`. Other constants related to the control behavior, such as PWM ramping time and thresholds for joystick and flex sensor inputs, can also be adjusted in this file.

If the wiring is different from the default setup, the pin definitions can be changed in `config.h`. The project is designed to be easily extensible, allowing for the addition of new control methods by following a simple procedure outlined in the documentation.

A `verbose` flag in `constants.h` allows for enabling or disabling debug output to the Serial Monitor, which can be useful for troubleshooting and development.

## ⚙️ Setup

### 1. 📦 Prerequisites

- PlatformIO (in VS Code)
- Arduino-compatible board (here the Arduino Uno)
- Flex Sensor (with 47kΩ pull-down)


### 2. 🛠 Wiring

| Component      | Pin                |
|----------------|--------------------|
| Joystick Y     | A0                 |
| Switch         | A2                 |
| Motor PWM      | D9                 |
| Motor DIR      | D8                 |
| Flex Sensor    | A4                 |
| Battery Voltage| A1                 |
| LED RED  | A3                 |
| LED GREEN | A5                |
| LED BLUE  | A6                |

If you don't have the same wiring as above, you can change the pin definitions in the `config.h` file.

### 3. ⚙️ platformio.ini Example

```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
upload_port = COM5

build_flags = -D SERIAL_SPEED=115200
```

### 4. 🎮 Changing Control Modes

The default mode is set in the `constants.h` file.

It is initially set to use the joystick only as the control.
```cpp
const ControlMode DEFAULT_CONTROL = JOYSTICK;
```

To switch to the flex sensor control mode, change the line to (you can comment the previous line and uncomment the next one):
```cpp
const ControlMode DEFAULT_CONTROL = FLEXSENSOR;
```
Then the flex sensor will be used by default unless the user press the switch to use the joystick control instead.

### 5. ⚙️ Changing Constants

You can change the constants in the `constants.h` file to adjust the behavior of the control system, such as:

* `MOTOR_RAMP_TIME`: Time in milliseconds between PWM ramp steps.
* `CONSTANT_SPEED`: Maximum PWM value (0–255) for motor power.
* `STEP_SIZE_UP` / `STEP_SIZE_DOWN`: How fast the motor accelerates or decelerates.
* `BATTERY_THRESHOLD_MEDIUM`: Voltage below which the battery is considered at medium level.
* `BATTERY_THRESHOLD_EMPTY`: Voltage below which the battery is considered low.
* `JOYSTICK_REST_POSITION`: X-axis value considered neutral.
* `JOYSTICK_UP_THRESHOLD`: Value above which joystick signals “UP”.
* `JOYSTICK_DOWN_THRESHOLD`: Value below which joystick signals “DOWN”.
* `FLEX_SENSOR_THRESHOLD`: Threshold value for the flex sensor to trigger motor movement.
* `FLEXSENSOR_THRESHOLD_UP`: Flex angle threshold to move arm up.
* `FLEXSENSOR_THRESHOLD_DOWN`: Flex angle threshold to move arm down.
* `LED_DISPLAY`: Whether or not to enable LED indicator output (1 = on, 0 = off).

You also need to configure the flexsensor constants in the `config.h` file, such as:
* `FLEXSENSOR_VCC`: The voltage supplied to the flex sensor (usually 5V).
* `FLEXSENSOR_RDIV`: The resistance of the pull-down resistor (usually 47kΩ).
* `FLEXSENSOR_FLATR`: The resistance of the flex sensor when it is flat (set to 25kΩ).
* `FLEXSENSOR_BENTR`: The resistance of the flex sensor when it is bent (set to 10kΩ).


### 4. 🚀 Build and Upload

1. Open the project in VS Code with PlatformIO installed.
2. Connect your Arduino board.
3. Open the PlatformIO terminal.
4. Build the project with the command:
   ```bash
   pio run
   ```
5. Upload the firmware to the board with the command:
   ```bash  
    pio run --target upload
    ```
6. Open the Serial Monitor to see debug output:
    ```bash
     pio device monitor
     ```



## 🏗️ Add your own Control Mode

To add a new control mode, follow these steps:
1. **Create a new header file** in the `include/` directory, e.g., `newcontrol.h`.
2. **Define a new control mode** in the `ControlMode` enum in `types.h`:
   ```cpp
   enum ControlMode {
       JOYSTICK,
       FLEXSENSOR,
       NEWCONTROL // Add your new control mode here
   };
   ```
3. **Set the new wiring** in `config.h`.
4. **Define the constants you need** in `constants.h`.
5. **Implement the control logic** in a corresponding `newcontrol.cpp` file in the `src/` directory:
    - Implement a setup function to initialize the new control mode.
    - Implement a `newcontrolBasedStateChange` function to handle state changes (`UP`, `DOWN`, `REST`) based on the new control mode. It needs to have this definition: `void newcontrolBasedStateChange(State *prevState, State *currentState, bool verbose=false);`, modifying the previous and current state based on the new sensor input, no other arguments are allowed. See `flexsensor.cpp` for an example.
    - You can add additional functions as needed for your control mode logic, as reading inputs functions for example.
6. **Update the `control.cpp` file** to handle your new control mode:
    ```cpp
    ControlFunc controlTable[] = {
        joystickBasedStateChange,    // JOYSTICK
        flexsensorBasedStateChange,   // FLEXSENSOR
        newcontrolBasedStateChange    // NEWCONTROL
    };
    ```
    Note that the order of the functions in the `controlTable` array must match the order of the `ControlMode` enum values defined in `types.h`.
7. **Modify the `main.cpp` file** to include your new control mode setup:
   - Call the setup function for your new control mode in the `setup()` function.
8. **Switch to your new control mode** in the `constants.h` file:
    ```cpp
    const ControlMode DEFAULT_CONTROL = NEWCONTROL;
    ```



## 📚 References

- [Arduino Documentation](https://docs.arduino.cc/)
- [PlatformIO Documentation](https://docs.platformio.org/en/latest/)
- [Flex Sensor Guide](https://lastminuteengineers.com/flex-sensor-arduino-tutorial/)


