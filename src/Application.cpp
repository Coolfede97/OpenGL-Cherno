#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <assert.h>
using namespace std;

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h" 
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    {

        float positions[] =
        {
          // X      Y     S     T 
            -0.5f, -0.5f, 0.0f, 0.0f, // 0 
             0.5f, -0.5f, 1.0f, 0.0f,// 1
             0.5f,  0.5f, 1.0f, 1.0f,// 2
            -0.5f,  0.5f, 0.0f, 1.0f// 3
        };

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        if (glewInit() != GLEW_OK)
        {
            cout << "Error!" << endl;
        }

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        int nrAttributes;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
        cout << "Max attributes: " << nrAttributes << endl;

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        /*GLCall(glEnableVertexAttribArray(0));
        GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));*/

        // index buffer object
        IndexBuffer ib(indices, 6);

        Shader shader("res/shaders/BasicVertex.glsl", "res/shaders/BasicFragment.glsl");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.7f, 0.1f, 0.4f, 1.0);

        Texture texture("res/textures/francoKO.jpg");
        texture.Bind();
        // The second parameter is 0 because that's the slot where we've created the texture 
        // (that's why the ir no parameter in bind)
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        float r = 0.0;
        float speed = 0.01f;
        float step = 0.1f;


        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.1, 0.4, 1.0);
			
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, (float)glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            shader.SetUniformMat4f("u_model", model);

			glm::mat4 view = glm::mat4(1.0f);
			view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			shader.SetUniformMat4f("u_view", view);

                glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
            shader.SetUniformMat4f("u_projection", projection);

            renderer.Draw(va, ib, shader);

            if (r > 1.0f) step = -speed;
            else if (r < 0.0f) step = speed;
            r += step;

            glfwSwapBuffers(window);

            glfwPollEvents();
        }

    }
    glfwTerminate();
    return 0;
}