#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "transmat4.h"
#include <cmath>
using namespace std;
#define RADIANS(x) (x*3.14159f/180.0f)

namespace curiosity {

    class Camera
    {
    public:
        Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f),
               vec3 worldUp = vec3(0.0f, 1.0f, 0.0f),
               float pitch = 0.0f, float yaw = -90.0f);

        inline vec3 getPosition() {
            return position_;
        }

        TransMat4 getViewMatrix();

        inline void setMoveSpeed(float v) {
            moveSpeed_ = v;
        }

        enum MoveDirection {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        inline void setMouseSensitivity(float v) {
            mouseSensitivity_ = v;
        }
        void processKeyboard(MoveDirection direction);

        void processMouseMove(float xOffset, float yOffset);

    private:
        void updateCameraVectors();

    private:
        vec3 position_;
        vec3 front_;
        vec3 worldUp_;
        vec3 up_;
        vec3 right_;
        float pitch_;
        float yaw_;
        float moveSpeed_;
        float mouseSensitivity_;
    };

}

#endif // CAMERA_H
