#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	/*
		GLFWwindow* glfwCreateWindow(
		int width,
		int height,
		const char* title,
		GLFWmonitor* monitor,// for fullscreen mode
		GLFWwindow* share// for sharing resources with another window, can be NULL
		);
	*/
	if(window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();// clean up all resources allocated by GLFW
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	/*
		前两个参数控制窗口左下角的位置，第三个和第四个参数控制窗口的宽度和高度
	*/

	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// 设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);// 清空颜色缓冲

		glfwSwapBuffers(window);// 交换颜色缓冲
		glfwPollEvents();// 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
	}

	glfwTerminate();// 释放GLFW分配的所有资源
		
	return 0;
}