#ifndef TRANSFORMMATRIX_H
#define TRANSFORMMATRIX_H
#include <string.h>

namespace curiosity {
    class TransMat4
    {
    public:
        static TransMat4 Translation(float Tx, float Ty, float Tz);
        static TransMat4 Rotation(float Rx, float Ry, float Rz, float r);

        inline const float *dataPtr() {
            return (const float *)data;
        }

    private:
        TransMat4(float *d);

    private:
        float data[16];
    };
}

#endif // TRANSFORMMATRIX_H
