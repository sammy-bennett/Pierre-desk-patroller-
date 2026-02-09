# System Architecture Document

## Pierre the Planet Patroller

**Version:** 1.0  
**Date:** February 2026  
**Status:** Phase 1 - Planning & Architecture

---

## 1. Architecture Overview

Pierre is built on a modular architecture with clear separation between sensing, processing, actuation, and user interface layers. The ESP32 serves as the central processing unit, coordinating all subsystems through a state-driven personality engine.

### 1.1 Design Principles

- **Modularity:** Each subsystem operates independently with well-defined interfaces
- **Graceful Degradation:** System continues functioning if non critical components fail
- **Event-Driven:** Reactive architecture responding to sensor inputs sensor inturrputs and timers
- **Stateful Behavior:** Mood engine maintains persistent state affecting all behaviors

---

## 2. System Block Diagram

``` bash
┌─────────────────────────────────────────────────────────────────┐
│                         PIERRE SYSTEM                            │
│                                                                  │
│  ┌──────────────┐         ┌─────────────┐      ┌─────────────┐ │
│  │   SENSORS    │────────▶│   ESP32    │─────▶│  ACTUATORS  │ │
│  │              │         │     (MCU)   │      │             │ │
│  │ • ToF        │         │             │      │ • Motors    │ │
│  │ • IR Prox    │         │ • WiFi      │      │ • OLED      │ │
│  │ • Capacitive │         │ • Flash     │      │ • (LEDs)    │ │
│  │ • (IMU)      │         │ • RTOS      │      │             │ │
│  └──────────────┘         └─────────────┘      └─────────────┘ │
│         │                        │                     │        │
│         │                        ▼                     │        │
│         │              ┌──────────────────┐            │        │
│         └─────────────▶│  PERSONALITY     │◀───────────┘        │
│                        │     ENGINE       │                     │
│                        │                  │                     │
│                        │ • Mood State     │                     │
│                        │ • Touch Memory   │                     │
│                        │ • Behavior Logic │                     │
│                        └──────────────────┘                     │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │               EXTERNAL SERVICES (via WiFi)                │  │
│  │  • Weather API  • NTP Time Server  • (Future: OTA)       │  │
│  └──────────────────────────────────────────────────────────┘  │
│                                                                  │
│  ┌──────────────────────────────────────────────────────────┐  │
│  │                    POWER SYSTEM                           │  │
│  │  Battery ──▶ Regulator ──▶ ESP32 + Peripherals           │  │
│  │                  ▲                                         │  │
│  │            USB Charging                                    │  │
│  └──────────────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 3. Hardware Architecture

### 3.1 Core Processing Unit

#### ESP32 Development Board

- **Processor:** Dual-core Xtensa LX6, 240MHz
- **Memory:** 520KB SRAM, 4MB Flash (typical)
- **Connectivity:** WiFi 802.11 b/g/n, Bluetooth (unused in v1.0)
- **GPIO:** Sufficient pins for sensors, motors, display as some are non input or non output
- **Power:** 3.3V logic, ~80-260mA active (varies with WiFi interation)

### 3.2 Sensor Subsystem

#### Time of Flight (ToF) Sensor

- **Suggested Model:** VL53L0X or VL53L1X
- **Interface:** I2C
- **Range:** 30-1000mm (VL53L0X), up to 4000mm (VL53L1X)
- **Mounting:** Front facing or downward angled
- **Purpose:** Obstacle detection, curiosity triggers

#### IR Proximity Sensor

- **Suggested Model:** TCRT5000 or similar reflective sensor
- **Interface:** Analog or digital output
- **Range:** 1 - 25mm typical
- **Mounting:** Underneath chassis, facing down
- **Purpose:** Edge detection (edge avoidance)

#### Capacitive Touch Sensors

- **Implementation Options:**
  - ESP32 built in touch pins (T0 T9)
  - External TTP223 modules
  - Copper frame segments as touch electrodes
- **Zones:** Minimum 2 (Top and back)
- **Interface:** GPIO (ESP32 native)
- **Purpose:** User interaction, pattern recognition

#### Optional: IMU (Accelerometer/Gyroscope)

- **Suggested Model:** MPU6050
- **Interface:** I2C
- **Purpose:** Desk vibration detection, tilt sensing
- **Status:** ideal feature

### 3.3 Display Subsystem

#### 0.96" OLED Display (ELEGOO)

- **Resolution:** 128x64 pixels
- **Driver:** SSD1306 (typical for this size)
- **Interface:** I2C (SCL, SDA)
- **Power:** ~20mA active, < 1mA in low power mode
- **Colors:** Monochrome (white/blue on black)
- **Refresh Rate:** Target 10-30fps for animations

### 3.4 Actuation Subsystem

#### Motor System (TBD - options)

- **Option A: DC Gear Motors**
  - N20 micro gear motors (3V-6V)
  - Motor driver: DRV8833 or L298N
  - Simple forward, reverse and speed control
  
- **Option B: Servo Motors**
  - SG90 micro servos modified for continuous rotation
  - Direct PWM control from ESP32
  - Simpler wiring, less current

- **Wheels:** large cogs (TBC)
- **Configuration:** individual motors (differntial would be too large)

#### Optional: LED Indicators

- **Type:** WS2812B addressable RGB or simple single color LEDs
- **Location:** Embedded in copper frame
- **Interface:** Single GPIO pin (WS2812B) or multiple GPIO (standard LEDs)
- **Purpose:** status indication, ambience

### 3.5 Power Architecture

``` bash
USB 5V Input ──┬──▶ TP4056 Charging Module ──▶ Battery (LiPo/18650)
               │                                      │
               └──────────────────────────────────────┴──▶ Regulator ──▶ 3.3V/5V Rails
                                                              │
                                                              ├──▶ ESP32 (3.3V)
                                                              ├──▶ Sensors (3.3V)
                                                              ├──▶ OLED (3.3V)
                                                              └──▶ Motors (5V or direct battery)
