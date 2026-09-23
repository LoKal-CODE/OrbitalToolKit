```
   ____       __    _ __        ________            ____ __ _ __ 
  / __ \_____/ /_  (_) /_____ _/ /_  __/___  ____  / / //_/(_) /_
 / / / / ___/ __ \/ / __/ __ `/ / / / / __ \/ __ \/ / ,<  / / __/
/ /_/ / /  / /_/ / / /_/ /_/ / / / / / /_/ / /_/ / / /| |/ / /_  
\____/_/  /_.___/_/\__/\__,_/_/ /_/  \____/\____/_/_/ |_/_/\__/  
```

# OrbitalToolKit
 
A command-line C++ tool for calculating 2-burn Hohmann transfer orbits. Given a spacecraft's current orbit (read from a file) and a desired target orbital radius, it computes the full transfer maneuver: burn delta-Vs, total delta-V budget, and transfer time.
 
Built as a project for CS1 (Introduction to Computer Science) at the University of Colorado Boulder, applying orbital mechanics concepts alongside foundational C++ and object-oriented programming practices.
 
## Features
 
- Reads spacecraft and orbital data from a user-specified `.csv` or `.txt` file, with a user-defined delimiter
- Computes, using the vis-viva equation and Hohmann transfer relations:
  - Initial and target circular orbital velocities
  - Transfer orbit periapsis and apoapsis velocities
  - Delta-V required for each burn, and the total delta-V budget
  - Transfer time (seconds, minutes, and hours)
- Outputs a formatted summary of all computed values
Currently assumes transfers around Earth; the `Planet` class is structured so other central bodies can be added easily.
 
## Project Structure
 
```
OrbitalToolKit/
├── include/
│   ├── orbital.h      # Function declarations for orbital mechanics calculations
│   └── planet.h        # Planet class declaration
├── src/
│   ├── main.cpp         # Program entry point, user I/O, and file parsing
│   ├── orbital.cpp     # Orbital mechanics formula implementations
│   └── planet.cpp       # Planet class implementation
└── README.md
```
 
## Building
 
Requires a C++ compiler supporting C++11 or later (e.g., `g++`).
 
```bash
g++ -o orbitaltoolkit src/main.cpp src/orbital.cpp src/planet.cpp -Iinclude
```
 
## Usage
 
```bash
./orbitaltoolkit
```
 
You'll be prompted to:
1. Choose an operation (currently: 2-Burn Hohmann Transfer, or Exit)
2. Enter the path to your data file
3. Enter the delimiter used in that file (e.g., `,`)
4. Enter your desired target orbital radius, in km, measured from Earth's center
### Input File Format
 
Each line of the input file should contain six fields, separated by your chosen delimiter, in this order:
 
```
spacecraftName,mass,orbitalRadius,orbitingBody,eccentricity,inclination
```
 
Example (`spacecraft.csv`):
 
```
Voyager1,825,6678,Earth,0.0,28.5
```
 
- `mass` — spacecraft mass (kg)
- `orbitalRadius` — current orbital radius (km, measured from the central body's center)
- `orbitingBody` — name of the body currently being orbited
- `eccentricity` / `inclination` — current orbit's eccentricity and inclination (degrees)
### Example Output
 
```
========== Hohmann Transfer Results for Voyager1 ==========
Spacecraft mass           : 825.0000 kg
Orbiting body             : Earth
Initial orbit eccentricity: 0.0000
Initial orbit inclination : 28.5000 deg
 
--- Orbital Radii ---
Initial orbital radius    : 6678.0000 km  (6678000.0000 m)
Target orbital radius     : 42164.0000 km  (42164000.0000 m)
 
--- Delta-V Budget ---
Burn 1 (departure) dV     : 2426.1500 m/s
Burn 2 (insertion) dV     : 1477.3300 m/s
Total delta-V             : 3903.4800 m/s
 
--- Transfer Time ---
Transfer time             : 18919.2000 s
                          : 315.3200 min
                          : 5.2554 hr
=====================================================
```
 
*(Sample values above are illustrative — actual output will vary based on your input data.)*
 
## What I Learned
 
- Structuring a multi-file C++ project with separate header and source files
- Applying object-oriented design to encapsulate physical/orbital properties in a `Planet` class
- Parsing user-supplied command-line input and delimited data files in C++
- Implementing core orbital mechanics formulas (vis-viva equation, Hohmann transfer relations) in code

# Credit
- ASCII Text Generator for the project header art- ASCII TEXT (https://ascii.co.uk/text)