#pragma once
#include <vector>



std::vector<double> modulateAM(const std::vector<double>& time, const std::vector<double>& message, double kA, double fn);
std::vector<double> modulatePM(const std::vector<double>& time, const std::vector<double>& message, double kP, double fn);
std::vector<double> modulateFM(const std::vector<double>& time, const std::vector<double>& message, double kF, double fm, double fn);