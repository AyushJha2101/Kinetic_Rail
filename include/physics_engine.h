#pragma once

namespace kineticrail {

inline constexpr double kGravity = 9.80665;  // m/s^2

// Davis equation: F = A + B*v + C*v^2
// Units: A [N], B [N·s/m], C [N·s²/m²]
struct DavisCoefficients {
    double A;
    double B;
    double C;
};

// Running resistance [N]. Throws std::invalid_argument if speed_mps < 0.
double davisResistance(const DavisCoefficients& coeffs, double speed_mps);

// Gradient resistance [N]. grade is rise/run (0.01 = 1%), positive = uphill.
// Small-angle approximation: sin(theta) ~ grade.
double gradeResistance(double mass_kg, double grade);

// Curve resistance [N] from the empirical 600/R rule (600 N per 1000 N of weight,
// R in metres). radius_m == 0 means straight track and returns 0.
double curveResistance(double mass_kg, double radius_m);

// Maximum tractive force [N] before wheel slip: mu * m * g.
double adhesionLimit(double mass_kg, double adhesion_coefficient);

// Tractive effort actually available [N]: the lesser of the locomotive's
// maximum and the adhesion limit.
double tractiveEffortLimited(double max_tractive_effort_N, double mass_kg,
                             double adhesion_coefficient);

}  // namespace kineticrail