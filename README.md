# Minisumo_codigo  
### Embedded Firmware for Mini Sumo Robot  
**Arduino Nano | C++ | Sensors | Motor Control | State Logic**

---

## 📍 Overview

**Minisumo_codigo** contains the **embedded firmware** developed for my **Mini Sumo autonomous robot** (“Mini Mini Rumania”).  
The project focuses on **real-time sensor processing**, **motor and actuator control**, and **competition-oriented decision logic**, running on an **Arduino Nano** using **C++ (Arduino framework)**.

This repository is part of my **professional robotics portfolio** and demonstrates practical embedded programming applied to competitive robotics.

---

## 🎯 Project Objectives

- Implement reliable **real-time control logic** for Mini Sumo
- Integrate multiple sensors and actuators on a constrained MCU
- Apply structured decision logic for autonomous behavior
- Demonstrate clean, functional embedded C++ code

---

## ⚙️ System Description

The robot integrates the following hardware:

- **4 proximity sensors** (opponent detection)
- **2 floor sensors** (edge / dohyo detection)
- **2 DC motors** (locomotion)
- **2 servomotors** (auxiliary mechanisms)
- **1 control button**
- **1 competition starter (start module)**

The firmware continuously evaluates sensor data to decide between **search, attack, and edge-avoidance behaviors**, ensuring autonomous operation during competition.

---

## 🛠️ Technologies & Tools

- **Microcontroller:** Arduino Nano (ATmega328P)
- **Language:** C++ (Arduino framework)
- **IDE:** Arduino IDE
- **Control Methods:**  
  - Digital & analog sensor inputs  
  - PWM motor control  
  - Servo control via Arduino Servo library

---

## 🧠 Control Logic (High Level)

The firmware architecture is designed around:

- Continuous sensor polling
- Conditional decision making
- Priority handling for edge detection
- Deterministic motor and servo commands

This structure allows predictable behavior, fast reaction times, and easy strategy tuning.

---
---

## ✅ Project Status

- ✔ Functional firmware for Mini Sumo competition
- ✔ Multi-sensor integration
- ✔ Motor and servo control implemented
- 🔄 Ongoing refinements and optimizations

---

## 🔮 Planned Improvements

- Pinout table documentation
- Explicit state-machine diagram (search / attack / evade)
- Sensor calibration routines
- Strategy selection via button or configuration
- Serial debugging and performance logging

---

## 🧩 Engineering Focus

- Robust behavior under competition constraints
- Simple and maintainable logic
- Clear separation between sensing, decision and actuation
- Code written for **practical deployment**, not simulation only

---

## 👤 Author

**Areivan**  
Industrial Robotics Engineering Student  
Industrial Maintenance Technician  

- Embedded systems and robotics enthusiast  
- Focused on practical, real-world engineering projects  

🔗 GitHub: https://github.com/AREIVAN

---

## 📜 License

This project is intended for **educational, experimental and portfolio purposes**.  
Reuse is allowed with proper attribution to the author.

