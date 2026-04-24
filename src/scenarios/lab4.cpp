#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include "../../include/modulation.h"
#include "../../include/transforms.h"
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace matplot;


void generuj_wykres(string podpunkt, double kA, double kP, double kF) {
    cout << "Generowanie wykresow dla podpunktu " << podpunkt << "...\n";

    double Tc = 1;
    double Fs = 1000;
    double fm = 5;
    double fn = 70;
    int N = round(Tc * Fs);

    vector<double> t(N), m(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;
        m[n] = sin(2 * M_PI * fm * t[n]);
    }

    vector<double> zA = modulateAM(t, m, kA, fn);
    vector<double> zP = modulatePM(t, m, kP, fn);
    vector<double> zF = modulateFM(t, m, kF, fm, fn);

    figure(); plot(t, zA); title("Sygnal zA(t) - " + podpunkt); xlabel("Czas [s]"); ylabel("Amplituda"); save("output/lab4_sygnal_zA_" + podpunkt + ".png");
    figure(); plot(t, zP); title("Sygnal zP(t) - " + podpunkt); xlabel("Czas [s]"); ylabel("Amplituda"); save("output/lab4_sygnal_zP_" + podpunkt + ".png");
    figure(); plot(t, zF); title("Sygnal zF(t) - " + podpunkt); xlabel("Czas [s]"); ylabel("Amplituda"); save("output/lab4_sygnal_zF_" + podpunkt + ".png");

    auto fft_zA = calculateFFT(zA);
    auto fft_zP = calculateFFT(zP);
    auto fft_zF = calculateFFT(zF);

    auto widmo_zA = getAmplitudeSpectrum(fft_zA, false);
    auto widmo_zP = getAmplitudeSpectrum(fft_zP, false);
    auto widmo_zF = getAmplitudeSpectrum(fft_zF, false);
    auto fk = getFrequencyVector(N, Fs);

    figure(); stem(fk, widmo_zA); xlim({ 0, 100 }); title("Widmo M_A - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab4_widmo_MA_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zP); xlim({ 0, 100 }); title("Widmo M_P - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab4_widmo_MP_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zF); xlim({ 0, 100 }); title("Widmo M_F - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab4_widmo_MF_" + podpunkt + ".png");
}


void run_lab04() {
    cout << "\n--- Uruchamiam Lab 4: Modulacje Analogowe (AM, PM, FM) ---\n";

   
    double kA_a = 0.5, kP_a = 0.5, kF_a = 0.5;
    generuj_wykres("a", kA_a, kP_a, kF_a);

   
    double kA_b = 8.0, kP_b = 0.5 * M_PI, kF_b = 0.5 * M_PI;
    generuj_wykres("b", kA_b, kP_b, kF_b);


    double kA_c = 25.0, kP_c = 3.0 * M_PI, kF_c = 3.0 * M_PI;
    generuj_wykres("c", kA_c, kP_c, kF_c);


    show();
}