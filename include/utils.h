#pragma once
#include <vector>

// Funkcja do obliczania pasma sygna³u na podstawie zadanego spadku (np. 3 dB, 6 dB)
double oblicz_pasmo(const std::vector<double>& widmo, const std::vector<double>& f, double spadek);

// Funckja do obliczania energii ca³kowitej widma 
double oblicz_energie(const std::vector<double>& widmo_liniowe, double fn, double Fs, int N);