#include "result_manager.h"

#include <algorithm>
#include <fstream>
#include <stdexcept>

namespace kineticrail {

RunSummary summarize(const std::vector<SimulationState>& states) {
    RunSummary s{0.0, 0.0, 0.0, false};
    if (states.empty()) {
        return s;
    }
    for (const auto& st : states) {
        s.peak_speed_mps = std::max(s.peak_speed_mps, st.velocity_mps);
    }
    s.stopping_distance_m = states.back().position_m;
    s.duration_s = states.back().time_s;
    s.came_to_rest = states.back().velocity_mps == 0.0;
    return s;
}

void writeCsv(const std::string& path, const std::vector<SimulationState>& states) {
    std::ofstream out(path);
    if (!out) {
        throw std::runtime_error("writeCsv: cannot open " + path);
    }
    out << csvHeader() << '\n';
    for (const auto& st : states) {
        out << csvRow(st) << '\n';
    }
}

}  // namespace kineticrail