#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

std::string get_file_contents(const char* filename);

class Shader
{
	public:
		//reference to the ID of the shader
		GLuint ID;
		//constructor that buids the shader program from 2 different shaders, vertex and fragment
		Shader(const char* vertexFile, const char* fragmentFile);

		//Activates the shader program
		void Activate();
		//deletes the shader program
		void Delete();

	private:
		void compileErrors(unsigned int shader, const char* type);
};

#endif