#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
	public:
		// ID reference for the Vertex Array Object
		GLuint ID;
		// constructor that generates a VAO ID
		VAO();

		//links a VBO to the VAO using a certain layout
		void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		//binds the VAO
		void Bind();
		//unbinds the VAO
		void Unbind();
		//delets the VAO
		void Delete();
};

#endif