#include "main.h"

const char *vertex_shader_source = "#version 330 core\n"
	"layout (location = 0) in vec2 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, 0, 1.0);\n"
	"}\0";

/* R=1.0f G=0.5f B=0f opacity 100% = 1.0f*/
const char *fragment_shader_source = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const int log_size = 512;

int main()
{
	unsigned int width, height;
	int success;
	GLFWwindow *window;
	unsigned int vertex_shader, fragment_shader, shader_program;
	GLuint VBO, VAO, EBO;
	char info_log[log_size];

	float vertices[] =
	{
		0.0f, 0.0f,	//Vertex 1 (x,y)
		0.0f, 0.5f,	//Vertex 2
		0.5f, 0.0f,	//Vertex 3
		0.5f, 0.5f
	};

	unsigned int indices[] =
	{
		0, 1, 2,	//first triangle
		1, 2, 3		//second triangle
	};

	width = 800;
	height = 600;

	/*-----------Initialization--------*/
	if(!glfwInit())
		return -1;
	window = glfwCreateWindow(width, height, "Test", NULL, NULL);
	if(!window)
	{
		printf("window creation failed\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		printf("GLAD load failed\n");
		glfwTerminate();
		return -1;
	}
	/*------------Work with shaders------------*/
	/*define shader type*/
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	/*bind shader with source code
	glShaderSource
	(
		GLuint shader,
		GLsizei count,			string[n] n=count
		const GLchar **string,
		const GLint *length		string[n{i}][m] m=length[i] 
	)*/
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);

	/*compile*/
	glCompileShader(vertex_shader);
	glCompileShader(fragment_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		printf("vertex shader compilation error\n");
		glGetShaderInfoLog(vertex_shader, log_size, NULL, info_log);
		printf("%s\n", info_log);
	}

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		printf("fragment shader compilation error\n");
		glGetShaderInfoLog(fragment_shader, log_size, NULL, info_log);
		printf("%s\n", info_log);
	}
	/*bind all shaders to one object*/
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if(!success)
	{
		printf("shader program link error\n");
		glGetProgramInfoLog(shader_program, log_size, NULL, info_log);
		printf("%s\n", info_log);
	}

	/*delete shader after linking it to program*/
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/*---------BUFFERS---------*/
	/*Generate vertex buffer object*/
	glGenBuffers(1, &VBO);
	/*Generate vertex array object*/
	glGenBuffers(1, &VAO);
	/*Generate element buffer object*/
	glGenBuffers(1, &EBO);

	/*bind the Vertex Array Object first*/
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	/*Load vertex to GraphicCard memory*/
	glBufferData
	(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW
	);
	glBufferData
	(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW
	);

	glVertexAttribPointer
	(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		2*sizeof(float),
		NULL
	);
	glEnableVertexAttribArray(0);

	/*Unbind vao and vbo so other calls won't accidentally modify this vao*/
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		/*Six verticles in 2 triangles
		  GL_UNSIGNED_INT - type of the indices
		  EBO - offset*/
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(shader_program);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
