# Pierre Bot

**Version:** 1.0  
**Date:** February 2026  
**Status:** Phase 1 - Planning/Requirements

---

## 1. Project Overview

### 1.1 Project Summary

Pierre is a expressive ESP32-based small scale robot, to be a desk "friend". it features a copper wire frame that serves also as a grounding path. Pierre has emotinal awareness sensitive to the weather, time of day, and lighting of his envirment. they'll perform autonomous navigation along with being touch sensitive to interact with the enviroment during the long office hours.

### 1.2 Project Goals

- Create a functional desk robot demonstrating embedded systems integration.
- Implement vector driven dynamic behaviour to showcase a range of emotions.
- Aim for professinal representation of project planning and execution
- Develop a unique mechanical design using exposed copper frame construction.

### 1.3 Design Philosophy

Pierre is designed as a silent, non intrusive desk companion. All expression occurs through screen animations and movement. with a exposed copper frame to show  artistic expression. Pierre is ment to bring electronic engineering into a world of expression and emotion.  

---

## 3. Functional Requirements

### 3.1 Sensing & Perception

#### FR-1: Time of Flight (ToF) Sensor

**Priority:** Manditory
**Description:** Front or angled facing ToF sensor to aid in navigation, and obstical avoidance.
**Acceptance Criteria:**

- Detect objects within 0-200mm range
- Update rate: minimum 5Hz
- Integration with navigation algorithms

#### FR-2: IR Proximity Sensor

**Priority:**  Manditory
**Description:** Underneath-mounted infrared sensor for edge detection  
**Acceptance Criteria:**

- Detect table edge before avoiding falls.
- Trigger emergency stop and obstical avoidance
- Response time < 100ms

#### FR-3: Capacitive Touch Detection

**Priority:** Manditory  
**Description:** capacitive touch areas for user interaction  
**Acceptance Criteria:**

- Minimum 1 touch zones (Top, and head or chin!)
- Distinguish between tap, hold, and stroke patterns
- Touch response time < 50ms

#### FR-4: Angle sensor

**Priority:** Ideal
**Description:** Detect wether it has fallen over
**Acceptance Criteria:**

- heavily effects emotions tempirary to display discomfort
- Trigger corective movment if falling

#### FR-5: Desk Vibration Detection

**Priority:** Ideal
**Description:** Detect abrupt vibration from desk effecting short term emotion.
**Acceptance Criteria:**

- Sense moderate desk vibrations
- Filter out ambient/environmental noise
- Trigger curiosity or startled behaviors

#### FR-6: Environmental Sensing

**Priority:** Nice to Have  
**Description:** Light level and temperature.  
**Acceptance Criteria:**

- Provide context for mood adjustments
- Update interval, 1-5 minutes
- Influence short term behavior

### 3.2 Expression & Display

#### FR-7: Emotional Display System

**Priority:** Manditory
**Description:** OLED screen displaying varity of emotions
**Acceptance Criteria:**

- Minimum 5 distinct emotional states (happy, neutral, annoyed, curious, sleepy)
- Smooth transitions between expressions
- Frame rate minimum 10fps for animations
- There are OLED emotion libraries present that can be utalised

#### FR-8: Weather-Integrated Expressions

**Priority:** Manditory
**Description:** Weather effects Emotion
**Acceptance Criteria:**

- Elements of the facial features could represent weather
- Weather data fetched via WiFi
- If not connected to wifi small symbol will appear but and the weather integration will be ignored.

#### FR-9: LED Indicators

**Priority:** Nice to have  
**Description:** Subtle LED status indication inside
**Acceptance Criteria:**

- Low brightness for desk environment
- Synchronized with mood state
- Optional disable for minimal distraction
- synced with time of day or sunset metrics

#### FR-10: Time-Dependent Moods

**Priority:** Must-Have  
**Description:** Mood varies based on time of day  
**Acceptance Criteria:**

- Sleepy behavior during late night/early morning hours
- Active/energetic during mid-day
- User-configurable "work hours" or schedule
- Syncs time via NTP when WiFi available

#### FR-12: Short-Term Mood Shifts

**Priority:** Manditory
**Description:** Temporary mood changes based on recent interactions  
**Acceptance Criteria:**

- Becomes annoyed if poked or disturbed repeatedly
- Becomes happy with gentle, friendly interactions
- Mood decay back to baseline over 5-15 minutes
- Multiple interaction events stack effects

### 3.4 Mobility & Navigation

#### FR-14: Autonomous Roaming

