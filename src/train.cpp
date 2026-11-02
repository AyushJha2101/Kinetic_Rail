#include "train.h"

#include <stdexcept>

namespace kineticrail {

void validateTrain(const Train& train) {
    if (train.mass_kg <= 0.0) {
        throw std::invalid_argument("Train '" + train.name + "': mass must be > 0 kg");
    }
    if (train.max_tractive_effort_N <= 0.0) {
        throw std::invalid_argument("Train '" + train.name + "': max tractive effort must be > 0 N");
    }
}

}  // namespace kineticrail