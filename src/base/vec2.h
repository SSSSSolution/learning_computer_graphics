#ifndef VEC2_H
#define VEC2_H

namespace curiosity {

    class vec2
    {
    public:
        vec2() {}
        vec2(float x, float y)
            :x_(x), y_(y) {
        }

    public:
        float x_, y_;
    };

}

#endif // VEC2_H
