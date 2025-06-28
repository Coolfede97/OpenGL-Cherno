#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] (" << error << "): " << endl <<
            "in file: " << file << endl <<
            "in line: " << line << endl <<
            "in function: " << function << endl;

        return false;
    }
    return true;    
}

