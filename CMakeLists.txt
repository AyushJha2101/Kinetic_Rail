cmake_minimum_required(VERSION 3.15)

# The core engine runs in C++. (Python data analysis scripts run externally).
project(KineticRail VERSION 1.0 LANGUAGES CXX)

# Require C++17 standard for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------------------------------
# 1. Core Physics Library
# Keeps physics calculations separate from I/O and UI code
# ---------------------------------------------------------
add_library(KineticRail_Core STATIC
    src/Physics/DavisResistance.cpp
    src/Physics/TractiveEffort.cpp
    # Add future physics modules here
)
target_include_directories(KineticRail_Core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ---------------------------------------------------------
# 2. SQLite Database Integration (Data Logging & I/O)
# Fetch SQLiteCpp automatically during the build process
# ---------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(SQLiteCpp)

# ---------------------------------------------------------
# 3. Main Executable (The Time-Step Simulator)
# ---------------------------------------------------------
add_executable(KineticRail src/main.cpp)

# Wire the database wrapper (SQLiteCpp) and base SQLite (sqlite3) into the executable
target_link_libraries(KineticRail PRIVATE KineticRail_Core SQLiteCpp sqlite3)

# ---------------------------------------------------------
# 4. Unit Testing (Validation)
# ---------------------------------------------------------
enable_testing()
# find_package(GTest CONFIG REQUIRED)
# add_executable(KineticRail_Tests tests/test_physics.cpp)
# target_link_libraries(KineticRail_Tests PRIVATE KineticRail_Core GTest::gtest_main)
# add_test(NAME PhysicsValidation COMMAND KineticRail_Tests)