#pragma once

#include <vector>

namespace kineticrail {

struct TrackSegment {
    double length_m;
    double grade;              // rise/run, positive = uphill
    double curve_radius_m;     // 0 = straight
    double adhesion_coefficient;
};

class Track {
public:
    explicit Track(std::vector<TrackSegment> segments);

    double totalLength() const;

    // Segment containing the given position. Throws std::out_of_range if position < 0.
    // Positions past the end return the last segment.
    const TrackSegment& segmentAt(double position_m) const;

private:
    std::vector<TrackSegment> segments_;
    double total_length_m_;
};

}  // namespace kineticrail