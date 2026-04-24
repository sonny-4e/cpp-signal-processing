#include "../include/utils.h"

using namespace std;

double oblicz_pasmo(const vector<double>& widmo, const vector<double>& f, double spadek) {
    // Zabezpieczenie na wypadek pustych wektorów
    if (widmo.empty() || f.empty() || widmo.size() != f.size()) return 0.0;

    double max_val = widmo[0];
    for (size_t i = 1; i < widmo.size(); i++) {
        if (widmo[i] > max_val) {
            max_val = widmo[i];
        }
    }

    double prog = max_val - spadek;

    size_t lewy = 0;
    size_t prawy = widmo.size() - 1;

    while (lewy < widmo.size() && widmo[lewy] < prog) {
        lewy++;
    }

    while (prawy > 0 && widmo[prawy] < prog) {
        prawy--;
    }

    // Zabezpieczenie przed wyjœciem poza zakres, jeœli próg nie zosta³ przeciêty
    if (lewy >= prawy) return 0.0;

    return f[prawy] - f[lewy];
}

double oblicz_energie(const vector<double>& widmo_liniowe, double fn, double Fs, int N) {
    if (widmo_liniowe.empty()) return 0;

    double E_calkowita = 0.0;
    for (double probka : widmo_liniowe) {
        E_calkowita += probka * probka; // X(n)^2
    }

    // Zwiêkszamy alpha z krokiem a¿ znajdziemy 80% energii
    for (double alpha = 0.1; alpha <= fn; alpha += 0.1) {

        // k = (f * N) / Fs
        int ia = round(((fn - alpha) * N) / Fs);
        int ib = round(((fn + alpha) * N) / Fs);

        
        if (ia < 0) ia = 0;
        if (ib >= widmo_liniowe.size()) ib = widmo_liniowe.size() - 1;

       
        double E_okna = 0.0;
        for (int k = ia; k <= ib; ++k) {
            E_okna += widmo_liniowe[k] * widmo_liniowe[k];
        }

        // wspó³czynnik r_alpha
        double r_alpha = E_okna / E_calkowita;

        // Sprawdzenie warunku (> 80%)
        if (r_alpha > 0.80) {
            return 2.0 * alpha; // B = f_b - f_a = 2 * alpha
        }
    }

    return 0; 
}