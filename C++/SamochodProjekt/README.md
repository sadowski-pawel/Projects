# 🚗 Vehicle Simulation (C++ / SFML)

A simple real-time vehicle physics simulation written in C++ using SFML.  
The project models car motion using Newtonian physics and numerical integration.

---

## 📥 Installation

1. Download the `setup.exe` file from the repository (or Releases section)
2. Run `setup.exe`
3. Follow the installation steps
4. After installation, launch the application from the desktop shortcut or installation folder

---

## ▶️ Running the program

- Start the application by double-clicking the installed shortcut or the `.exe` file
- No additional setup is required


## 📁 Project structure
Source.cpp - main program loop
Pole_tekstowe.h - input field handling (UI form)
Interfejs_symulacji.h - simulation window + graph rendering
ZaladowaniePlikow.cpp - textures, sounds, asset loading
Samochod.h - physics model of the vehicle

---

## ⚙️ Features

- real-time physics simulation of a car
- force-based motion model (engine, braking, drag, friction)
- parameter input system (UI form)
- real-time graph visualization
- SFML-based graphics and sound support
- restartable simulation loop

---

## 🧠 Physics model

The simulation is based on Newton’s second law:

\[
F = m \cdot a
\]

### Acceleration:

\[
a = \frac{F_{net}}{m}
\]

### Net force:

\[
F_{net} = F_{engine} - F_{brake} - F_{rolling} - F_{air}
\]

---

## 📊 Numerical integration

The simulation uses Euler integration:


v = v + a * dt
s = s + v * dt


This approximates derivatives:
- velocity = derivative of position
- acceleration = derivative of velocity

---

## 🎮 Controls

- ↑ Arrow Up – increase throttle
- ↓ Arrow Down – decrease throttle
- Space – brake
- ESC – exit simulation
- 0 – restart input system

---

## 🧱 Technologies

- C++
- SFML (graphics, audio, window system)

---

---

## 👨‍💻 Author

Paweł Sadowsk