```

**Battery Options (TBD):**

- **18650 Li-ion:** 2500, 3500mAh, 3.7V nominal, robust, easy to source
- **LiPo:** 1000 - 2000mAh, lighter, various form factors
- **Regulator:** LM1117 3.3 or buck converter (higher efficiency)

**Power Consumption Estimate (Preliminary):**

| Component | Typical | Peak |
| --------- | ------- | ---- |
| ESP32 (WiFi on) | 160mA | 260mA |
| OLED | 20mA | 20mA |
| ToF Sensor | 20mA | 40mA |
| IR Proximity | 5mA | 5mA |
| Capacitive Touch | <1mA | <1mA |
| Motors (2x) | 100mA | 400mA |
| **Total** | **~305mA** | **~725mA** |

**Battery Life Estimate (Conservative):**

- 2000mAh battery ÷ 400mA average = ~ 5 Hr
- Allows for periodic WiFi use, intermittent movement

---

## 4. Software Architecture

### 4.1 Software Stack

``` bash
┌─────────────────────────────────────────┐
│         Application Layer               │
│  • Main Loop / Behavior Coordinator     │
└─────────────────────────────────────────┘
                   │
┌─────────────────────────────────────────┐
│       Personality Engine                │
│  • Mood State Machine                   │
│  • Touch Pattern Recognizer             │
│  • Behavior Arbiter                     │
└─────────────────────────────────────────┘
                   │
┌─────────────────────────────────────────┐
│        Hardware Abstraction             │
│  • Sensor Manager                       │
│  • Display Driver                       │
│  • Motor Controller                     │
│  • WiFi Manager                         │
└─────────────────────────────────────────┘
                   │
