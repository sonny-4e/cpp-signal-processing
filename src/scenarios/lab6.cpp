#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include "../../include/modulation.h"
#include "../../include/transforms.h"
#include "../../include/utils.h" 
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace matplot;

// Funkcja zamieniajaca napis ASCII na strumien 7-bitowy
string ascii_to_7bit_binary(const string& text) {
    string binary = "";
    for (char c : text) {
        // Konwersja znaku na 7 bitow
        for (int i = 6; i >= 0; --i) {
            binary += ((c >> i) & 1) ? '1' : '0';
        }
    }
    return binary;
}

void czesc_pierwsza_lab6() {
    cout << "  Generowanie przebiegow czasowych (B = 10 bitow)..." << endl;

    string bits = "0110100110"; // Dokladnie 10 bitow
    int B = bits.length();

    double Tc = 1.0;            // Czas trwania calego sygnalu [s]
    double Tb = Tc / B;         // Czas trwania pojedynczego bitu
    double Fs = 2000.0;         // Czestotliwosc probkowania
    int N = round(Tc * Fs);

    double W = 2.0;
    double fn = W / Tb;
    double fn1 = (W + 1.0) / Tb;
    double fn2 = (W + 2.0) / Tb;

    double A1 = 0.5; // Amplituda dla zera
    double A2 = 1.5; // Amplituda dla jedynki

    vector<double> t(N), Za(N), Zf(N), Zp(N), sygnal_binarny(N);

    for (int i = 0; i < N; ++i) {
        t[i] = i / Fs;

        // Ustalenie, ktory bit aktualnie modulujemy
        int bit_index = t[i] / Tb;
        if (bit_index >= B) bit_index = B - 1;

        char b = bits[bit_index];

        // Do celow wizualizacyjnych (fala prostokatna)
        sygnal_binarny[i] = (b == '0') ? -0.5 : 2.0;

        if (b == '0') {
            Za[i] = A1 * sin(2 * M_PI * fn * t[i]);
            Zf[i] = sin(2 * M_PI * fn1 * t[i]);
            Zp[i] = sin(2 * M_PI * fn * t[i]);
        }
        else {
            Za[i] = A2 * sin(2 * M_PI * fn * t[i]);
            Zf[i] = sin(2 * M_PI * fn2 * t[i]);
            Zp[i] = sin(2 * M_PI * fn * t[i] + M_PI);
        }
    }

    figure(); plot(t, sygnal_binarny, "--r", t, Za, "-b"); title("ASK - Kluczowanie Amplitudy"); save("output/lab6_ASK_czas.png");
    figure(); plot(t, sygnal_binarny, "--r", t, Zf, "-b"); title("FSK - Kluczowanie Czestotliwosci"); save("output/lab6_FSK_czas.png");
    figure(); plot(t, sygnal_binarny, "--r", t, Zp, "-b"); title("PSK - Kluczowanie Fazy"); save("output/lab6_PSK_czas.png");
}

void czesc_druga_lab6() {
    cout << "  Generowanie widm w skali decybelowej (cale slowo ASCII)..." << endl;

    string word = "ZUT";
    string bits = ascii_to_7bit_binary(word);
    int B = bits.length(); // 3 znaki * 7 bitow = 21 bitow

    double Tc = 1.0;
    double Tb = Tc / B;
    double Fs = 4000.0; // Wyzsze probkowanie dla lepszego widma
    int N = round(Tc * Fs);

    double W = 2.0;
    double fn = W / Tb;
    double fn1 = (W + 1.0) / Tb;
    double fn2 = (W + 2.0) / Tb;

    double A1 = 0.5, A2 = 1.5;

    vector<double> t(N), Za(N), Zf(N), Zp(N);

    for (int i = 0; i < N; ++i) {
        t[i] = i / Fs;
        int bit_index = t[i] / Tb;
        if (bit_index >= B) bit_index = B - 1;

        char b = bits[bit_index];

        if (b == '0') {
            Za[i] = A1 * sin(2 * M_PI * fn * t[i]);
            Zf[i] = sin(2 * M_PI * fn1 * t[i]);
            Zp[i] = sin(2 * M_PI * fn * t[i]);
        }
        else {
            Za[i] = A2 * sin(2 * M_PI * fn * t[i]);
            Zf[i] = sin(2 * M_PI * fn2 * t[i]);
            Zp[i] = sin(2 * M_PI * fn * t[i] + M_PI);
        }
    }

    auto fft_zA = calculateFFT(Za);
    auto fft_zP = calculateFFT(Zp);
    auto fft_zF = calculateFFT(Zf);

    // true = skala dB
    auto widmo_zA = getAmplitudeSpectrum(fft_zA, true);
    auto widmo_zP = getAmplitudeSpectrum(fft_zP, true);
    auto widmo_zF = getAmplitudeSpectrum(fft_zF, true);
    auto fk = getFrequencyVector(N, Fs);

    figure(); stem(fk, widmo_zA); xlim({ 0, 300 }); title("Widmo ASK [dB] dla slowa " + word); xlabel("f [Hz]"); ylabel("M(k) [dB]"); save("output/lab6_ASK_widmo.png");
    figure(); stem(fk, widmo_zF); xlim({ 0, 300 }); title("Widmo FSK [dB] dla slowa " + word); xlabel("f [Hz]"); ylabel("M(k) [dB]"); save("output/lab6_FSK_widmo.png");
    figure(); stem(fk, widmo_zP); xlim({ 0, 300 }); title("Widmo PSK [dB] dla slowa " + word); xlabel("f [Hz]"); ylabel("M(k) [dB]"); save("output/lab6_PSK_widmo.png");
}

void run_lab06() {
    cout << "\n--- Uruchamiam Lab 6: Modulacje Cyfrowe (ASK, FSK, PSK) ---\n";
    czesc_pierwsza_lab6();
    czesc_druga_lab6();
    show();
}