#include "vec2.h"

namespace egc {

    vec2 &vec2::operator=(const vec2 &srcVector) {
        this->x = srcVector.x;
        this->y = srcVector.y;

        return *this;
    }

    vec2 vec2::operator+(const vec2 &srcVector) const {
        vec2 ret;
        ret.x = this->x + srcVector.x;
        ret.y = this->y + srcVector.y;

        return ret;
    }

    vec2 &vec2::operator+=(const vec2 &srcVector) {
        this->x += srcVector.x;
        this->y += srcVector.y;

        return *this;
    }

    vec2 vec2::operator*(float scalarValue) const {
        vec2 ret;

        ret.x = this->x * scalarValue;
        ret.y = this->y * scalarValue;

        return ret;
    }

    vec2 vec2::operator-(const vec2 &srcVector) const {
        vec2 ret;
        ret.x = this->x - srcVector.x;
        ret.y = this->y - srcVector.y;

        return ret;
    }

    vec2 &vec2::operator-=(const vec2 &srcVector) {
        this->x -= srcVector.x;
        this->y -= srcVector.y;

        return *this;
    }

    vec2 vec2::operator-() const {
        vec2 ret;
        ret.x = -this->x;
        ret.y = -this->y;

        return ret;
    }

    float vec2::length() const {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    vec2 &vec2::normalize() {
        float len = this->length();
        this->x /= len;
        this->y /= len;

        return *this;
    }

    float dotProduct(const vec2 &v1, const vec2 &v2) {
        return v1.x * v2.x + v1.y * v2.y;
    }

}