┌─────────────────────────────────────────┐
│      ESP-IDF / Arduino Framework        │
│  • FreeRTOS                             │
│  • WiFi Stack                           │
│  • I2C / GPIO / PWM Drivers             │
└─────────────────────────────────────────┘
```

### 4.2 Key Software Modules

#### Sensor Manager

- **Responsibilities:**
  - Poll sensors at appropriate rates
  - Filter/debounce sensor data
  - Provide clean data to application layer
  - Raise inturrupt on edge detection
- **Interfaces:**
  - `uint16_t getToFDistance()`
  - `bool isEdgeDetected()`
  - `TouchEvent getTouchEvent()`

#### Mood Engine

- **Responsibilities:**
  - Maintain current mood state
  - Process time, weather, and interaction inputs
  - Calculate mood transitions
  - Store/retrieve touch patterns from flash
- **State Variables:**
  - Base mood (weather + time influenced)
  - Short-term mood modifier (recent interactions)
  - Energy level (social battery)
  - Recognized touch pattern ID
- **Interfaces:**
  - `MoodState getCurrentMood()`
  - `void processInteraction(TouchEvent event)`
  - `void updateWeather(WeatherData data)`

#### Display Manager

- **Responsibilities:**
  - Render facial expressions based on mood
  - Smooth animation transitions
  - Integrate weather symbols into face
- **Interfaces:**
  - `void showExpression(MoodState mood)`
  - `void updateWeatherSymbol(WeatherType type)`

#### Navigation Controller

- **Responsibilities:**
  - Execute movement commands
  - Emergency stop on edge/obstacle detection
  - Smooth motor control
- **Interfaces:**
  - `void move(Direction dir, uint8_t speed)`
  - `void stop()`
  - `bool isSafeToMove()`

#### WiFi Manager

- **Responsibilities:**
  - Connect to WiFi on startup
  - Fetch weather data periodically
  - Sync time via NTP
  - Handle connection loss gracefully
- **Interfaces:**
  - `WeatherData fetchWeather()`
  - `DateTime getCurrentTime()`

### 4.3 State Machine: Mood System

``` bash
                    ┌──────────────┐
                    │   NEUTRAL    │
                    │  (baseline)  │
                    └──────┬───────┘
                           │
         ┌─────────────────┼─────────────────┐
         │                 │                 │
         ▼                 ▼                 ▼
    ┌─────────┐      ┌──────────┐      ┌─────────┐
    │  HAPPY  │      │  CURIOUS │      │ ANNOYED │
    └─────────┘      └──────────┘      └─────────┘
         │                 │                 │
         └─────────────────┼─────────────────┘
                           │
                 (decay back to baseline)
                           │
                    ┌──────▼───────┐
                    │    SLEEPY    │
                    │ (time-based) │
                    └──────────────┘

Modifiers:
• Weather: Shifts baseline (rain → slightly gloomy)
• Time: Late night → sleepy override
• Interactions: Short-term shifts (+happy, +annoyed, etc.)
• Social Battery: Low energy → withdrawn, less responsive
```

### 4.4 Touch Pattern Recognition Algorithm (Preliminary)

``` bash
1. Capture touch sequence:
   - Zone touched (head, side, back)
   - Duration (tap <200ms, hold >200ms)
   - Interval between touches

2. Create signature:
   - [Zone1, Duration1, Interval1, Zone2, Duration2, ...]
   - Normalize timing to account for variation

3. Compare to stored patterns:
   - Calculate similarity score (pattern matching)
   - Threshold: >80% match = recognized

4. Store new pattern if unknown:
   - Limit: 3-5 stored patterns
   - Overwrite least-used if full
```

---

## 5. Data Flow Diagrams

### 5.1 Touch Interaction Flow

``` bash
User Touch
    │
    ▼
Capacitive Sensor ──▶ Sensor Manager ──▶ Debounce/Filter
    │
    ▼
Touch Event (zone, duration)
    │
    ▼
Mood Engine ──▶ Pattern Recognizer ──▶ Compare to Stored Patterns
    │                                           │
    ▼                                           ▼
Update Short-Term Mood                   Recognized? Yes/No
    │                                           │
    ▼                                           ▼
Display Manager ◀───────────────────────── Response Behavior
    │
    ▼
Show Expression (happy, annoyed, etc.)
```

### 5.2 Weather Update Flow

``` bash
Timer Trigger (every 30 min)
    │
    ▼
WiFi Manager ──▶ HTTP Request to Weather API
    │
    ▼
Parse JSON Response ──▶ Extract: Condition, Temp, Icon
    │
    ▼
Mood Engine ──▶ Update Base Mood (sunny → cheerful)
    │
    ▼
Display Manager ──▶ Update Weather Symbol in Face
```

### 5.3 Navigation Decision Flow

``` bash
Main Loop (10Hz)
    │
    ▼
Sensor Manager ──▶ Read ToF Distance, IR Edge Sensor
    │
    ▼
Navigation Controller ──▶ Evaluate Safety
    │                          │
    ▼                          ▼
Edge Detected?           Obstacle Close?
    │                          │
    Yes                        Yes
    │                          │
    ▼                          ▼
EMERGENCY STOP           Turn / Retreat
    │                          │
    └──────────────┬───────────┘
                   ▼
              Safe to Continue?
                   │
                   Yes
                   ▼
         Execute Movement (forward, turn)
                   │
                   ▼
         Mood-Influenced Speed/Pattern
         (curious → explore, tired → slow)
