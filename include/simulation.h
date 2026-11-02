#pragma once

#include <vector>

#include "simulation_state.h"
#include "track.h"
#include "train.h"

namespace kineticrail {

struct SimulationConfig {
    double dt_s;              // time step [s]
    double max_time_s;        // hard time limit [s]
    double initial_speed_mps; // starting speed [m/s]
    double brake_force_N;     // constant service brake force [N]; 0 = traction run
};

class Simulation {
public:
    Simulation(const Train& train, const Track& track, SimulationConfig config);

    // Runs the time-stepped model and returns one state per step, including the final one.
    // Stops when the train comes to rest with no net forward force, reaches the end of
    // the track, or exceeds max_time_s.
    std::vector<SimulationState> run() const;

private:
    Train train_;
    Track track_;
    SimulationConfig config_;
};

}  // namespace kineticrail