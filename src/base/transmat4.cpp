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
                        0.0f, 1.0,  0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f,
                        Tx,   Ty,   Tz,   1.0f };
        TransMat4 mat(d);
        return mat;
    }

    TransMat4 TransMat4::Rotation(float Rx, float Ry, float Rz, float r)
    {
        float d[16] = { cos(r)+Rx*Rx*(1-cos(r)),    Ry*Rx*(1-cos(r))+Rz*sin(r), Rz*Rx*(1-cos(r))-Ry*sin(r), 0.0f,
                        Rx*Ry*(1-cos(r))-Rz*sin(r), cos(r)+Ry*Ry*(1-cos(r)),    Rz*Ry*(1-cos(r))+Rx*sin(r), 0.0f,
                        Rx*Rz*(1-cos(r))+Ry*sin(r), Ry*Rz*(1-cos(r))-Rx*sin(r), cos(r)+Rz*Rz*(1-cos(r)),    0.0f,
                        0.0f,                       0.0f,                       0.0f,                       1.0f };
        TransMat4 mat(d);
        return mat;
    }
}
