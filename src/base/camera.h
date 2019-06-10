#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"

namespace curiosity {

    class Camera
    {
    public:
        Camera() {}

        Camera(vec3 &p, vec3 &f, vec3 &u)
            : pos(p), front(f), up(u) {
        }

        inline vec3 getPos() {
            return pos;
        }
        inline vec3 getFront() {
            return front;
        }
        inline vec3 getUp() {
            return up;
        }
        inline void setPos(const vec3 &v) {
            pos = v;
        }
        inline void setFront(const vec3 &v) {
            front = v;
        }
        inline void setUp(const vec3 &v) {
            up = v;
        }

    private:
        vec3 pos;
        vec3 front;
        vec3 up;
    };

}

#endif // CAMERA_H