```

---

## 6. Communication Interfaces

### 6.1 I2C Bus

- **Speed:** 100kHz (standard) or 400kHz (fast mode)
- **Devices:**
  - OLED Display (address: 0x3C or 0x3D typical)
  - ToF Sensor (address: 0x29 typical, configurable)
  - Optional IMU (address: 0x68 typical)
- **Pins:** ESP32 GPIO21 (SDA), GPIO22 (SCL) - typical defaults

### 6.2 GPIO Pins

- **Capacitive Touch:** ESP32 touch pins T0-T9 (various GPIOs)
- **IR Proximity:** Analog input (ADC pin) or digital GPIO
- **Motor PWM:** 2-4 GPIO pins (depending on driver)
- **Optional LEDs:** 1+ GPIO pins

### 6.3 WiFi

- **Protocol:** HTTP/HTTPS for weather API
- **Security:** WPA2-PSK
- **Services:**
  - Weather API (OpenWeatherMap, WeatherAPI.com, etc.)
  - NTP time sync (pool.ntp.org)

### 6.4 Storage

- **Flash Memory:** ESP32 onboard flash
- **Data Stored:**
  - WiFi credentials
  - Touch pattern database (3-5 patterns)
  - Configuration settings
  - Weather cache (for offline fallback)
- **File System:** SPIFFS or LittleFS

---

## 7. Physical Architecture

### 7.1 Copper Frame Structure

``` bash
       ┌─── Head (OLED mount) ───┐
       │                         │
       │    ┌───────────┐        │
       │    │   OLED    │        │  ← Capacitive Touch Zones
       │    └───────────┘        │     on frame segments
       │                         │
       └────┬─── Body ───┬───────┘
            │            │
         ┌──┴──┐      ┌──┴──┐
         │Motor│      │Motor│
         └─┬─┬─┘      └─┬─┬─┘
           │ │          │ │
          Wheel        Wheel

Frame Material: ~1mm copper wire (TBD)
Function: Structure + Electrical Ground
```

### 7.2 Component Mounting Strategy

- **ESP32:** Central body location, easily accessible
- **OLED:** Front-facing, secure mount to frame
- **Battery:** Low center of gravity, removable
- **Sensors:** ToF front, IR underside, touch integrated into frame
- **Motors:** Rear or side-mounted, mechanically isolated from frame vibration

---

## 8. Design Decisions & Rationale

| Decision | Rationale |
| -------- | --------- |
| **ESP32 platform** | WiFi capability, sufficient GPIO, existing hardware, strong community |
| **I2C for sensors** | Minimal wiring, multiple devices on 2 pins, well-supported libraries |
| **No audio output** | Desk-friendly, non-distracting, reduces power consumption |
| **Monochrome OLED** | Low power, high contrast, sufficient for geometric expressions |
| **Copper wire frame** | Aesthetic uniqueness, functional grounding, structural simplicity |
| **State machine mood** | Predictable behavior, easy debugging, extendable personality |
| **Offline fallback** | Graceful degradation if WiFi unavailable, autonomous operation |

---

## 9. Interfaces to Other Phase 1 Documents

- **Requirements Specification:** All functional/non-functional requirements mapped to architecture components
- **Bill of Materials:** All components listed in hardware architecture section
- **Pin Assignments:** GPIO allocations derived from sensor/actuator interfaces
- **Power Budget:** Power consumption estimates feed battery sizing decisions

---

## 10. Future Architecture Considerations

### Potential Enhancements (Post-v1.0)

- **OTA Updates:** Firmware updates over WiFi
- **Mobile App:** Bluetooth control, configuration, mood history
- **Multi-Robot Communication:** Pierre-to-Pierre interaction via WiFi/BLE
- **Advanced AI:** TinyML on-device pattern recognition
- **Voice Commands:** Microphone + speech recognition (conflicts with silent operation goal)
- **Expandable Sensors:** Modular sensor mounting for experimentation

---

## 11. Document History

| Version | Date | Author | Changes |
| ------- | ---- | ------ | ------- |
| 1.0 | Feb 2026 | Project Lead | Initial architecture document |

---

**Next Steps:**

- Finalize component selection (motors, battery, sensors)
- Create detailed pin assignment table
- Develop power budget spreadsheet
- Begin hardware prototyping (breadboard validation)
