#include "transform.h"

namespace egc {
    //transformation matrices in 2D
    mat3 translate(const vec2 translateArray) {
        mat3 translateMatrix = mat3();
        translateMatrix.at(0, 2) = translateArray.x;
        translateMatrix.at(1, 2) = translateArray.y;
        return translateMatrix;
    };

    mat3 translate(float tx, float ty) {
        mat3 translateMatrix = mat3();
        translateMatrix.at(0, 2) = tx;
        translateMatrix.at(1, 2) = ty;
        return translateMatrix;
    };

    mat3 scale(const vec2 scaleArray) {
        mat3 scaleMatrix = mat3();
        scaleMatrix.at(0, 0) = scaleArray.x;
        scaleMatrix.at(1, 1) = scaleArray.y;
        return scaleMatrix;
    };

    mat3 scale(float sx, float sy) {
        mat3 scaleMatrix = mat3();
        scaleMatrix.at(0, 0) = sx;
        scaleMatrix.at(1, 1) = sy;
        return scaleMatrix;
    };

    mat3 rotate(float angle) {
        mat3 rotateMatrix = mat3();
        double degrees = angle * PI / 180;
        rotateMatrix.at(0, 0) = cos(degrees);
        rotateMatrix.at(0, 1) = -sin(degrees);
        rotateMatrix.at(1, 0) = sin(degrees);
        rotateMatrix.at(1, 1) = cos(degrees);
        return rotateMatrix;
    };

    //transformation matrices in 3D
    mat4 translate(const vec3 translateArray) {
        mat4 translateMatrix = mat4();
        translateMatrix.at(0, 3) = translateArray.x;
        translateMatrix.at(1, 3) = translateArray.y;
        translateMatrix.at(2, 3) = translateArray.z;
        return translateMatrix;
    };

    mat4 translate(float tx, float ty, float tz) {
        mat4 translateMatrix = mat4();
        translateMatrix.at(0, 3) = tx;
        translateMatrix.at(1, 3) = ty;
        translateMatrix.at(2, 3) = tz;
        return translateMatrix;
    };

    mat4 scale(const vec3 scaleArray) {
        mat4 scaleMatrix = mat4();
        scaleMatrix.at(0, 0) = scaleArray.x;
        scaleMatrix.at(1, 1) = scaleArray.y;
        scaleMatrix.at(2, 2) = scaleArray.z;
        return scaleMatrix;
    };

    mat4 scale(float sx, float sy, float sz) {
        mat4 scaleMatrix = mat4();
        scaleMatrix.at(0, 0) = sx;
        scaleMatrix.at(1, 1) = sy;
        scaleMatrix.at(2, 2) = sz;
        return scaleMatrix;
    };

    mat4 rotateZ(float angle) {
        mat4 rotateMatrix = mat4();
        double degrees = angle * PI / 180;
        rotateMatrix.at(0,0) = cos(degrees);
        rotateMatrix.at(0,1) = -sin(degrees);
        rotateMatrix.at(1,0) = sin(degrees);
        rotateMatrix.at(1,1) = cos(degrees);
        return rotateMatrix;
    };

    mat4 rotateY(float angle) {
        mat4 rotateMatrix = mat4();
        double degrees = angle * PI / 180;
        rotateMatrix.at(0,0) = cos(degrees);
        rotateMatrix.at(0,2) = sin(degrees);
        rotateMatrix.at(2,0) = -sin(degrees);
        rotateMatrix.at(2,2) = cos(degrees);
        return rotateMatrix;
    };

    mat4 rotateX(float angle) {
        mat4 rotateMatrix = mat4();
        double degrees = angle * PI / 180;
        rotateMatrix.at(1,1) = cos(degrees);
        rotateMatrix.at(1,2) = -sin(degrees);
        rotateMatrix.at(2,1) = sin(degrees);
        rotateMatrix.at(2,2) = cos(degrees);
        return rotateMatrix;
    };
}