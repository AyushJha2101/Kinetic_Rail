#pragma once

#include <string>

namespace kineticrail {

// One telemetry sample. Field order matches the CSV columns and is used in aggregate init.
struct SimulationState {
    double time_s;
    double position_m;
    double velocity_mps;
    double acceleration_mps2;
    double tractive_effort_N;
    double resistance_N;
};

std::string csvHeader();
std::string csvRow(const SimulationState& state);

}  // namespace kineticrail