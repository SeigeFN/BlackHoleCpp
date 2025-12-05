#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

int main() {
	//key variables
	int width = 800;
	int height = 600;

	//initialize GLFW (windows and inputs)
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW\n";
		return -1;
	}

	//set OpenGL version (3.3 core)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//other window hints
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//create window
	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Test", NULL, NULL);
	if (!window) {
	std::cout << "Failed to create window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//load openGL functions through glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	//set viewport and callback
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
