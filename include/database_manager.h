#pragma once

#include <string>
#include <vector>

#include <SQLiteCpp/SQLiteCpp.h>

#include "simulation_state.h"

namespace kineticrail {

class DatabaseManager {
public:
    // Opens or creates the database and ensures the tables exist.
    explicit DatabaseManager(const std::string& path);

    // Inserts a test_runs row and returns its id.
    long long createTestRun(const std::string& name, const std::string& config_json);

    // Writes all states for one run in a single transaction.
    void logTelemetry(long long run_id, const std::vector<SimulationState>& states);

private:
    SQLite::Database db_;
};

}  // namespace kineticrail