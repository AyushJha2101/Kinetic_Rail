#include "simulation.h"

#include <stdexcept>

#include "physics_engine.h"

namespace kineticrail {

Simulation::Simulation(const Train& train, const Track& track, SimulationConfig config)
    : train_(train), track_(track), config_(config) {
    validateTrain(train_);
    if (config_.dt_s <= 0.0) {
        throw std::invalid_argument("Simulation: dt_s must be > 0");
    }
    if (config_.max_time_s <= 0.0) {
        throw std::invalid_argument("Simulation: max_time_s must be > 0");
    }
    if (config_.initial_speed_mps < 0.0) {
        throw std::invalid_argument("Simulation: initial speed must be >= 0");
    }
    if (config_.brake_force_N < 0.0) {
        throw std::invalid_argument("Simulation: brake force must be >= 0");
    }
}

std::vector<SimulationState> Simulation::run() const {
    std::vector<SimulationState> history;

    const double dt = config_.dt_s;
    const double m = train_.mass_kg;
    const bool braking = config_.brake_force_N > 0.0;

    double t = 0.0;
    double x = 0.0;
    double v = config_.initial_speed_mps;

    while (t <= config_.max_time_s && x < track_.totalLength()) {
        const TrackSegment& seg = track_.segmentAt(x);

        const double drive = braking
            ? 0.0
            : tractiveEffortLimited(train_.max_tractive_effort_N, m, seg.adhesion_coefficient);
        const double resist = davisResistance(train_.davis, v)
            + gradeResistance(m, seg.grade)
            + curveResistance(m, seg.curve_radius_m);
        const double brake = braking ? config_.brake_force_N : 0.0;

        const double net = drive - resist - brake;
        const double a = net / m;

        history.push_back({t, x, v, a, drive, resist});

        // At rest with no net forward force: the run is finished.
        if (v <= 0.0 && net <= 0.0) {
            break;
        }

        // Semi-implicit Euler. The train never reverses in this model.
        double v_next = v + a * dt;
        if (v_next < 0.0) {
            v_next = 0.0;
        }
        x += v_next * dt;
        v = v_next;
        t += dt;
    }

    return history;
}

}  // namespace kineticrail