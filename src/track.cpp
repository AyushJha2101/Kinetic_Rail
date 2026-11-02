#include "track.h"

#include <stdexcept>
#include <utility>

namespace kineticrail {

Track::Track(std::vector<TrackSegment> segments)
    : segments_(std::move(segments)), total_length_m_(0.0) {
    if (segments_.empty()) {
        throw std::invalid_argument("Track: at least one segment is required");
    }
    for (const auto& s : segments_) {
        if (s.length_m <= 0.0) {
            throw std::invalid_argument("Track: segment length must be > 0 m");
        }
        if (s.curve_radius_m < 0.0) {
            throw std::invalid_argument("Track: curve radius must be >= 0 m");
        }
        if (s.adhesion_coefficient <= 0.0) {
            throw std::invalid_argument("Track: adhesion coefficient must be > 0");
        }
        total_length_m_ += s.length_m;
    }
}

double Track::totalLength() const {
    return total_length_m_;
}

const TrackSegment& Track::segmentAt(double position_m) const {
    if (position_m < 0.0) {
        throw std::out_of_range("Track::segmentAt: position must be >= 0 m");
    }
    double start = 0.0;
    for (const auto& s : segments_) {
        if (position_m < start + s.length_m) {
            return s;
        }
        start += s.length_m;
    }
    return segments_.back();
}

}  // namespace kineticrail