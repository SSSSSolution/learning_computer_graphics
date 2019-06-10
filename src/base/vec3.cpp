#include "vec3.h"
#include <cmath>

namespace curiosity {

    vec3 vec3::normalize() const
    {
        float sum = x*x + y*y + z*z;
        vec3 ret(x < 0 ? -1.0f * std::sqrt(x*x/sum) : std::sqrt(x*x/sum),
                 y < 0 ? -1.0f * std::sqrt(y*y/sum) : std::sqrt(y*y/sum),
                 z < 0 ? -1.0f * std::sqrt(z*z/sum) : std::sqrt(z*z/sum));
        return ret;
    }

    vec3 vec3::operator +(const vec3 &other) const
    {
        vec3 ret(x+other.x, y+other.y, z+other.z);
        return ret;
    }

    vec3 vec3::operator -(const vec3 &other) const
    {
        vec3 ret(x-other.x, y-other.y, z-other.z);
        return ret;
    }

    vec3 vec3::operator *(float v) const
    {
        vec3 ret(x*v, y*v, z*v);
        return ret;
    }

    float vec3::operator *(const vec3 &other) const
    {
        return x*other.x + y*other.y + z*other.z;
    }

    vec3 vec3::cross(const vec3 &other) const
    {
        vec3 ret(y*other.z - z*other.y,
                 z*other.x - x*other.z,
                 x*other.y - y*other.x);
        return ret;
    }

}
