#include "Input.h"

float Input::GetInputAxis2D(GLFWwindow* window, const std::string axis)
{
	float value = 0;
	if (axis == "x")
	{
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			value += 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			value -= 1.0f;
		}
		return value;
	}
	if (axis == "y")
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			value -= 1.0f;
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			value += 1.0f;
		}
		return value;
	}
	return 0;
	// Handle Error
}

void Input::MoveCamera(GLFWwindow* window, Camera& camera, const float speed)
{
	glm::vec3 camera_dir = camera.m_direction;
	glm::vec3 camera_up = camera.m_up;
	if (camera_dir == camera_up)
		cout << "Error: camera_dir and camera_up can't be equal (because it results in a NaN when normalizing their cross product)" << "\n";
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		velocity += speed * glm::normalize(glm::cross(camera_dir, camera_up));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		velocity -= speed * glm::normalize(glm::cross(camera_dir, camera_up));
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		velocity += speed * camera_dir;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		velocity -= speed * camera_dir;
	}
	camera.m_position += velocity;
}
