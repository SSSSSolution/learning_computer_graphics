#include "transmat4.h"
#include <cmath>
#include <string.h>

using namespace std;
namespace curiosity {

    TransMat4::TransMat4(float *d)
    {
        memcpy(data, d, 16*sizeof(float));
    }

    TransMat4 TransMat4::Translation(float Tx, float Ty, float Tz)
    {
        float d[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        Tx,   Ty,   Tz,   1.0f };
        TransMat4 mat(d);
        return mat;
    }

    TransMat4 TransMat4::Rotation(float Rx, float Ry, float Rz, float r)
    {
        float sum = Rx*Rx + Ry*Ry + Rz*Rz;
        float x = sqrt(Rx*Rx/sum);
        float y = sqrt(Ry*Ry/sum);
        float z = sqrt(Rz*Rz/sum);

        float d[16] = { cos(r)+x*x*(1-cos(r)),   y*x*(1-cos(r))+z*sin(r), z*x*(1-cos(r))-y*sin(r), 0.0f,
                        x*y*(1-cos(r))-z*sin(r), cos(r)+y*y*(1-cos(r)),   z*y*(1-cos(r))+x*sin(r), 0.0f,
                        x*z*(1-cos(r))+y*sin(r), y*z*(1-cos(r))-x*sin(r), cos(r)+z*z*(1-cos(r)),   0.0f,
                        0.0f,                    0.0f,                    0.0f,                    1.0f };
        TransMat4 mat(d);
        return mat;
    }

    TransMat4 TransMat4::Projection(float aspect, float fov, float zNear, float zFar)
    {
        float d[16] = { 1.0f/(aspect*tan(fov/2.0f)),    0.0f,     0.0f,    0.0f,
                        0.0f,  1.0f/tan(fov/2.0f),      0.0f,              0.0f,
                        0.0f,  0.0f,  (-1.0f*zFar - zNear)/(zNear - zFar), 1.0f,
                        0.0f,  0.0f,  (2*zNear*zFar)/(zNear-zFar),         0.0f };
        TransMat4 mat(d);
        return mat;
    }

    TransMat4 TransMat4::Identity()
    {
        float d[16] = { 1.0f, 0.0f, 0.0f, 0.0f,
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, 0.0f, 1.0f };
        TransMat4 mat(d);
        return mat;
    }

    TransMat4 TransMat4::operator *(TransMat4 &other)
    {
        float d[16];
        const float *od = other.dataPtr();

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
}

















