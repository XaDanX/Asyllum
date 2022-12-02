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
}
#endif //ASYLLUM_MATH_H
