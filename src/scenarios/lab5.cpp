#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include "../../include/modulation.h"
#include "../../include/transforms.h"
#include "../../include/utils.h" 
#include "../../include/tools.h"
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>


using namespace std;
using namespace matplot;


void generuj_wykres_lab5(string podpunkt, double kA, double kP, double kF) {
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

    auto fft_zA = calculateFFT(zA);
    auto fft_zP = calculateFFT(zP);
    auto fft_zF = calculateFFT(zF);

    auto widmo_zA = getAmplitudeSpectrum(fft_zA, true);
    auto widmo_zP = getAmplitudeSpectrum(fft_zP, true);
    auto widmo_zF = getAmplitudeSpectrum(fft_zF, true);
    auto fk = getFrequencyVector(N, Fs);

    auto widmo_zA_dB = getAmplitudeSpectrum(fft_zA, true);
    auto widmo_zP_dB = getAmplitudeSpectrum(fft_zP, true);
    auto widmo_zF_dB = getAmplitudeSpectrum(fft_zF, true);

    cout << "\n    WYNIKI DLA PODPUNKTU " << podpunkt<< endl;

    cout << "[CZESC 1] Metoda spadkowa (z widma w decybelach):" << endl;
    cout << "AM:  B3=" << oblicz_pasmo(widmo_zA_dB, fk, 3) << " Hz, B6=" << oblicz_pasmo(widmo_zA_dB, fk, 6) << " Hz, B10=" << oblicz_pasmo(widmo_zA_dB, fk, 10) << " Hz\n";
    cout << "PM:  B3=" << oblicz_pasmo(widmo_zP_dB, fk, 3) << " Hz, B6=" << oblicz_pasmo(widmo_zP_dB, fk, 6) << " Hz, B10=" << oblicz_pasmo(widmo_zP_dB, fk, 10) << " Hz\n";
    cout << "FM:  B3=" << oblicz_pasmo(widmo_zF_dB, fk, 3) << " Hz, B6=" << oblicz_pasmo(widmo_zF_dB, fk, 6) << " Hz, B10=" << oblicz_pasmo(widmo_zF_dB, fk, 10) << " Hz\n";

    // false = skala liniowa
    auto widmo_zA_lin = getAmplitudeSpectrum(fft_zA, false);
    auto widmo_zP_lin = getAmplitudeSpectrum(fft_zP, false);
    auto widmo_zF_lin = getAmplitudeSpectrum(fft_zF, false);

    cout << "\n[CZESC 2] Metoda energetyczna (80% energii z widma liniowego):" << endl;
    cout << "AM:  B=" << oblicz_energie(widmo_zA_lin, fn, Fs, N) << " Hz\n";
    cout << "PM:  B=" << oblicz_energie(widmo_zP_lin, fn, Fs, N) << " Hz\n";
    cout << "FM:  B=" << oblicz_energie(widmo_zF_lin, fn, Fs, N) << " Hz\n";

    figure(); stem(fk, widmo_zA_dB); title("Widmo amplitudowe M_A [dB] - " + podpunkt); xlabel("f [Hz]"); ylabel("[dB]"); save("output/lab5_widmo_MA_dB_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zP_dB); title("Widmo amplitudowe M_P [dB] - " + podpunkt); xlabel("f [Hz]"); ylabel("[dB]"); save("output/lab5_widmo_MP_dB_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zF_dB); title("Widmo amplitudowe M_F [dB] - " + podpunkt); xlabel("f [Hz]"); ylabel("[dB]"); save("output/lab5_widmo_MF_dB_" + podpunkt + ".png");

    figure(); stem(fk, widmo_zA_lin); title("Widmo amplitudowe M_A [liniowa] - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab5_widmo_MA_lin_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zP_lin); title("Widmo amplitudowe M_P [liniowa] - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab5_widmo_MP_lin_" + podpunkt + ".png");
    figure(); stem(fk, widmo_zF_lin); title("Widmo amplitudowe M_F [liniowa] - " + podpunkt); xlabel("f [Hz]"); ylabel("Amplituda"); save("output/lab5_widmo_MF_lin_" + podpunkt + ".png");
}


void run_lab05() {
    cout << "\n--- Uruchamiam Lab 5: Analiza Pasma Sygnalow Zmodulowanych ---\n";

    // A
    double kA_a = 0.5, kP_a = 0.5, kF_a = 0.5;
    generuj_wykres_lab5("a", kA_a, kP_a, kF_a);

    // B
    double kA_b = 8.0, kP_b = 0.5 * M_PI, kF_b = 0.5 * M_PI;
    generuj_wykres_lab5("b", kA_b, kP_b, kF_b);

    // C
    double kA_c = 25.0, kP_c = 3.0 * M_PI, kF_c = 3.0 * M_PI;
    generuj_wykres_lab5("c", kA_c, kP_c, kF_c);

    string wnioski =
        "WNIOSKI\n\n"

        "CZESC 1: \n"

        "Wyniki dla podpunktu a:\n"
        "AM:  B3 = 0 Hz, B6 = 0 Hz, B10 = 10 Hz\n PM : B3 = 0 Hz, B6 = 10 Hz, B10 = 10 Hz\nFM : B3 = 0 Hz, B6 = 0 Hz, B10 = 0 Hz\n"
        "Wyniki dla podpunktu b:\n"
        "AM:  B3=10 Hz, B6=10 Hz, B10=10 Hz\n PM:  B3 = 10 Hz, B6 = 20 Hz, B10 = 30 Hz\nFM : B3 = 0 Hz, B6 = 0 Hz, B10 = 10 Hz"
        "Wyniki dla podpunktu c:\n"
        "AM:  B3=10 Hz, B6=10 Hz, B10=10 Hz\nPM:  B3 = 90 Hz, B6 = 110 Hz, B10 = 120 Hz\nFM : B3 = 20 Hz, B6 = 20 Hz, B10 = 30 Hz"


        "Metoda spadkowa(3dB, 6dB, 10dB) na podstawie widma w skali decybelowej\n"
        "Szerokosc pasma dla sygnalu AM jest stala i niezalezna od glebokosci modulacji kA "
        "Dla zadanych parametrow zawsze wynosi 10 Hz, co pokrywa sie z teoria (B = 2*fm, gdzie fm=5 Hz)\n"
        "Sygnaly zmodulowane katowo (PM i FM) maja szersze widmo niz AM"
        "Sygnal noœny jest w nich rozpraszany na wiele prazkow bocznych o amplitudach opisanych funkcjami Bessela\n"

        "CZESC 2:\n" 

        "Wyniki dla podpunktu a:\n"
        "AM:  B=0.2 Hz\nPM:  B = 0.2 Hz\nFM : B = 0.2 Hz"
        "Wynik dla podpunktu b:\n"
        "AM:  B=9.2 Hz\nPM:  B = 9.2 Hz\nFM : B = 0.2 Hz"
        "Wynik dla podpunktu c:\n"
        "AM:  B=9.2 Hz\nPM:  B = 79 Hz\nFM : B = 19.2 Hz"


        "Metoda energetyczna (80% energii) na podstawie widma w skali liniowej\n"
        "Metoda energetyczna okazala sie znacznie stabilniejsza miara rzeczywistego pasma zajmowanego przez skomplikowane sygnaly katowe\n"
        "W przypadku modulacji PM o wysokim wskazniku modulacji (kP = 3*PI, przypadek C), energia zostala "
        "najbardziej rozproszona, wymagalo to najszerszego okna czestotliwosciowego do uchwycenia 80% energii "; 
        
    generuj_wniosek(wnioski);

    show();
}