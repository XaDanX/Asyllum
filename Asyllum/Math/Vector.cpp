//
// Created by XaDanX on 3/4/2023.
//
#include "Vector.h"

struct ProjectionInfo {
    bool IsOnSegment;
    Vector3 LinePoint;
    Vector3 SegmentPoint;

    ProjectionInfo(bool is_on_segment, Vector3 const& segment_point, Vector3 const& line_point);
};

ProjectionInfo::ProjectionInfo(const bool is_on_segment, Vector3 const& segment_point, Vector3 const& line_point) :
        IsOnSegment(is_on_segment), LinePoint(line_point), SegmentPoint(segment_point)
{}

Vector3 Vector3::segment_point(const Vector3 &segment_start, const Vector3 &segment_end) {
    float rs;
    auto const cx = x;
    auto const cz = z;
    auto const ax = segment_start.x;
    auto const az = segment_start.z;
    auto const bx = segment_end.x;
    auto const bz = segment_end.z;

    auto const cy = y;
    auto const ay = segment_start.y;
    auto const by = segment_end.y;

    const auto rl = ((cx - ax) * (bx - ax) + (cz - az) * (bz - az) + (cy - ay) * (by - ay)) / (pow(bx - ax, 2) + pow(bz - az, 2) + pow(by - ay, 2));
    const auto point_line = Vector3(ax + rl * (bx - ax), ay + rl * (by - ay), az + rl * (bz - az));

    //	const auto rl = ((cx - ax) * (bx - ax) + (cz - az) * (bz - az)) / (pow(bx - ax, 2) + pow(bz - az, 2));
    //	const auto point_line = Vector3(ax + rl * (bx - ax), 0, az + rl * (bz - az));

    if (rl < 0)
    {
        rs = 0;
    }
    else if (rl > 1)
    {
        rs = 1;
    }
    else
    {
        rs = rl;
    }

    auto const is_on_segment = rs == rl;
    auto const point_segment = is_on_segment ? point_line : Vector3(ax + rs * (bx - ax), ay + rs * (by - ay), az + rs * (bz - az));
    //auto const point_segment = is_on_segment ? point_line : Vector3(ax + rs * (bx - ax), 0, az + rs * (bz - az));

    return point_segment;
}
