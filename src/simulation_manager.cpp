#include "simulation_manager.h"

#include <filesystem>
#include <sstream>
#include <utility>

namespace kineticrail {

namespace {

std::string configToJson(const SimulationConfig& c) {
    std::ostringstream out;
    out << "{\"dt_s\":" << c.dt_s
        << ",\"max_time_s\":" << c.max_time_s
        << ",\"initial_speed_mps\":" << c.initial_speed_mps
        << ",\"brake_force_N\":" << c.brake_force_N << "}";
    return out.str();
}

}  // namespace

SimulationManager::SimulationManager(const std::string& db_path, std::string output_dir)
    : db_(db_path), output_dir_(std::move(output_dir)) {
    std::filesystem::create_directories(output_dir_);
}

RunSummary SimulationManager::runTest(const std::string& name, const Train& train,
                                      const Track& track, const SimulationConfig& config) {
    Simulation sim(train, track, config);
    const auto states = sim.run();

    writeCsv(output_dir_ + "/" + name + ".csv", states);

    const long long run_id = db_.createTestRun(name, configToJson(config));
    db_.logTelemetry(run_id, states);

    return summarize(states);
}

}  // namespace kineticrail