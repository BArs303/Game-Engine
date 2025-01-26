#include "main.h"

int main()
{
	GLFWwindow *window;
	if(!glfwInit())
		return -1;
	window = glfwCreateWindow(640, 480, "Test", NULL, NULL);
	if(!window)
	{
		printf("window creation failed\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		printf("GLAD load failed\n");
		glfwTerminate();
		return -1;
	}

	while(!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
