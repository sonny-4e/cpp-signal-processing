#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include "../../include/transforms.h"
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace matplot;


void czesc_pierwsza_lab3() {
    double Tc = 2;
    double Fs = 1024;
    double f = 2;
    int N = round(Tc * Fs);

    vector <double> t(N), a(N), b(N), c(N);
    int H_a = floor(Fs / (2 * f));
    int H_bc = floor((Fs / (4 * f)) + 0.5);

    cout << "Liczba prazkow dla a) " << H_a << endl;
    cout << "Liczba prazkow dla b) i c) " << H_bc << endl;

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;

        double sum1 = 0;
        for (int k = 1; k <= H_a; ++k) {
            sum1 += pow(-1, k + 1) * (sin(2 * M_PI * k * f * t[n]) / (k));
        }
        a[n] = (2 / M_PI) * (sum1);

        double sum2 = 0;
        for (int k = 1; k <= H_bc; ++k) {
            sum2 += pow(-1, k - 1) * (sin(2 * M_PI * (2 * k - 1) * f * t[n])) / pow((2 * k - 1), 2);
        }
        b[n] = (8 / pow(M_PI, 2)) * sum2;

        double sum3 = 0;
        for (int k = 1; k <= H_bc; ++k) {
            sum3 += (sin(2 * M_PI * (2 * k - 1) * f * t[n])) / (2 * k - 1);
        }
        c[n] = (4 / M_PI) * sum3;
    }


    figure(); plot(t, a); title("Sygnal 1 (Pila)"); save("output/lab3_sygnal_1.png");
    figure(); plot(t, b); title("Sygnal 2 (Trojkat)"); save("output/lab3_sygnal_2.png");
    figure(); plot(t, c); title("Sygnal 3 (Prostokat)"); save("output/lab3_sygnal_3.png");


    auto fft_a = calculateFFT(a);
    auto fft_b = calculateFFT(b);
    auto fft_c = calculateFFT(c);

    auto widmo_a = getAmplitudeSpectrum(fft_a, false);
    auto widmo_b = getAmplitudeSpectrum(fft_b, false);
    auto widmo_c = getAmplitudeSpectrum(fft_c, false);
    auto fk = getFrequencyVector(N, Fs);

    figure(); stem(fk, widmo_a); xlim({ 0, 15 }); title("Widmo amplitudowe sygnalu 1"); save("output/lab3_widmo_1.png");
    figure(); stem(fk, widmo_b); xlim({ 0, 15 }); title("Widmo amplitudowe sygnalu 2"); save("output/lab3_widmo_2.png");
    figure(); stem(fk, widmo_c); xlim({ 0, 15 }); title("Widmo amplitudowe sygnalu 3"); save("output/lab3_widmo_3.png");
}

void czesc_druga_lab3() {
    double Tc = 1;
    double Fs = 8000;
    int N = round(Tc * Fs);
    double f1 = 5;
    double f2 = 12;
    double alpha = 2.5;
    double beta = 4;

    vector<double> t(N), x(N), y(N), z(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;

        x[n] = 0.5 * sin(2 * M_PI * f1 * t[n]);
        y[n] = sin(2 * M_PI * f2 * t[n]) + 0.7 * sin(2 * M_PI * f1 * t[n]);
        z[n] = alpha * x[n] + beta * y[n];
    }

    figure(); plot(t, x); title("Sygnal x(t)"); save("output/lab3_x_t.png");
    figure(); plot(t, y); title("Sygnal y(t)"); save("output/lab3_y_t.png");
    figure(); plot(t, z); title("Sygnal z(t)"); save("output/lab3_z_t.png");

    auto fft_x = calculateFFT(x);
    auto fft_y = calculateFFT(y);
    auto fft_z = calculateFFT(z);

    int polowa_N = (N / 2) - 1;
    vector<double> Mx(polowa_N), My(polowa_N), Mz(polowa_N), Mz_2(polowa_N), fk(polowa_N);

    for (int k = 0; k < polowa_N; ++k) {
        // Obliczamy widma z poprawka na 2.0/N tak jak miales w oryginalnym kodzie
        Mx[k] = sqrt(pow(fft_x[k].real(), 2) + pow(fft_x[k].imag(), 2));
        My[k] = sqrt(pow(fft_y[k].real(), 2) + pow(fft_y[k].imag(), 2));
        Mz[k] = sqrt(pow(fft_z[k].real(), 2) + pow(fft_z[k].imag(), 2));

        Mz_2[k] = alpha * Mx[k] + beta * My[k];
        fk[k] = k * (Fs / N);
    }

    figure(); stem(fk, Mx); xlim({ 0, 20 }); title("Widmo amplitudowe Mx"); save("output/lab3_widmo_Mx.png");
    figure(); stem(fk, My); xlim({ 0, 20 }); title("Widmo amplitudowe My"); save("output/lab3_widmo_My.png");
    figure(); stem(fk, Mz); xlim({ 0, 20 }); title("Widmo amplitudowe Mz"); save("output/lab3_widmo_Mz.png");
    figure(); stem(fk, Mz_2); xlim({ 0, 20 }); title("Widmo Mz^ (Ze wzoru)"); save("output/lab3_widmo_Mz_wzor.png");
}


void run_lab03() {
    cout << "\n--- Uruchamiam Lab 3: Szeregi Fouriera i Liniowosc FFT ---\n";

    cout << "Generowanie szeregow Fouriera (pila, trojkat, prostokat)...\n";
    czesc_pierwsza_lab3();

    cout << "Badanie liniowosci transformaty Fouriera...\n";
    czesc_druga_lab3();


    show();
}