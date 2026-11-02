#include "database_manager.h"

namespace kineticrail {

DatabaseManager::DatabaseManager(const std::string& path)
    : db_(path, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
    db_.exec(R"sql(
        CREATE TABLE IF NOT EXISTS test_runs (
            id         INTEGER PRIMARY KEY AUTOINCREMENT,
            name       TEXT NOT NULL,
            created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
            config     TEXT
        );
        CREATE TABLE IF NOT EXISTS telemetry_logs (
            id                  INTEGER PRIMARY KEY AUTOINCREMENT,
            run_id              INTEGER NOT NULL REFERENCES test_runs(id),
            time_s              REAL NOT NULL,
            position_m          REAL NOT NULL,
            velocity_mps        REAL NOT NULL,
            acceleration_mps2   REAL NOT NULL,
            tractive_effort_N   REAL NOT NULL,
            resistance_N        REAL NOT NULL
        );
    )sql");
}

long long DatabaseManager::createTestRun(const std::string& name, const std::string& config_json) {
    SQLite::Statement q(db_, "INSERT INTO test_runs (name, config) VALUES (?, ?)");
    q.bind(1, name);
    q.bind(2, config_json);
    q.exec();
    return db_.getLastInsertRowid();
}

void DatabaseManager::logTelemetry(long long run_id, const std::vector<SimulationState>& states) {
    SQLite::Transaction tx(db_);
    SQLite::Statement q(db_,
        "INSERT INTO telemetry_logs "
        "(run_id, time_s, position_m, velocity_mps, acceleration_mps2, tractive_effort_N, resistance_N) "
        "VALUES (?, ?, ?, ?, ?, ?, ?)");
    for (const auto& s : states) {
        q.bind(1, run_id);
        q.bind(2, s.time_s);
        q.bind(3, s.position_m);
        q.bind(4, s.velocity_mps);
        q.bind(5, s.acceleration_mps2);
        q.bind(6, s.tractive_effort_N);
        q.bind(7, s.resistance_N);
        q.exec();
        q.reset();
    }
    tx.commit();
}

}  // namespace kineticrail