#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
//#include <vector>
#include <cmath>

#include<../BlackHoleCpp/Texture.h>
#include"../BlackHoleCpp/shaderClass.h"
#include"../BlackHoleCpp/VAO.h"
#include"../BlackHoleCpp/VBO.h"
#include"../BlackHoleCpp/EBO.h"






const float pi = 3.1415926f;



//Vertices Coordinates
	//3 points that create an equilateral triangle
		//now we are making zelda logo thingy, 3 triangles
GLfloat triangles_vertices[] =
{//					Coordinates/XYZ/		/ Z	|		Colours/RGBA/		//
	- 0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	1.0f,	0.0f, 0.0f,	//lower left
	0.5f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.0f,	1.0f, 0.0f,	//lower right
	0.0f,	0.5f * float(sqrt(3)) * 2 / 3,	0.0f,	0.0f,	0.0f, 1.0f,	//middle top

	-0.25f,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.5f,	0.0f, 0.5f,	//inner left
	0.25f,	0.5f * float(sqrt(3)) / 6,		0.0f,	0.0f,	0.5f, 0.5f,	//inner right
	0.0f,	-0.5f * float(sqrt(3)) / 3,		0.0f,	0.5f,	0.5f, 0.0f	//inner middle
};

GLuint triangles_indices[] =
{
	0, 3, 5,	//Lower left triangle
	3, 2, 4,	//Upper triangle
	5, 4, 1		//Lower right triangle
};

GLfloat vertices[] =
{//	Coordinates/XYZ/		|		Colours/RGBA/	|		TexCoord	//
	-0.5f,	0.0f,	0.5f,		1.0f,	0.0f, 0.0f,		0.0f, 0.0f,
	-0.5f,	0.0f,	-0.5f,		0.0f,	1.0f, 0.0f,		5.0f, 0.0f,
	0.5f,	0.0f,	-0.5f,		0.0f,	0.0f, 1.0f,		0.0f, 0.0f,
	0.5f,	0.0f,	0.5f,		1.0f,	1.0f, 1.0f,		5.0f, 0.0f,
	0.0f,	0.8f,	0.0f,		0.0f,	0.0f, 0.0f,		2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

struct Engine {
	GLFWwindow* window;
	//screen size
	const unsigned int WIDTH = 800;
	const unsigned int HEIGHT = 800;
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
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//unbind all array/buffers to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture
	/*int widthImg, heightImg, numColourChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("TimOpenGL.png", &widthImg, &heightImg, &numColourChannels, 0);

	if (!bytes) {
		std::cout << "STB failed: " << stbi_failure_reason() << std::endl;
	}
	else {
		std::cout << "Loaded texture: " << widthImg << "x" << heightImg << ", channels " << numColourChannels << std::endl;
	}

	//std::cout << numColourChannels << std::endl;

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);*/

	Texture TimOpenGl("TimOpenGl.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	TimOpenGl.texUnit(shaderProgram, "tex0", 0);


	float rotation = 0.0f;
	double prevTime = 0;


	//main loop
	while (!glfwWindowShouldClose(engine.window)) {
		engine.run();

		shaderProgram.Activate();

		double curTime = glfwGetTime();
		double timeDelta = curTime - prevTime;
		if (timeDelta >= (1.0 / 60.0)) {
			//std::cout << timeDelta << std::endl;
			rotation += 0.5f;
			prevTime = curTime;
		}

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(engine.WIDTH / engine.HEIGHT), 0.1f, 100.0f);

		int modelLoc = glGetUniformLocation(shaderProgram.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(shaderProgram.ID, "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		glUniform1f(uniID, 0.5f);

		TimOpenGl.Bind();
		VAO1.Bind();
		//draw the triangle using the GL_TRIANGLES primative
			//draw triangles
		//glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		
		//draw square
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
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
	TimOpenGl.Delete();
	shaderProgram.Delete();
	engine.deleteStuff();
	return 0;
}
