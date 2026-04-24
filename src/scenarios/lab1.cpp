#define _USE_MATH_DEFINES
#include "../../include/scenarios.h"
#include <matplot/matplot.h>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;
using namespace matplot;

void czesc_pierwsza_lab1() {
    double Tc = 2;
    double Fs = 8000;
    double f = 1;
    double fi = 0;
    int N = round(Tc * Fs);

    vector<double> t(N), x(N), y(N), z(N), v(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;

        x[n] = sin(2 * M_PI * f * t[n] * cos(3 * M_PI * t[n]) + t[n] * fi);
        y[n] = (pow(t[n], 3) - 1) + cos(4 * pow(t[n], 2) * M_PI) * t[n];
        z[n] = x[n] / (abs(y[n] * cos(5 * t[n]) - x[n] * y[n]) + 3);
        v[n] = (x[n] * 662) / (abs(x[n] - y[n]) + 0.5);
    }

    figure(); plot(t, x); title("Sygnal X"); save("output/lab1_x.png");
    figure(); plot(t, y); title("Sygnal Y"); save("output/lab1_y.png");
    figure(); plot(t, z); title("Sygnal Z"); save("output/lab1_z.png");
    figure(); plot(t, v); title("Sygnal V"); save("output/lab1_v.png");
}

void czesc_druga_lab1() {
    double Tc = 4;
    double Fs = 8000;
    double f = 1;
    double fi = 0;
    int N = round(Tc * Fs);

    vector <double> t(N), u(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;
        double value = 0;
        if (t[n] >= 0 && t[n] < 1.2) {
            value = (-1 * pow(t[n], 2) + 0.5) * sin(30 * M_PI * t[n]) * log2(pow(t[n], 2) + 1);
        }
        else if (t[n] >= 1.2 && t[n] < 2) {
            value = (1 / t[n]) * 0.8 * sin(24 * M_PI * t[n]) - 0.1 * t[n];
        }
        else if (t[n] >= 2 && t[n] < 2.4) {
            value = pow(abs(sin(2 * M_PI * pow(t[n], 2))), 0.8);
        }
        else if (t[n] >= 2.4 && t[n] < 3.1) {
            value = (pow(t[n], 4) * log10(t[n])) / 30;
        }

        u[n] = value;
    }

    figure();
    plot(t, u);
    title("Sygnal U (zlozony)");
    xlim({ 0.0, 4.0 });
    ylim({ -2.0, 2.0 });
    save("output/lab1_u.png");
}

void czesc_druga_zad2_lab1() {
    double Tc = 1;
    double Fs = 22050;
    double f = 1;
    int N = round(Tc * Fs);

    vector <double>  t(N), b1(N), b2(N), b3(N);

    for (int n = 0; n < N; ++n) {
        t[n] = n / Fs;

        double sum1 = 0;
        for (int h = 1; h <= 2; ++h) {
            sum1 += pow(-1, h) * (sin(2 * M_PI * h * t[n]) + cos(6 * M_PI * h * t[n]));
        }
        b1[n] = abs(sum1);

        double sum2 = 0;
        for (int h = 1; h <= 20; ++h) {
            sum2 += pow(-1, h) * (sin(2 * M_PI * h * t[n]) + cos(6 * M_PI * h * t[n]));
        }
        b2[n] = abs(sum2);

        double sum3 = 0;
        for (int h = 1; h <= 60; ++h) {
            sum3 += pow(-1, h) * (sin(2 * M_PI * h * t[n]) + cos(6 * M_PI * h * t[n]));
        }
        b3[n] = abs(sum3);
    }

    figure(); plot(t, b1); title("Sygnal b1(t) [H=2]"); save("output/lab1_b1.png");
    figure(); plot(t, b2); title("Sygnal b2(t) [H=20]"); save("output/lab1_b2.png");
    figure(); plot(t, b3); title("Sygnal b3(t) [H=60]"); save("output/lab1_b3.png");
}


void run_lab01() {
    cout << "\n--- Uruchamiam Lab 1: Generacja Sygnalow ---\n";

    cout << "Generowanie sygnalow x, y, z, v...\n";
    czesc_pierwsza_lab1();

    cout << "Generowanie sygnalu warunkowego u...\n";
    czesc_druga_lab1();

    cout << "Generowanie szeregow b1, b2, b3...\n";
    czesc_druga_zad2_lab1();


    show();
}