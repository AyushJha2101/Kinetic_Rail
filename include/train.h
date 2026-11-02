#pragma once

#include <string>

#include "physics_engine.h"

namespace kineticrail {

struct Train {
    std::string name;
    double mass_kg;                 // total mass [kg]
    double max_tractive_effort_N;   // locomotive maximum [N]
    DavisCoefficients davis;
};

// Throws std::invalid_argument if mass or max tractive effort is not positive.
void validateTrain(const Train& train);

}  // namespace kineticrail