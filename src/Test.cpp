//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <assert.h>
//using namespace std;
//
//#include "Renderer.h"
//
//#include "VertexBuffer.h"
//#include "IndexBuffer.h" 
//#include "VertexArray.h"
//
//string ReadFileToString(const string& filePath)
//{
//    ifstream file(filePath);
//    if (!file.is_open()) cout << "ERROR WHILE TRYING TO OPEN A FILE (ReadFileToString)" << endl;
//    stringstream buffer;
//    buffer << file.rdbuf();
//    return buffer.str();
//}
//
//static unsigned int CompileShader(unsigned int type, const string& source)
//{
//    unsigned int id = glCreateShader(type);
//    const char* src = source.c_str();
//    // The second parameter indicates how many strings will be in the array of the source
//    // The second one, if it's nullptr, indicates that the strings of the array will be null terminated
//    GLCall(glShaderSource(id, 1, &src, nullptr));
//    GLCall(glCompileShader(id));
//
//    int result;
//    // glGetShaderiv returns a parameter from a shader object. In this case the parameter will be stored in result
//    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//    if (result == GL_FALSE)
//    {
//        int length;
//        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
//        char* message = (char*)alloca(length * sizeof(char));
//        GLCall(glGetShaderInfoLog(id, length, &length, message));
//        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader! " << endl;
//        cout << message << endl;
//        GLCall(glDeleteShader(id));
//        return 0;
//    }
//
//    return id;
//}
//
//static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader)
//{
//    unsigned int program = glCreateProgram();
//    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    // A program is a group of glsl that can run on the GPU
//    GLCall(glAttachShader(program, vs));
//    GLCall(glAttachShader(program, fs));
//    GLCall(glLinkProgram(program));
//    GLCall(glValidateProgram(program));
//
//    GLCall(glDeleteShader(vs));
//    GLCall(glDeleteShader(fs));
//
//    return program;
//}
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    {
//        float positions[] =
//        {
//            -0.5f, -0.5f, // 0 
//            0.5f, -0.5f, // 1
//            0.5f, 0.5f, // 2
//            -0.5f, 0.5f, // 3
//        };
//
//        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//        /* Create a windowed mode window and its OpenGL context */
//        if (!window)
//        {
//            glfwTerminate();
//            return -1;
//        }
//
//        /* Make the window's context current */
//        glfwMakeContextCurrent(window);
//
//        glfwSwapInterval(1);
//
//        if (glewInit() != GLEW_OK)
//        {
//            cout << "Error!" << endl;
//        }
//        vector<float> xySurface;
//
//        float vertexCount = 60.0;
//        float vertexStep = 2.0 / (vertexCount - 1.0);
//
//        for (int row = 0.0; row < vertexCount; ++row)
//        {
//            for (int column = 0.0; column < vertexCount; ++column)
//            {
//                xySurface.push_back(-1.0+ column * vertexStep);
//                xySurface.push_back(-1.0+ row * vertexStep);
//            }
//        }
//
//        float* surface = new float[xySurface.size()];
//        copy(xySurface.begin(), xySurface.end(), surface);
//
//        VertexArray va;
//        VertexBuffer vb(surface, xySurface.size()*sizeof(float));
//
//        VertexBufferLayout layout;
//        layout.Push<float>(2);
//        va.AddBuffer(vb, layout);
//
//
//        string vertexShader = ReadFileToString("res/shaders/BasicVertex.glsl");
//        string fragmentShader = ReadFileToString("res/shaders/BasicFragment.glsl");
//
//        unsigned int shader = CreateShader(vertexShader, fragmentShader);
//        GLCall(glUseProgram(shader));
//
//        GLCall(int location = glGetUniformLocation(shader, "u_Color"));
//        ASSERT(location != -1);
//        GLCall(glUniform4f(location, 0.7f, 0.1f, 0.4f, 1.0));
//
//        GLCall(glBindVertexArray(0));
//        GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
//        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//        GLCall(glUseProgram(0));
//
//        float r = 0;
//        float speed = 0.01f;
//        float step = 0.1f;
//
//        while (!glfwWindowShouldClose(window))
//        {
//            glClear(GL_COLOR_BUFFER_BIT);
//
//            GLCall(glUseProgram(shader));
//
//            va.Bind();
//
//            GLCall(glDrawArrays(GL_POINTS, 0, xySurface.size()/2));
//
//            glfwSwapBuffers(window);
//
//            glfwPollEvents();
//        }
//
//        glDeleteProgram(shader);
//    }
//    glfwTerminate();
//    return 0;
//}