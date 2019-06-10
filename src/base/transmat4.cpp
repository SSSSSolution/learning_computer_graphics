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
        float x = Rx < 0 ? -1.0f * sqrt(Rx*Rx/sum) : sqrt(Rx*Rx/sum);
        float y = Ry < 0 ? -1.0f * sqrt(Ry*Ry/sum) : sqrt(Ry*Ry/sum);
        float z = Rz < 0 ? -1.0f * sqrt(Rz*Rz/sum) : sqrt(Rz*Rz/sum);

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

    TransMat4 TransMat4::lookAt(const vec3 &position, const vec3 &target, const vec3 &up)
    {
        vec3 direct = target - position;
        vec3 right = direct.cross(up);

        vec3 _direct = direct.normalize();
        vec3 _right = right.normalize();
        vec3 _up = up.normalize();

        float d[16];
        d[0] = _right.x;
        d[4] = _right.y;
        d[8] = _right.z;
        d[1] = _up.x;
        d[5] = _up.y;
        d[9] = _up.z;
        d[2] = _direct.x;
        d[6] = _direct.y;
        d[10] = _direct.z;
        d[15] = 1.0f;
        d[3]=d[7]=d[11]=d[12]=d[13]=d[14]=0.0f;

        TransMat4 mat1(d);

        TransMat4 mat2 = TransMat4::Identity();
        mat2.data[12] = 1.0f * -1.0f * position.x;
        mat2.data[13] = 1.0f * -1.0f * position.y;
        mat2.data[14] = 1.0f * -1.0f * position.z;

        return mat1*mat2;
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

















