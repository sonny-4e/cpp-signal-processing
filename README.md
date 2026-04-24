# C++ Signal Processing & Data Transmission

This repository contains my laboratory coursework for the "Data Transmission" and "Signal Processing" subjects at West Pomeranian University of Technology (ZUT). The project serves as a comprehensive toolkit for generating, modulating, and analyzing both digital and analog signals.

## 🚀 Key Features
* **Fourier Analysis (DFT & FFT):** Implementation of the Discrete Fourier Transform from scratch, alongside an optimized Fast Fourier Transform wrapper. Includes calculation of amplitude spectra in both linear and logarithmic (dB) scales.
* **Analog Modulations (AM, FM, PM):** Simulation of Amplitude, Frequency, and Phase modulations. 
* **Bandwidth Calculation:** Implementation of signal bandwidth calculation algorithms using both the envelope drop method (e.g., -3dB, -6dB) and the energy integration method (80% energy containment).
* **Digital Modulations (ASK, FSK, PSK):** Coding of ASCII strings into 7-bit binary streams and modulating them onto carrier waves using Shift Keying techniques.

## 🛠️ Technologies & Libraries
* **C++17** (Vectors, Complex Numbers, File I/O, Mathematical Modeling)
* **CMake** (Build system and dependency management)
* **[KissFFT](https://github.com/mborgerding/kissfft):** Used for highly efficient, production-ready Fast Fourier Transform calculations.
* **[Matplot++](https://github.com/alandefreitas/matplotplusplus):** Used to render native, MATLAB-style plots and stems directly from C++ vectors to visualize signals in both the time and frequency domains.

## 👨‍💻 About Me
I am a Computer Science student with a focus on Cloud Engineering, interested in systems programming, automation, and backend infrastructure.
