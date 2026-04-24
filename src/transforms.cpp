#define _USE_MATH_DEFINES
#include "../include/transforms.h"
#include "../third_party/kiss_fft/kiss_fft.h"
#include <cmath>

using namespace std;


vector<complex<double>> calculateDFT(const vector<double>& x) {
    int N = x.size();
    vector<complex<double>> wynik(N);

    for (int k = 0; k < N - 1; ++k) {
        double a_suma = 0.0;
        double b_suma = 0.0;

        for (int n = 0; n < N; ++n) {
            double alfa = (-2 * M_PI * n * k) / N;
            a_suma += x[n] * cos(alfa);
            b_suma += x[n] * sin(alfa);
        }
        wynik[k] = complex<double>(a_suma, b_suma);
    }
    return wynik;
}

vector<complex<double>> calculateFFT(const vector<double>& x) {
    int N = x.size();
    vector<complex<double>> result(N);

    kiss_fft_cfg cfg = kiss_fft_alloc(N, 0, NULL, NULL);
    if (!cfg) return result; 

    vector<kiss_fft_cpx> cx_in(N), cx_out(N);

    for (int n = 0; n < N; ++n) {
        cx_in[n].r = x[n];
        cx_in[n].i = 0.0;
    }

    kiss_fft(cfg, cx_in.data(), cx_out.data());

    // Zwalnianie pamiêci
    free(cfg);

    // Konwersja z powrotem na wygodny format (complex)
    for (int k = 0; k < N; ++k) {
        result[k] = complex<double>(cx_out[k].r, cx_out[k].i);
    }

    return result;
}

vector<double> getFrequencyVector(int N, double Fs) {
    int half_N = (N / 2) - 1;
    vector<double> fk(half_N);
    for (int k = 0; k < half_N; ++k) {
        fk[k] = k * (Fs / N);
    }
    return fk;
}

vector<double> getAmplitudeSpectrum(const vector<complex<double>>& fft_result, bool in_dB) {
    int N = fft_result.size();
    int half_N = (N / 2) - 1;
    vector<double> widmo(half_N);

    for (int k = 0; k < half_N; ++k) {
        // Obliczanie modu³u liczby zespolonej
        double M_k = sqrt(pow(fft_result[k].real(), 2) + pow(fft_result[k].imag(), 2));

        if (in_dB) {
            if (M_k < 1e-12) M_k = 1e-12; // Zabezpieczenie dla logarytmu (log10(0) nie istnieje)
            widmo[k] = 10 * log10(M_k);
        }
        else {
            widmo[k] = M_k;
        }
    }
    return widmo;
}