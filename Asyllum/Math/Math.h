//
// Created by XaDanX on 12/1/2022.
//

#ifndef ASYLLUM_MATH_H
#define ASYLLUM_MATH_H

namespace {
    void MultiplySquareMatrices(float* output, float* a, float* b) {
        int size = 4 * 4;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.f;
                for (int k = 0; k < 4; k++)
                    sum = sum + a[i * 4 + k] * b[k * 4 + j];
                output[i * 4 + j] = sum;
            }
        }
    }

    float PerpedincularDistToSegment(Vector2 p, Vector2 s1, Vector2 s2) {
        auto px = s2.x - s1.x;
        auto py = s2.y - s1.y;

        auto norm = (px*px) + (py*py);

        auto u = ((p.x - s1.x) * px + (p.y - s1.y) * py) / (float)norm;

        if (u > 1)
            u = 1;
        else if (u < 0)
            u = 0;

        auto x = s1.x + u * px;
        auto y = s1.y + u * py;

        auto dx = x - p.x;
        auto dy = y - p.y;

        return static_cast<float>(std::pow(dx*dx + dy*dy, 0.5));

    }
    /*float PerpedincularDistToSegment(Vector2 p, Vector2 s1, Vector2 s2) { //p = pos s1 start s2 end // start end pos
        float cx, cy, ax, ay, bx, by;
        cx = p.x;
        cy = p.y;
        ax = s1.x;
        ay = s1.y;
        bx = s2.x;
        by = s2.y;

        auto rL = ((cx - ax) * (bx - ax) + (cy - ay) * (by - ay)) / (
                std::pow((bx - ax), 2) + std::pow((by - ay), 2)
        );
        auto pointLine = Vector3(ax + rL * (bx - ax), 0, ay + rL * (by - ay));
        auto rS = rL < 0 and 0 or (rL > 1 and 1 or rL);
        auto isOnSegment = rS == rL;

        auto pointSegment = Vector3(ax + rS * (bx - ax), 0, ay + rS * (by - ay));

        auto xy = Vector2(pointSegment.x, pointSegment.z);
        return std::pow(p.distance(xy), .5);

    }*/
}
#endif //ASYLLUM_MATH_H
