//
// Created by XaDanX on 2/24/2023.
//

#ifndef ASYLLUM_GEOMETRY_H
#define ASYLLUM_GEOMETRY_H
#pragma once

#pragma warning (disable : 4244 4018)

#include "Clipper.h"
#include "Vector.h"
#include <vector>

namespace Geometry {
    class Polygon {
    public:
        std::vector<Vector3> points;

        void Add(const Vector3& point) {
            points.push_back(point);
        }

        bool IsInside(const Vector3& point) {
            return !IsOutside(point);
        }

        bool IsOutside(const Vector3& point) {
            const auto p = ClipperLib::IntPoint(point.x, point.z);
            return ClipperLib::PointInPolygon(p, ToClipperPath()) != 1;
        }

        int PointInPolygon(const Vector3& point) {
            const auto p = ClipperLib::IntPoint(point.x, point.z);
            return ClipperLib::PointInPolygon(p, ToClipperPath());
        }

        std::vector<ClipperLib::IntPoint> ToClipperPath() {
            std::vector<ClipperLib::IntPoint> result;

            for (const auto& point : points)
                result.emplace_back(point.x, point.z);

            return result;
        }
    };

    class Rectangle {
    public:
        Vector3 direction;
        Vector3 perpendicular;
        Vector3 startPos;
        Vector3 endPos;
        float width;

        Rectangle(const Vector3& start, const Vector3& end, float widthStart) {
            startPos = start;
            endPos = end;
            width = widthStart;
            direction = end.sub(start).normalize();
            perpendicular = direction.perpendicular();
        }

        Polygon ToPolygon(int offset = 0, float overridewidth = -1) {
            Polygon result = Polygon();

            result.Add(startPos.add(
                    perpendicular.mult(overridewidth > 0 ? overridewidth : width + offset).sub(
                            direction.mult(offset))));
            result.Add(startPos.sub(
                    perpendicular.mult(overridewidth > 0 ? overridewidth : width + offset).sub(
                            direction.mult(offset))));
            result.Add(endPos.sub(
                    perpendicular.mult(overridewidth > 0 ? overridewidth : width + offset).add(
                            direction.mult(offset))));
            result.Add(endPos.add(
                    perpendicular.mult(overridewidth > 0 ? overridewidth : width + offset).add(
                            direction.mult(offset))));

            return result;
        }
    };
}

#endif //ASYLLUM_GEOMETRY_H
