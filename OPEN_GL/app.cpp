#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

GLfloat vertices[] =
{//		COORDINATES                          /       COLOR //
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,	0.8f, 0.3f, 0.02f,//left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f,//right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,	1.0f, 0.6f, 0.32f,//up corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,//
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	0.9f, 0.45f, 0.17f,// 
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.8f, 0.3f, 0.02f,//
};

GLuint indices[] =
{
	0, 3, 5,
	3, 2, 4,
	5, 4, 1
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

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.Unbind();
	vbo.UnBind();
	ebo.UnBind();

	GLuint unitID = glGetUniformLocation(shaderProgram.ID, "scale");

	while (!glfwWindowShouldClose(window)) 
	{
		//Background color 
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		glUniform1f(unitID, 0.5f);
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		//Swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}