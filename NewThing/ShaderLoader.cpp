#include "ShaderLoader.h"

GLuint CreateShader(GLenum a_eShaderType, const char* a_strShaderFile)
{
	std::string strShaderCode;

	//open the shader file
	std::ifstream ShaderStream(a_strShaderFile);

	if (ShaderStream.is_open())
	{
		std::string Line = "";
		while (std::getline(ShaderStream, Line))
		{
			strShaderCode += "\n" + Line;
		}
		ShaderStream.close();
	}

	//convert to cstring
	char const *szShaderSourcePointer = strShaderCode.c_str();
	 
	//compile and create the shader
	GLuint uiShader = glCreateShader(a_eShaderType);
	glShaderSource(uiShader, 1, &szShaderSourcePointer, NULL);
	glCompileShader(uiShader);

	GLint iStatus;
	glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iStatus);
	if (iStatus == GL_FALSE)	//if it fails output the error message to the console
	{
		GLint infoLogLength;
		glGetShaderiv(uiShader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(uiShader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch(a_eShaderType)
		{
			case GL_VERTEX_SHADER:
				strShaderType = "vertex";
			break;
			case GL_FRAGMENT_SHADER:
				strShaderType = "fragment";
			break;
		}

		fprintf(stderr, " Compilation of ya %s shader has failed: \n%s\n ", strShaderType, strInfoLog);
		delete strInfoLog;
	}
	return uiShader;
}

GLuint CreateProgram(const char *a_vertex, const char *a_frag)
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader( GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader( GL_FRAGMENT_SHADER, a_frag));

	GLuint uiProgram = glCreateProgram();

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
		glAttachShader(uiProgram, *shader);
	
	glLinkProgram(uiProgram);

	GLint iStatus;
	glGetProgramiv(uiProgram, GL_LINK_STATUS, &iStatus);
	if (iStatus == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(uiProgram, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(uiProgram, infoLogLength, NULL, strInfoLog);

		fprintf(stderr, "Linker failure: %s\n : ", strInfoLog);
		delete strInfoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader ++)
	{
		glDetachShader(uiProgram, *shader);
		glDeleteShader(*shader);
	}

	return uiProgram;
	
}