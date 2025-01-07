#include "mat3.h"

namespace egc {
    mat3 &mat3::operator=(const mat3 &srcMatrix) {
        std::copy(srcMatrix.matrixData, srcMatrix.matrixData + 9, matrixData);
        return *this;
    }

    mat3 mat3::operator*(float scalarValue) const {
        mat3 ret;
        for (int i = 0; i < 9; i++) {
            ret.matrixData[i] = matrixData[i] * scalarValue;
        }
        return ret;
    }

    mat3 mat3::operator*(const mat3& srcMatrix) const {
        mat3 result;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                float sum = 0.0f;
                for (int k = 0; k < 3; ++k) {
                    sum += matrixData[i + k * 3] * srcMatrix.matrixData[k + j * 3];
                }
                result.matrixData[i + j * 3] = sum;
            }
        }
        return result;
    }

    vec3 mat3::operator*(const vec3& srcVector) const {
        return vec3(
                matrixData[0] * srcVector.x + matrixData[3] * srcVector.y + matrixData[6] * srcVector.z,
                matrixData[1] * srcVector.x + matrixData[4] * srcVector.y + matrixData[7] * srcVector.z,
                matrixData[2] * srcVector.x + matrixData[5] * srcVector.y + matrixData[8] * srcVector.z
        );
    }

    mat3 mat3::operator+(const mat3 &srcMatrix) const {
        mat3 ret;
        for (int i = 0; i < 9; i++) {
            ret.matrixData[i] = matrixData[i] + srcMatrix.matrixData[i];
        }
        return ret;
    }

    float &mat3::at(int i, int j) {
        return matrixData[i * 3 + j];
    }

    const float &mat3::at(int i, int j) const {
        return matrixData[i * 3 + j];
    }

    float mat3::determinant() const {
        return matrixData[0] * (matrixData[4] * matrixData[8] - matrixData[5] * matrixData[7]) -
               matrixData[1] * (matrixData[3] * matrixData[8] - matrixData[5] * matrixData[6]) +
               matrixData[2] * (matrixData[3] * matrixData[7] - matrixData[4] * matrixData[6]);
    }

    mat3 mat3::inverse() const {
        mat3 ret;

        float det = determinant();
        if (det == 0) {
            return ret;
        }

        ret.matrixData[0] = (matrixData[4] * matrixData[8] - matrixData[5] * matrixData[7]) / det;
        ret.matrixData[1] = (matrixData[2] * matrixData[7] - matrixData[1] * matrixData[8]) / det;
        ret.matrixData[2] = (matrixData[1] * matrixData[5] - matrixData[2] * matrixData[4]) / det;
        ret.matrixData[3] = (matrixData[5] * matrixData[6] - matrixData[3] * matrixData[8]) / det;
        ret.matrixData[4] = (matrixData[0] * matrixData[8] - matrixData[2] * matrixData[6]) / det;
        ret.matrixData[5] = (matrixData[2] * matrixData[3] - matrixData[0] * matrixData[5]) / det;
        ret.matrixData[6] = (matrixData[3] * matrixData[7] - matrixData[4] * matrixData[6]) / det;
        ret.matrixData[7] = (matrixData[1] * matrixData[6] - matrixData[0] * matrixData[7]) / det;
        ret.matrixData[8] = (matrixData[0] * matrixData[4] - matrixData[1] * matrixData[3]) / det;

        return ret;
    }

    mat3 mat3::transpose() const {
        mat3 ret;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ret.matrixData[i * 3 + j] = matrixData[j * 3 + i];
            }
        }

        return ret;
    }
}