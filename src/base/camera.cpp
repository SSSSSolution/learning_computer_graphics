#include "camera.h"
#include <string.h>

namespace curiosity {

    Camera::Camera(vec3 position,vec3 worldUp,float pitch, float yaw)
        : position_(position), worldUp_(worldUp),
          pitch_(pitch), yaw_(yaw),
          moveSpeed_(1.0f), mouseSensitivity_(0.1) {
        updateCameraVectors();
    }

    TransMat4 Camera::getViewMatrix()
    {
        return TransMat4::lookAt(position_, position_+front_, up_);
    }

    void Camera::processKeyboard(MoveDirection direction)
    {
        switch (direction) {
        case FORWARD:
            position_ = position_ + front_ * moveSpeed_;
            break;
        case BACKWARD:
            position_ = position_ - front_ * moveSpeed_;
            break;
        case LEFT:
            position_ = position_ - right_ * moveSpeed_;
            break;
        case RIGHT:
            position_ = position_ + right_ * moveSpeed_;
            break;
        }
        updateCameraVectors();
    }

    void Camera::processMouseMove(float xOffset, float yOffset)
    {
        xOffset *= mouseSensitivity_;
        yOffset *= mouseSensitivity_;

        yaw_ += xOffset;
        pitch_ -= yOffset;

        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;

        updateCameraVectors();
    }


    void Camera::updateCameraVectors() {
        vec3 front;
        front.x = cos(RADIANS(yaw_))*cos(RADIANS(pitch_));
        front.y = sin(RADIANS(pitch_));
        front.z = sin(RADIANS(yaw_))*cos(RADIANS(pitch_));
        front_ = front.normalize();
        right_ = front_.cross(worldUp_);
        up_ = right_.cross(front_);
    }

}
