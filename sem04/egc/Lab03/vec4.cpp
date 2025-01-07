#include "vec4.h"

namespace egc {

    vec4 &vec4::operator=(const vec4 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;
        this->z = srcVector.z;
        this->w = srcVector.w;

        return *this;
    }

    vec4 vec4::operator+(const vec4 &srcVector) const {
        vec4 ret;
        ret.x = this->x + srcVector.x;
        ret.y = this->y + srcVector.y;
        ret.z = this->z + srcVector.z;
        ret.w = this->w + srcVector.w;

        return ret;
    }

    vec4 &vec4::operator+=(const vec4 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;
        this->z += srcVector.z;
        this->w += srcVector.w;

        return *this;
    }

    vec4 vec4::operator*(float scalarValue) const {
        vec4 ret;

        ret.x = this->x * scalarValue;
        ret.y = this->y * scalarValue;
        ret.z = this->z * scalarValue;
        ret.w = this->w * scalarValue;

        return ret;
    }

    vec4 vec4::operator-(const vec4 &srcVector) const {
        vec4 ret;
        ret.x = this->x - srcVector.x;
        ret.y = this->y - srcVector.y;
        ret.z = this->z - srcVector.z;
        ret.w = this->w - srcVector.w;

        return ret;
    }

    vec4 &vec4::operator-=(const vec4 &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;
        this->z -= srcVector.z;
        this->w -= srcVector.w;

        return *this;
    }

    vec4 vec4::operator-() const {
        vec4 ret;
        ret.x = -this->x;
        ret.y = -this->y;
        ret.z = -this->z;
        ret.w = -this->w;

        return ret;
    }

    float vec4::length() const {
        return sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
    }

    vec4 &vec4::normalize() {
        float length = this->length();
        this->x /= length;
        this->y /= length;
        this->z /= length;
        this->w /= length;
        return *this;
    }
}