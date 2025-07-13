#pragma once
#include <string>
#include "Renderer.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
class Input
{
public:
	static float GetInputAxis2D(GLFWwindow* window, const std::string axis);
	static void MoveCamera(GLFWwindow* window, Camera& camera, const float speed);
};