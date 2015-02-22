#include <iostream>
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "ShaderLoader.h"
#include "colour.h"

#include "vertex.h"
#include "quaternion.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GLFW\glfw3.h>

struct OpenGlData
{
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;
	unsigned int m_VertexCount;
};

OpenGlData ExampleTraingle(vec4 a, vec4 b, vec4 c)
{
	//creates basic triangle to play with
	vertex* myShape = new vertex[3];
	myShape[0].m_vPosition = a;
	myShape[1].m_vPosition = b;
	myShape[2].m_vPosition = c;

	myShape[0].m_oColour = colour().Red();
	myShape[1].m_oColour = colour().Green();
	myShape[2].m_oColour = colour().Blue();

	unsigned int Indeces[3] = { 0, 1, 2 };

	//creates and bind our buffers
	GLuint VAO, VBO, IBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	//loads in VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 3,
		myShape, GL_STATIC_DRAW);

	//loads in IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3,
		Indeces, GL_STATIC_DRAW);

	//defines our attribute pointers
	glEnableVertexAttribArray(0);	//POSITION
	glEnableVertexAttribArray(1);	//COLOUR

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
							sizeof(vertex), 0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
							sizeof(vertex), (void*)(sizeof(vec4)));

	//unbinds out buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//returns result
	OpenGlData returnData;
	returnData.m_VAO = VAO;
	returnData.m_VBO = VBO;
	returnData.m_IBO = IBO;
	returnData.m_VertexCount = 3;

	delete[] myShape;

	return returnData;
}

void Draw(GLFWwindow* window , OpenGlData DataToDraw, GLuint ShaderProgram, mat4 MVP, mat4 Transform, colour Colour = colour::White())
{
	GLuint MVP_handle = glGetUniformLocation(ShaderProgram, "MVP");
		glUniformMatrix4fv(MVP_handle, 1, GL_FALSE, (float*)MVP.ToArray());
	
	glUseProgram(ShaderProgram);
	glBindVertexArray(DataToDraw.m_VAO);
	glDrawElements(GL_TRIANGLES, DataToDraw.m_VertexCount, GL_UNSIGNED_BYTE, NULL);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void ClearOpenGlData(OpenGlData &dataToClear)
{
	glDeleteVertexArrays(1, &dataToClear.m_VAO);
	glDeleteBuffers(1, &dataToClear.m_VBO);
	glDeleteBuffers(1, &dataToClear.m_IBO);
	dataToClear.m_VertexCount = 0;
}

int main()
{
	//initialise GLFW
	if (!glfwInit())
		return -1;

	//Creates the context window
	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "OI OI", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//logs this window as the one we want to play with
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	//creates a mighty curious triangle
	OpenGlData George = ExampleTraingle(	vec4(1024 / 2.0,		  720 / 2.0 + 100.0f, 1.0f,	1.0f),
											vec4(1024 / 2.0 - 160.0f, 720 / 2.0 - 80.0f, -1.0f, 1.0f),
											vec4(1024 / 2.0 + 160.0f, 720 / 2.0 - 80.0f, -1.0f, 1.0f));

	//loads in our shaders
	GLuint uiProgramFlat = CreateProgram("VertexShader.glsl", "FlatFragmentShader.glsl");

	mat4 ortho = mat4().Identity(); //mat4().getOrthographic(0, 1024, 0, 720, -1000, 1000);

	//Game loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3f, 0.3f, 0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Draw(window, George, uiProgramFlat, ortho, mat4::Identity());
	}

	ClearOpenGlData(George);

	glfwTerminate();
	return 0;
}
