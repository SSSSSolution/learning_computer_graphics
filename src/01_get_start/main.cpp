#include "sb7_include/sb7.h"

class my_application : public sb7::application
{
public:
	void render(double currentTime)
	{
        fprintf(stderr, "%lf\n", currentTime);
//		static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f };
        const GLfloat color[] = { (float)sin(currentTime)*0.5f + 0.5f,
                                  (float)cos(currentTime)*0.5f + 0.5f,
                                  0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, color);
	}
};

DECLARE_MAIN(my_application);
