#pragma once

#include <string>

#include "database_manager.h"
#include "result_manager.h"
#include "simulation.h"
#include "track.h"
#include "train.h"

namespace kineticrail {

class SimulationManager {
public:
    SimulationManager(const std::string& db_path, std::string output_dir);

    // Runs one test, writes a CSV to output_dir/<name>.csv, logs the run and its
    // telemetry to the database, and returns the summary.
    RunSummary runTest(const std::string& name, const Train& train, const Track& track,
                       const SimulationConfig& config);

private:
    DatabaseManager db_;
    std::string output_dir_;
};

}  // namespace kineticrail