**Priority:** Manditory
**Description:** Patrol desk area independently, avoiding obstacles and edges  
**Acceptance Criteria:**

- Move forward, backward, turn left/right
- Stop before colliding with obstacles (ToF)
- Stop before falling off edges (IR proximity)
- Random/curiosity-driven movement patterns
- Interact with objects breifly(ramming or pushing)

#### FR-15: Movement as Expression

**Priority:** Manditory
**Description:** Movement patterns express emotional state  
**Acceptance Criteria:**

- Excited breif shuffles back and forth
- Retreat when annoyed or scared
- Slow, deliberate movement when tired
-

#### FR-16: Creative Wheel Design

**Priority:** ideal
**Description:** Distinctive wheel  
**Acceptance Criteria:**

- Functional on smooth desk surfaces
- Aesthetically aligned with exposed frame design
- Sylish choice but still practical

---

## 4. Non-Functional Requirements

### 4.1 Performance

#### NFR-1: Response Time

- Touch input response < 1000ms
- Sensor samplin minimum 5 Hz
- Display update minimum 10 fps
- Edge detection emergency stop: < 100ms

#### NFR-2: Reliability

- Graceful handling of WiFi disconnection
- No crashes during normal operation
- Safe failure modes (stop moving if sensor fails)
- stop moving if fallen over
- handels overnight charging
- Powers off before battery dies, to minimise currutption.

#### NFR-3: Battery Life

- Target: 3 - 8 hours active use
- Overnight charging acceptable
- Low battery warning behavior (sleepy, reduced activity)
- USB charging via dedicated circuit or ESP32

### 4.2 Usability

#### NFR-4: Minimal Setup

- Power on and operational within 30 seconds
- WiFi credentials configurable (captive portal or hardcoded)
- No external app required for basic operation

#### NFR-5: Desk-Friendly Operation

- Silent (no speakers or buzzers)
- Non-distracting and Non-intrusive (subtle movements and displays)
- Safe (won't fall off desk or damage items)

### 4.3 Maintainability

#### NFR-6: Modular Software Design

- Separate modules for sensors, display, mood engine, navigation
- Mathmatical vector driven moods
- Clear state machine implementation
- Well-commented code
- Version control via GitHub

#### NFR-7: Accessible Hardware

- Standard charging connectors
- Exposed motor spindle for clearning of debris
- Exposed dummy wheel for clearing of debris

### 4.4 Aesthetics

#### NFR-8: Exposed Copper Frame

- 1mm copper wire frame (TBD, thickness subject to structural testing)
- Frame serves as electrical ground(TBC, subject to interfierance testing)
- Skeletal aesthetic showing internal components
- Structurally sound for weight of components

#### NFR-9: Unique Character Elements

- Optional decorative elements (flowers, accessories)
- Personality-driven design choices

#### NFR-10: Single hand to hold small decor

- Small claw to grip a accessory like a flower or paper clip
- Stern and flexable to maintain grip

---

## 5. Feature Prioritization

### Must-Have (Version 1.0)

- Roaming capability with edge/obstacle detection
- Touch memory system (recognize patterns)
- Weather based mood system
- Time based mood system
- Emotional display on OLED
- Basic personality engine

### ideal/Nice to have (Version 1.0 or future)

- Desk vibration detection
- LED indicators in frame
- Social battery system
- Environmental sensors (light, temp)
- Advanced movement patterns
- Creative wheel design

### Future Enhancements

- Multiple personality profiles
- Mobile app integration
- Advanced AI/ML for pattern recognition
- Voice command support
- Multi-robot interaction
- Noise generation

---

## 6. Assumptions & Dependencies

### 6.1 Assumptions

- ESP32 WiFi reliably available for weather/time sync
- Desk surface is flat and stable
- Operating temperature: 10-30°C (typical indoor)
- User interactions are gentle (no aggressive handling)
- will not substain any harsh impacts
- OLED Emotion libraries have been debugged

### 6.2 Dependencies

- Weather API availability (OpenWeatherMap, WeatherAPI, or similar)
- NTP server for time synchronization
- Component availability within budget
- PlatformIO development environment
- OLED Emotion libraries

### 6.3 Unknowns / TBD

- **Motor selection:** Type, size, and power requirements
- **Exact frame dimensions:** Subject to component layout
- **Wheel/locomotion mechanism:** Design approach
- **Battery type and capacity:** LiPo vs 18650 vs other
- **Total budget:** Component costs to be finalized in BOM
