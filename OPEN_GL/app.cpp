#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

#include "Texture.h"

GLfloat vertices[] =
{//				COORDINATES         /		COLOR		  //
	-0.5f,		-0.5f,		0.0f,		1.f,	0.0f,	0.0f,	0.0f, 0.0f,//lower left corner
	-0.5f,		0.5f,		0.0f,		0.0f,	1.0f,	0.0f,	0.0f, 1.0f,//upper left corner
	0.5f,		0.5f,		0.0f,		0.0f,	0.0f,	1.0f,	1.0f, 1.0f,//upper right corner
	0.5f,		-0.5f,		0.0f,		1.0f,	1.0f,	1.0f,	1.0f, 0.0f//lower right corner
};

GLuint indices[] =
{
	0, 2, 1, //Upper triangle
	0, 3, 2  //Lower triangle
};

int main() 
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 800, "Open gl window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Load glad so it configures OpenGL
	gladLoadGL();
	glViewport(0, 0, 800, 800);


	Shader shaderProgram("default.vert", "default.frag");
	
	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	vao.Unbind();
	vbo.UnBind();
	ebo.UnBind();

	GLuint unitID = glGetUniformLocation(shaderProgram.ID, "scale");

	//Texture
	Texture cat("oui.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) 
	{
		//Background color 
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(unitID, 0.5f);
		cat.Bind();
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	cat.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}