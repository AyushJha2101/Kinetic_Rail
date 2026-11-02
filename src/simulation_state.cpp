#include "simulation_state.h"

#include <sstream>

namespace kineticrail {

std::string csvHeader() {
    return "time_s,position_m,velocity_mps,acceleration_mps2,tractive_effort_N,resistance_N";
}

std::string csvRow(const SimulationState& s) {
    std::ostringstream out;
    out.precision(10);
    out << s.time_s << ',' << s.position_m << ',' << s.velocity_mps << ','
        << s.acceleration_mps2 << ',' << s.tractive_effort_N << ',' << s.resistance_N;
    return out.str();
}

}  // namespace kineticrail