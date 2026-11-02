#pragma once

#include <string>
#include <vector>

#include "simulation_state.h"

namespace kineticrail {

struct RunSummary {
    double stopping_distance_m;  // position at the final state
    double duration_s;
    double peak_speed_mps;
    bool came_to_rest;
};

RunSummary summarize(const std::vector<SimulationState>& states);

// Throws std::runtime_error if the file cannot be opened.
void writeCsv(const std::string& path, const std::vector<SimulationState>& states);

}  // namespace kineticrail