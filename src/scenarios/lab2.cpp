#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include "../../include/transforms.h"
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace matplot;



void czesc_pierwsza_lab2() {
    double Tc = 1;
    double Fs = 16000;
    double f = 50;
    int N = round(Tc * Fs);

    vector<double> t(N), x(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;
        x[n] = sin(2 * M_PI * f * t[n]);
    }

 
    vector<complex<double>> X = calculateDFT(x);

   
    vector<double> widmo_amplitudowe = getAmplitudeSpectrum(X, false);
    vector<double> fk = getFrequencyVector(N, Fs);

    figure();
    plot(t, x);
    title("Sygnal w dziedzinie czasu x(t)");
    xlabel("Czas [s]");
    ylabel("Amplituda");
    xlim({ 0, 0.1 });
    save("output/lab2_czesc1_sygnal.png");

    figure();
    stem(fk, widmo_amplitudowe);
    title("Widmo amplitudowe M(k)");
    xlabel("Czestotliwosc [Hz]");
    ylabel("Amplituda");
    xlim({ 0, 100 });
    save("output/lab2_czesc1_widmo.png");
}

void czesc_druga_lab2() {
   
    double Tc = 1;
    double Fs = 16000;
    double f = 50;
    int N = round(Tc * Fs);

    vector<double> t(N), x(N);
    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;
        x[n] = sin(2 * M_PI * f * t[n]);
    }

    vector<complex<double>> X = calculateDFT(x);
    vector<double> widmo_amplitudowe = getAmplitudeSpectrum(X, true); // true = skala dB
    vector<double> fk = getFrequencyVector(N, Fs);

  
    double Fs2 = 2000;
    double Tc2 = 1;
    int N2 = round(Tc2 * Fs2);

    double f1 = 10;
    double f2 = (Fs2 / 2) - f1;
    double f3 = f1 / 2;

    vector<double> t2(N2), x2(N2);
    for (int n = 0; n < N2; ++n) {
        t2[n] = n / Fs2;
        x2[n] = sin(2 * M_PI * f1 * t2[n]) + sin(2 * M_PI * f2 * t2[n]) + sin(2 * M_PI * f3 * t2[n]);
    }

    vector<complex<double>> X2 = calculateDFT(x2);
    vector<double> widmo_amplitudowe2 = getAmplitudeSpectrum(X2, true); // true = skala dB
    vector<double> fk2 = getFrequencyVector(N2, Fs2);

   
    figure();
    plot(fk, widmo_amplitudowe);
    title("Widmo sygnalu 1 [dB]");
    xlabel("f [Hz]");
    ylabel("M'(k) [dB]");
    save("output/lab2_widmo_sygnalu_1.png");

    figure();
    plot(fk2, widmo_amplitudowe2);
    title("Widmo sygnalu 2 (skala liniowa - osi x)");
    xlabel("f [Hz]");
    ylabel("M'(k) [dB]");
    save("output/lab2_widmo_sygnalu_2_liniowa.png");

    figure();
    semilogx(fk2, widmo_amplitudowe2);
    title("Widmo sygnalu 2 (skala logarytmiczna - osi x)");
    xlabel("f [Hz]");
    ylabel("M'(k) [dB]");
    save("output/lab2_widmo_sygnalu_2_logarytmiczna.png");
}



void run_lab02() {
    cout << "\n--- Uruchamiam Lab 2: Implementacja i Analiza DFT ---\n";

    cout << "Generowanie sygnalu bazowego i wyliczanie DFT...\n";
    czesc_pierwsza_lab2();

    cout << "Generowanie sygnalu zlozonych i analizy w skali decybelowej...\n";
    czesc_druga_lab2();



    show();
}