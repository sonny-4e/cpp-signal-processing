#pragma once
#include <vector>
#include <complex>


std::vector<std::complex<double>> calculateDFT(const std::vector<double>& x);

std::vector<std::complex<double>> calculateFFT(const std::vector<double>& x);

std::vector<double> getFrequencyVector(int N, double Fs);

std::vector<double> getAmplitudeSpectrum(const std::vector<std::complex<double>>& fft_result, bool in_dB = false);