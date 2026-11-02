cmake_minimum_required(VERSION 3.15)

project(KineticRail VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    SQLiteCpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG 3.3.2  # pin to a released version; check the releases page
)
FetchContent_MakeAvailable(SQLiteCpp)

# ---------------------------------------------------------
# 1. Physics core: no I/O
# ---------------------------------------------------------
add_library(KineticRail_Core STATIC
    src/physics_engine.cpp
    src/train.cpp
    src/track.cpp
    src/simulation.cpp
    src/simulation_state.cpp
)
target_include_directories(KineticRail_Core PUBLIC ${CMAKE_SOURCE_DIR}/include)

# ---------------------------------------------------------
# 2. I/O layer: CSV output and SQLite logging
# ---------------------------------------------------------
add_library(KineticRail_IO STATIC
    src/result_manager.cpp
    src/database_manager.cpp
    src/simulation_manager.cpp
)
target_include_directories(KineticRail_IO PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(KineticRail_IO PUBLIC KineticRail_Core SQLiteCpp)

# ---------------------------------------------------------
# 3. Main executable
# ---------------------------------------------------------
add_executable(KineticRail
    src/main.cpp
    src/application.cpp
)
target_link_libraries(KineticRail PRIVATE KineticRail_IO)

# ---------------------------------------------------------
# 4. Unit tests (enable once GTest is set up)
# ---------------------------------------------------------
# enable_testing()
# find_package(GTest CONFIG REQUIRED)
# add_executable(KineticRail_Tests tests/physics/test_davis_resistance.cpp)
# target_link_libraries(KineticRail_Tests PRIVATE KineticRail_Core GTest::gtest_main)
# add_test(NAME PhysicsValidation COMMAND KineticRail_Tests)