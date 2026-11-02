#include "physics_engine.h"

#include <algorithm>
#include <stdexcept>

namespace kineticrail {

double davisResistance(const DavisCoefficients& coeffs, double speed_mps) {
    if (speed_mps < 0.0) {
        throw std::invalid_argument("davisResistance: speed must be >= 0 m/s");
    }
    return coeffs.A + coeffs.B * speed_mps + coeffs.C * speed_mps * speed_mps;
}

double gradeResistance(double mass_kg, double grade) {
    if (mass_kg <= 0.0) {
        throw std::invalid_argument("gradeResistance: mass must be > 0 kg");
    }
    return mass_kg * kGravity * grade;
}

double curveResistance(double mass_kg, double radius_m) {
    if (mass_kg <= 0.0) {
        throw std::invalid_argument("curveResistance: mass must be > 0 kg");
    }
    if (radius_m < 0.0) {
        throw std::invalid_argument("curveResistance: radius must be >= 0 m");
    }
    if (radius_m == 0.0) {
        return 0.0;  // straight track
    }
    return 0.6 * mass_kg * kGravity / radius_m;
}

double adhesionLimit(double mass_kg, double adhesion_coefficient) {
    if (mass_kg <= 0.0 || adhesion_coefficient <= 0.0) {
        throw std::invalid_argument("adhesionLimit: mass and coefficient must be > 0");
    }
    return adhesion_coefficient * mass_kg * kGravity;
}

double tractiveEffortLimited(double max_tractive_effort_N, double mass_kg,
                             double adhesion_coefficient) {
    return std::min(max_tractive_effort_N, adhesionLimit(mass_kg, adhesion_coefficient));
}

}  // namespace kineticrail