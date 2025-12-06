#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <stb/stb_image.h>
#include <glm/glm/glm.hpp>
//#include <glm/glm/gtc/matrix_transform.hpp>
//#include <glm/glm/gtc/type_ptr.hpp>
#include <iostream>
//#include <vector>
#include <cmath>

const float pi = 3.1415926f;

//Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"{\n"
"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

struct Engine {
	GLFWwindow* window;
	//create a bunch of shit like shader objects
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	//reference contains for the Vertex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;
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

		//initialize vertex shader object and get reference
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// attach vertex shader source to the vertex shader object
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		//compile the vertex shader into machine code
		glCompileShader(vertexShader);

		//initialize fragment shader object and get reference
		fragmentShader = glCreateShader(GL_VERTEX_SHADER);
		//attach fragment shader source to the fragment shader object
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		//complie the fragment shader into machine code
		glCompileShader(fragmentShader);

		//initialize shader program and get its reference
		shaderProgram = glCreateProgram();
		//attache the vertex and fragment shaders to the shader program
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		//wrap up/link all the shaders together into the shader program
		glLinkProgram(shaderProgram);

		//delete the now useless vertex and fragement shader objects
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		//generate the VAO and VBO with only 1 object each
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		//make the VAO the current vertex array object by binding it
		glBindVertexArray(VAO);

		//bind the VBO specifying its a GL_ARRAY_BUFFER
		glBindBuffer(GL_ARRAY_BUFFER, VBO);


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
		
		//tell OpenGL which shader program we want to use
		glUseProgram(shaderProgram);
		//bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);

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
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
		glfwDestroyWindow(window);
		glfwTerminate();
	}
};
Engine engine;

/*void drawCircle(float cx, float cy, float r, int segments) {
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(cx, cy);

	for (int i = 0; i <= segments; i++) {
		float angle = i * 2.0f * pi / segments;
		float x = cx + r * cos(angle);
		float y = cy + r * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}*/

int main() {

	//Vertices Coordinates
	//3 points that create an equilateral triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	//lower left
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		//lower right
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f	//middle top
	};

	//introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//configure the vertex attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enable the vertex attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	//bind both the VBO and VAO to 0 so that we dont accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);




	//main loop
	while (!glfwWindowShouldClose(engine.window)) {
		engine.run();

		//draw the triangle using the GL_TRIANGLES primative
		glDrawArrays(GL_TRIANGLES, 0, 3);
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
	engine.deleteStuff();
	return 0;
}
