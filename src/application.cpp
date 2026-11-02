#include "application.h"

#include <exception>
#include <iostream>

#include "simulation_manager.h"
#include "track.h"
#include "train.h"

namespace kineticrail {

int Application::run(int /*argc*/, char* /*argv*/[]) {
    try {
        // Placeholder values for a demo run. Replace with validated data.
        const Train train{
            "Demo freight",
            1.5e6,        // 1500 t
            300e3,        // 300 kN
            {3.0e4, 1.0e2, 10.0}  // Davis A, B, C
        };

        const Track track({
            {5000.0, 0.0,  0.0, 0.25},   // level, straight
            {2000.0, 0.01, 600.0, 0.25}  // 1% grade, 600 m curve
        });

        // Braking test: start at 25 m/s and apply a constant 200 kN service brake.
        const SimulationConfig config{0.1, 3600.0, 25.0, 200e3};

        SimulationManager manager("database/kineticrail.db", "output");
        const RunSummary s = manager.runTest("demo_brake_25mps", train, track, config);

        std::cout << "Run complete\n"
                  << "  Stopping distance: " << s.stopping_distance_m << " m\n"
                  << "  Duration:          " << s.duration_s << " s\n"
                  << "  Peak speed:        " << s.peak_speed_mps << " m/s\n"
                  << "  Came to rest:      " << (s.came_to_rest ? "yes" : "no") << '\n';
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "KineticRail error: " << e.what() << '\n';
        return 1;
    }
}

}  // namespace kineticrail