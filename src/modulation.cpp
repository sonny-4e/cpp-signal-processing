#define _USE_MATH_DEFINES
#include "../include/modulation.h"
#include <cmath>

using namespace std;

vector<double> modulateAM(const vector<double>& time, const vector<double>& message, double kA, double fn) {
    vector<double> zA(time.size());
    for (size_t n = 0; n < time.size(); ++n) {
        zA[n] = (kA * message[n] + 1) * cos(2 * M_PI * fn * time[n]);
    }
    return zA;
}

vector<double> modulatePM(const vector<double>& time, const vector<double>& message, double kP, double fn) {
    vector<double> zP(time.size());
    for (size_t n = 0; n < time.size(); ++n) {
        zP[n] = cos(2 * M_PI * fn * time[n] + kP * message[n]);
    }
    return zP;
}

vector<double> modulateFM(const vector<double>& time, const vector<double>& message, double kF, double fm, double fn) {
    vector<double> zF(time.size());
    for (size_t n = 0; n < time.size(); ++n) {
        zF[n] = cos(2 * M_PI * fn * time[n] + (kF / fm) * message[n]);
    }
    return zF;
}