#include "vec3.h"

namespace egc {

    vec3 &vec3::operator=(const vec3 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;

        return *this;
    }

    vec3 vec3::operator+(const vec3 &srcVector) const {
        vec3 ret;
        ret.x = this->x + srcVector.x;
        ret.y = this->y + srcVector.y;
        ret.z = this->z + srcVector.z;

        return ret;
    }

    vec3 &vec3::operator+=(const vec3 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;

        return *this;
    }

    vec3 vec3::operator*(float scalarValue) const {
        vec3 ret;

        ret.x = this->x * scalarValue;
        ret.y = this->y * scalarValue;
        ret.z = this->z * scalarValue;

        return ret;
    }

    vec3 vec3::operator-(const vec3 &srcVector) const {
        vec3 ret;
        ret.x = this->x - srcVector.x;
        ret.y = this->y - srcVector.y;
        ret.z = this->z - srcVector.z;

        return ret;
    }

    vec3 &vec3::operator-=(const vec3 &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;

        return *this;
    }

    vec3 vec3::operator-() const {
        vec3 ret;
        ret.x = -this->x;
        ret.y = -this->y;
        ret.z = -this->z;

        return ret;
    }

    float vec3::length() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    vec3 &vec3::normalize() {
        float length = this->length();
        this->x /= length;
        this->y /= length;
        this->z /= length;

        return *this;
    }

    float dotProduct(const vec3 &v1, const vec3 &v2) {
        return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    }

    vec3 crossProduct(const vec3 &v1, const vec3 &v2) {
        vec3 ret;
        ret.x = v1.y * v2.z - v1.z * v2.y;
        ret.y = v1.z * v2.x - v1.x * v2.z;
        ret.z = v1.x * v2.y - v1.y * v2.x;

        return ret;
    }
}
