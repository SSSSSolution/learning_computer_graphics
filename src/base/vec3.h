#ifndef VEC3_H
#define VEC3_H

namespace curiosity {

    class vec3
    {
    public:
        vec3() {}

        vec3(float x, float y, float z) : x(x), y(y), z(z) {
        }

        /* 规范化 */
        vec3 normalize() const;
        /* 差 */
        vec3 operator -(const vec3 &other) const;
        /* 和　*/
        vec3 operator +(const vec3 &other) const;
        /* 数乘 */
        vec3 operator *(float v) const;
        /* 点乘 */
        float operator *(const vec3 &other) const;
        /* 叉乘 */
        vec3 cross(const vec3 &other) const;

    public:
        float x, y, z;
    };

}

#endif // VEC3_H
