#include "transmat4.h"
#include <cmath>
#include <string.h>

using namespace std;

namespace curiosity {
    namespace graphics {
        TransMat4::TransMat4() {
            for (int i = 0; i < 16; i++) {
                data[i] = 0;
            }
        }

        TransMat4::TransMat4(float *d) {
            memcpy(data, d, 16*sizeof(float));
        }

        TransMat4 TransMat4::operator *(TransMat4 &other) {
            float d[16];
            const float *od = other.d_;

            for (int j = 0; j < 4; ++j) {
                for (int i = 0; i < 4; ++i) {
                    d[j*4+i] = od[j*4+0] * data[0*4+i] +
                               od[j*4+1] * data[1*4+i] +
                               od[j*4+2] * data[2*4+i] +
                               od[j*4+3] * data[3*4+i];
                }
            }
            TransMat4 mat(d);
            return mat;
        }

        TransMat4 TransMat4::identity() {
            float d[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f };
            TransMat4 mat(d);
            return mat;
        }

        TransMat4 TransMat4::translation(float Tx, float Ty, float Tz)
        {
            float d[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            Tx,   Ty,   Tz,   1.0f };
            TransMat4 mat(d);
            return mat;
        }

        TransMat4 TransMat4::translation(Vec3 &vec3)
        {
            return translation(vec3.x_, vec3.y_, vec3.z_);
        }

        TransMat4 TransMat4::rotation(float Rx, float Ry, float Rz, float r)
        {
            float r = RADIANS(r);
            Vec3 norm = Vec3(Rx, Ry, Rz).normalize();
            float x = norm.x_;
            float y = norm.y_;
            float z = norm.z_;

            float d[16] = { cos(r)+x*x*(1-cos(r)),   y*x*(1-cos(r))+z*sin(r), z*x*(1-cos(r))-y*sin(r), 0.0f,
                            x*y*(1-cos(r))-z*sin(r), cos(r)+y*y*(1-cos(r)),   z*y*(1-cos(r))+x*sin(r), 0.0f,
                            x*z*(1-cos(r))+y*sin(r), y*z*(1-cos(r))-x*sin(r), cos(r)+z*z*(1-cos(r)),   0.0f,
                            0.0f,                    0.0f,                    0.0f,                    1.0f };
            TransMat4 mat(d);
            return d;
        }

        TransMat4 TransMat4::rotation(Vec3 &vec3, float r)
        {
            return rotation(vec3.x_, vec3.y_, vec3.z_, r);
        }

        TransMat4 TransMat4::projection(float aspect, float fov, float zNear, float zFar)
        {
            fov = RADIANS(fov);
            float d[16] = { 1.0f/(aspect*tan(fov/2.0f)),    0.0f,     0.0f,    0.0f,
                            0.0f,  1.0f/tan(fov/2.0f),      0.0f,              0.0f,
                            0.0f,  0.0f,  (-1.0f*zFar - zNear)/(zNear - zFar), 1.0f,
                            0.0f,  0.0f,  (2*zNear*zFar)/(zNear-zFar),         0.0f };
    //        float d[16] = { 1.0f/(aspect*tan(fov/2.0f)),    0.0f,     0.0f,    0.0f,
    //                        0.0f,  1.0f/tan(fov/2.0f),      0.0f,              0.0f,
    //                        0.0f,  0.0f,  (zFar)/(zFar-zNear), 1.0f,
    //                        0.0f,  0.0f,  (zNear*zFar)/(zNear-zFar),         0.0f };
            TransMat4 mat(d);
            return mat;
        }

        TransMat4 TransMat4::lookAt(const Vec3 &position, const Vec3 &front, const Vec3 &up)
        {
            Vec3 zaxis = front.normalize();
            Vec3 xaxis = zaxis.cross(up).normalize();
            Vec3 yaxis = xaxis.cross(zaxis);

            float d[16];
            d[0] = xaxis.x_;
            d[4] = xaxis.y_;
            d[8] = xaxis.z_;
            d[1] = yaxis.x_;
            d[5] = yaxis.y_;
            d[9] = yaxis.z_;
            d[2] = zaxis.x_;
            d[6] = zaxis.y_;
            d[10] = zaxis.z_;
            d[15] = 1.0f;
            d[3]=d[7]=d[11]=d[12]=d[13]=d[14]=0.0f;

            TransMat4 mat1(d);

            TransMat4 mat2 = TransMat4::identity();
            mat2.data[12] =  -1.0f * position.x_;
            mat2.data[13] =  -1.0f * position.y_;
            mat2.data[14] =  -1.0f * position.z_;

            return mat1*mat2;
        }
    }
}
































