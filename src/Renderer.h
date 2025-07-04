#pragma once

#include <iostream>
#include <GL/glew.h>
using namespace std;

#define ASSERT(x) if(!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
    x; \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);
