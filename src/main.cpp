#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <stb/stb_image.h>
#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
//#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
//#include <vector>
#include <cmath>

#include"../BlackHoleCpp/shaderClass.h"
#include"../BlackHoleCpp/VAO.h"
#include"../BlackHoleCpp/VBO.h"
#include"../BlackHoleCpp/EBO.h"






const float pi = 3.1415926f;



//Vertices Coordinates
	//3 points that create an equilateral triangle
		//now we are making zelda logo thingy, 3 triangles
GLfloat vertices[] =
{//					Coordinates/XYZ/		/ Z	|		Colours/RGBA/		//
	- 0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.5f,	0.0f, 0.0f,	//lower left
	0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.0f,	1.0f, 0.0f,	//lower right
	0.0f,	0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	0.0f,	0.0f, 1.0f,	//middle top

	-0.25f,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.5f,	0.0f, 0.5f,	//inner left
	0.25f,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.0f,	0.5f, 0.5f,	//inner right
	0.0f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.5f,	0.5f, 0.0f	//inner middle
};
GLuint indices[] =
{
	0, 3, 5,	//Lower left triangle
	3, 2, 4,	//Upper triangle
	5, 4, 1		//Lower right triangle
};

struct Engine {
	GLFWwindow* window;
	//screen size
	int WIDTH = 800;
	int HEIGHT = 800;
	//physical area
	/*
	float widthAU = 1e11f;
	float heightAU = 7.5e10f;
	//camera
	float cameraX = 0.0f;
	float cameraY = 0.0f;
	float cameraZoom = 1.0f; //default no zoom*/

	Engine() {
		//initialize GLFW
		if (!glfwInit()) {
			std::cerr << "Failed to initialize GLFW\n";
		}

		//tell GLFW which version of OPENGL to use
		// OpenGL 3.3 with CORE profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		//initialize glfw window
		window = glfwCreateWindow(WIDTH, HEIGHT, "Black Hole Sim", NULL, NULL);
		if (!window) {
			std::cerr << "Failed to create window\n";
			glfwTerminate();
		}

		//tell GLFW to use 'window' in the context
		glfwMakeContextCurrent(window);

		//load glad
		if (!gladLoadGL()) {
			std::cout << "Failed to initialize GLAD\n";
		}
		//specifyu the viewport of OpenGL in the window
		glViewport(0, 0, WIDTH, HEIGHT);


		//set colour buffer bit
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//clean the backbuffer and assign the new colour to it
		glClear(GL_COLOR_BUFFER_BIT);
		//swap teh back buffer with the front buffer
		glfwSwapBuffers(window);


		/*
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
		}*/
	}


	void run() {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		//background colour
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//zoom
		float halfWidth = widthAU / 1.0f / cameraZoom;
		float halfHeight = heightAU / 1.0f / cameraZoom;

		//set orthographic projection
		//glOrtho(cameraX - halfWidth, cameraX + halfWidth, cameraY - halfHeight, cameraY + halfHeight, -1.0, 1.0);
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glTranslatef(-cameraX, -cameraY, 0.0f);*/
	}

	void deleteStuff() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};
Engine engine;


int main() {
	// Create Shader object using the default vertex and fragment
	Shader shaderProgram("default.vert", "default.frag");

	// Generate Vertex Array Object and bind it
	VAO VAO1;
	VAO1.Bind();

	// Generate Vertex Buffer Object and link it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate Element Buffer Object and link it to indices
	EBO EBO1(indices, sizeof(indices));

	//Links VBO1 to VAO1
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//unbind all array/buffers to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//main loop
	while (!glfwWindowShouldClose(engine.window)) {
		engine.run();

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		VAO1.Bind();
		//draw the triangle using the GL_TRIANGLES primative
			//draw triangles
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(engine.window);

		/*
		glColor3f(1.0f, 0.0f, 0.0f);
		drawCircle(3e10f, 0.0f, 2.0e10f, 40);

		glColor3f(0.0f, 0.5f, 1.0f);
		drawCircle(-3e10f, 0.0f, 2.0e10f, 40);

		glfwSwapBuffers(engine.window);

		if (glfwGetKey(engine.window, GLFW_KEY_W) == GLFW_PRESS) {
			engine.cameraY -= 1e8f; // move up
		}
		if (glfwGetKey(engine.window, GLFW_KEY_S) == GLFW_PRESS) {
			engine.cameraY += 1e8f; // move down
		}
		if (glfwGetKey(engine.window, GLFW_KEY_A) == GLFW_PRESS) {
			engine.cameraX += 1e8f; // move left
		}
		if (glfwGetKey(engine.window, GLFW_KEY_D) == GLFW_PRESS) {
			engine.cameraX -= 1e8f; // move right
		}
		if (glfwGetKey(engine.window, GLFW_KEY_UP) == GLFW_PRESS) {
			engine.cameraZoom += 0.001f; // zoom in
		}
		if (glfwGetKey(engine.window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			engine.cameraZoom -= 0.001f; // zoom out
			if (engine.cameraZoom <= 0.0f) {
				engine.cameraZoom = 0;
			}
		}

		*/
		// take care of all glfw events
		glfwPollEvents();
	}


	//close and delete shit
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	engine.deleteStuff();
	return 0;
}
