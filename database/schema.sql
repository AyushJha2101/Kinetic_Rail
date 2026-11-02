-- KineticRail database schema.
-- Mirrors the CREATE TABLE statements in src/database_manager.cpp.
-- The application creates these tables automatically; this file is for reference.

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