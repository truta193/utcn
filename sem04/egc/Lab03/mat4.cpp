#include "mat4.h"

namespace egc {
    mat4 &mat4::operator=(const mat4 &srcMatrix) {
        std::copy(srcMatrix.matrixData, srcMatrix.matrixData + 16, matrixData);
        return *this;
    }

    mat4 mat4::operator*(float scalarValue) const {
        mat4 ret;

        for (int i = 0; i < 16; i++) {
            ret.matrixData[i] = matrixData[i] * scalarValue;
        }

        return ret;
    }

    mat4 mat4::operator*(const mat4& srcMatrix) const {
        mat4 result;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                float sum = 0.0f;
                for (int k = 0; k < 4; ++k) {
                    sum += matrixData[i + k * 4] * srcMatrix.matrixData[k + j * 4];
                }
                result.matrixData[i + j * 4] = sum;
            }
        }
        return result;
    }

    vec4 mat4::operator*(const vec4& srcVector) const {
        return {
                matrixData[0] * srcVector.x + matrixData[4] * srcVector.y + matrixData[8] * srcVector.z + matrixData[12] * srcVector.w,
                matrixData[1] * srcVector.x + matrixData[5] * srcVector.y + matrixData[9] * srcVector.z + matrixData[13] * srcVector.w,
                matrixData[2] * srcVector.x + matrixData[6] * srcVector.y + matrixData[10] * srcVector.z + matrixData[14] * srcVector.w,
                matrixData[3] * srcVector.x + matrixData[7] * srcVector.y + matrixData[11] * srcVector.z + matrixData[15] * srcVector.w
        };
    }

    mat4 mat4::operator+(const mat4 &srcMatrix) const {
        mat4 ret;

        for (int i = 0; i < 16; i++) {
            ret.matrixData[i] = matrixData[i] + srcMatrix.matrixData[i];
        }

        return ret;
    }

    //get element by (row, column)
    float &mat4::at(int i, int j) {
        return matrixData[i * 4 + j];
    }

    const float &mat4::at(int i, int j) const {
        return matrixData[i * 4 + j];
    }

    float mat4::determinant() const {
        return matrixData[0] *
               (matrixData[5] * matrixData[10] * matrixData[15] + matrixData[6] * matrixData[11] * matrixData[13] +
                matrixData[7] * matrixData[9] * matrixData[14] - matrixData[7] * matrixData[10] * matrixData[13] -
                matrixData[6] * matrixData[9] * matrixData[15] - matrixData[5] * matrixData[11] * matrixData[14]) -
               matrixData[1] *
               (matrixData[4] * matrixData[10] * matrixData[15] + matrixData[6] * matrixData[11] * matrixData[12] +
                matrixData[7] * matrixData[8] * matrixData[14] - matrixData[7] * matrixData[10] * matrixData[12] -
                matrixData[6] * matrixData[8] * matrixData[15] - matrixData[4] * matrixData[11] * matrixData[14]) +
               matrixData[2] *
               (matrixData[4] * matrixData[9] * matrixData[15] + matrixData[5] * matrixData[11] * matrixData[12] +
                matrixData[7] * matrixData[8] * matrixData[13] - matrixData[7] * matrixData[9] * matrixData[12] -
                matrixData[5] * matrixData[8] * matrixData[15] - matrixData[4] * matrixData[11] * matrixData[13]) -
               matrixData[3] *
               (matrixData[4] * matrixData[9] * matrixData[14] + matrixData[5] * matrixData[10] * matrixData[12] +
                matrixData[6] * matrixData[8] * matrixData[13] - matrixData[6] * matrixData[9] * matrixData[12] -
                matrixData[5] * matrixData[8] * matrixData[14] - matrixData[4] * matrixData[10] * matrixData[13]);
    }

    mat4 mat4::inverse() const {
        mat4 inv;

        float det = determinant();
        if (det == 0) {
            return inv;
        }

        inv.matrixData[0] = matrixData[5] * matrixData[10] * matrixData[15] -
                            matrixData[5] * matrixData[11] * matrixData[14] -
                            matrixData[9] * matrixData[6] * matrixData[15] +
                            matrixData[9] * matrixData[7] * matrixData[14] +
                            matrixData[13] * matrixData[6] * matrixData[11] -
                            matrixData[13] * matrixData[7] * matrixData[10];

        inv.matrixData[4] = -matrixData[4] * matrixData[10] * matrixData[15] +
                            matrixData[4] * matrixData[11] * matrixData[14] +
                            matrixData[8] * matrixData[6] * matrixData[15] -
                            matrixData[8] * matrixData[7] * matrixData[14] -
                            matrixData[12] * matrixData[6] * matrixData[11] +
                            matrixData[12] * matrixData[7] * matrixData[10];

        inv.matrixData[8] = matrixData[4] * matrixData[9] * matrixData[15] -
                            matrixData[4] * matrixData[11] * matrixData[13] -
                            matrixData[8] * matrixData[5] * matrixData[15] +
                            matrixData[8] * matrixData[7] * matrixData[13] +
                            matrixData[12] * matrixData[5] * matrixData[11] -
                            matrixData[12] * matrixData[7] * matrixData[9];

        inv.matrixData[12] = -matrixData[4] * matrixData[9] * matrixData[14] +
                             matrixData[4] * matrixData[10] * matrixData[13] +
                             matrixData[8] * matrixData[5] * matrixData[14] -
                             matrixData[8] * matrixData[6] * matrixData[13] -
                             matrixData[12] * matrixData[5] * matrixData[10] +
                             matrixData[12] * matrixData[6] * matrixData[9];

        inv.matrixData[1] = -matrixData[1] * matrixData[10] * matrixData[15] +
                            matrixData[1] * matrixData[11] * matrixData[14] +
                            matrixData[9] * matrixData[2] * matrixData[15] -
                            matrixData[9] * matrixData[3] * matrixData[14] -
                            matrixData[13] * matrixData[2] * matrixData[11] +
                            matrixData[13] * matrixData[3] * matrixData[10];

        inv.matrixData[5] = matrixData[0] * matrixData[10] * matrixData[15] -
                            matrixData[0] * matrixData[11] * matrixData[14] -
                            matrixData[8] * matrixData[2] * matrixData[15] +
                            matrixData[8] * matrixData[3] * matrixData[14] +
                            matrixData[12] * matrixData[2] * matrixData[11] -
                            matrixData[12] * matrixData[3] * matrixData[10];

        inv.matrixData[9] = -matrixData[0] * matrixData[9] * matrixData[15] +
                            matrixData[0] * matrixData[11] * matrixData[13] +
                            matrixData[8] * matrixData[1] * matrixData[15] -
                            matrixData[8] * matrixData[3] * matrixData[13] -
                            matrixData[12] * matrixData[1] * matrixData[11] +
                            matrixData[12] * matrixData[3] * matrixData[9];

        inv.matrixData[13] = matrixData[0] * matrixData[9] * matrixData[14] -
                             matrixData[0] * matrixData[10] * matrixData[13] -
                             matrixData[8] * matrixData[1] * matrixData[14] +
                             matrixData[8] * matrixData[2] * matrixData[13] +
                             matrixData[12] * matrixData[1] * matrixData[10] -
                             matrixData[12] * matrixData[2] * matrixData[9];

        inv.matrixData[2] = matrixData[1] * matrixData[6] * matrixData[15] -
                            matrixData[1] * matrixData[7] * matrixData[14] -
                            matrixData[5] * matrixData[2] * matrixData[15] +
                            matrixData[5] * matrixData[3] * matrixData[14] +
                            matrixData[13] * matrixData[2] * matrixData[7] -
                            matrixData[13] * matrixData[3] * matrixData[6];

        inv.matrixData[6] = -matrixData[0] * matrixData[6] * matrixData[15] +
                            matrixData[0] * matrixData[7] * matrixData[14] +
                            matrixData[4] * matrixData[2] * matrixData[15] -
                            matrixData[4] * matrixData[3] * matrixData[14] -
                            matrixData[12] * matrixData[2] * matrixData[7] +
                            matrixData[12] * matrixData[3] * matrixData[6];

        inv.matrixData[10] = matrixData[0] * matrixData[5] * matrixData[15] -
                             matrixData[0] * matrixData[7] * matrixData[13] -
                             matrixData[4] * matrixData[1] * matrixData[15] +
                             matrixData[4] * matrixData[3] * matrixData[13] +
                             matrixData[12] * matrixData[1] * matrixData[7] -
                             matrixData[12] * matrixData[3] * matrixData[5];

        inv.matrixData[14] = -matrixData[0] * matrixData[5] * matrixData[14] +
                             matrixData[0] * matrixData[6] * matrixData[13] +
                             matrixData[4] * matrixData[1] * matrixData[14] -
                             matrixData[4] * matrixData[2] * matrixData[13] -
                             matrixData[12] * matrixData[1] * matrixData[6] +
                             matrixData[12] * matrixData[2] * matrixData[5];

        inv.matrixData[3] = -matrixData[1] * matrixData[6] * matrixData[11] +
                            matrixData[1] * matrixData[7] * matrixData[10] +
                            matrixData[5] * matrixData[2] * matrixData[11] -
                            matrixData[5] * matrixData[3] * matrixData[10] -
                            matrixData[9] * matrixData[2] * matrixData[7] +
                            matrixData[9] * matrixData[3] * matrixData[6];

        inv.matrixData[7] = matrixData[0] * matrixData[6] * matrixData[11] -
                            matrixData[0] * matrixData[7] * matrixData[10] -
                            matrixData[4] * matrixData[2] * matrixData[11] +
                            matrixData[4] * matrixData[3] * matrixData[10] +
                            matrixData[8] * matrixData[2] * matrixData[7] -
                            matrixData[8] * matrixData[3] * matrixData[6];

        inv.matrixData[11] = -matrixData[0] * matrixData[5] * matrixData[11] +
                             matrixData[0] * matrixData[7] * matrixData[9] +
                             matrixData[4] * matrixData[1] * matrixData[11] -
                             matrixData[4] * matrixData[3] * matrixData[9] -
                             matrixData[8] * matrixData[1] * matrixData[7] +
                             matrixData[8] * matrixData[3] * matrixData[5];

        inv.matrixData[15] = matrixData[0] * matrixData[5] * matrixData[10] -
                             matrixData[0] * matrixData[6] * matrixData[9] -
                             matrixData[4] * matrixData[1] * matrixData[10] +
                             matrixData[4] * matrixData[2] * matrixData[9] +
                             matrixData[8] * matrixData[1] * matrixData[6] -
                             matrixData[8] * matrixData[2] * matrixData[5];

        for (float &i : inv.matrixData) {
            i /= det;
        }

        return inv;
    }

    mat4 mat4::transpose() const {
        mat4 ret;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                ret.matrixData[i * 4 + j] = matrixData[j * 4 + i];
            }
        }

        return ret;
    }
}