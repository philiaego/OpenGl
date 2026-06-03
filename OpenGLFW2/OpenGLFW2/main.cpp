#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

const char* vertexShaderSource = "#version 460 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main() {\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	const char* fragmentShaderSource = "#version 460 core\n"
		"out vec4 FragColor;\n"
		"void main() {\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

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
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();// clean up all resources allocated by GLFW
		return -1;
	}

	glfwMakeContextCurrent(window);// 将窗口的上下文设置为当前线程的主上下文，这样OpenGL函数就可以在这个窗口上进行渲染了

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	/*
		前两个参数控制窗口左下角的位置，第三个和第四个参数控制窗口的宽度和高度
	*/
	


	

	unsigned int vertexShader;// 创建一个顶点着色器对象，并返回其ID
	unsigned int fragmentShader;// 创建一个片段着色器对象，并返回其ID
	vertexShader = glCreateShader(GL_VERTEX_SHADER);// 参数指定了要创建的着色器类型，这里是顶点着色器
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);// 参数指定了要创建的着色器类型，这里是片段着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// 将顶点着色器源码附加到着色器对象上
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);// 将片段着色器源码附加到着色器对象上
	/*
		参数
			-shader: 指定要编译的着色器对象
			-count: 指定传递的源码字符串数量，这里是1
			-string: 指向一个字符串数组的指针，包含了着色器源码
			-length: 指定每个字符串的长度，或者为NULL表示字符串以null结尾
	*/
	glCompileShader(vertexShader);// 编译着色器对象
	glCompileShader(fragmentShader);// 编译着色器对象

	// 检查编译是否成功
	int success;
	int success2;
	char infoLog[512];
	char infoLog2[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);// 获取着色器对象的编译状态
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success2);// 获取着色器对象的编译状态
	/*
		函数作用：查询着色器对象的参数
		参数
			-shader: 指定要查询的着色器对象
			-pname: 指定要查询的参数，这里是GL_COMPILE_STATUS表示编译状态
			-params: 指向一个整数的指针，用于存储查询结果
	*/
	if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog); // 修复后的代码
			/*
				函数作用：获取着色器对象的编译错误日志
				参数
					-shader: 指定要查询的着色器对象
					-maxLength: 指定要获取的日志的最大长度，这里是512
					-length: 指向一个整数的指针，用于存储实际获取的日志长度，或者为NULL表示不需要
					-infoLog: 指向一个字符数组的指针，用于存储获取的日志
			*/
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	if(!success2) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2); // 修复后的代码
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
	}

	unsigned int shaderProgram;// 创建一个着色器程序对象，并返回其ID
	shaderProgram = glCreateProgram();// 创建一个着色器程序对象，并返回其ID
	glAttachShader(shaderProgram, vertexShader);// 将顶点着色器对象附加到着色器程序对象上
	glAttachShader(shaderProgram, fragmentShader);// 将片段着色器对象附加到着色器程序对象上
	glLinkProgram(shaderProgram);// 链接着色器程序对象

	// 检查链接是否成功
	int success3;
	char infoLog3[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success3);// 获取着色器程序对象的链接状态

	if(!success3) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog3); // 修复后的代码
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog3 << std::endl;
	}

	// 删除着色器对象，因为它们已经链接到程序对象上了，之后就不再需要了
	glDeleteShader(vertexShader);// 删除一个着色器对象
	glDeleteShader(fragmentShader);// 删除一个着色器对象

	
	
	/*
		函数作用：定义一个顶点属性数据的格式和位置
		参数：
			-index: 指定要修改的顶点属性的索引，这里是0，表示第一个顶点属性
			-size: 指定每个顶点属性的组件数量，这里是3，表示每个顶点属性由3个浮点数组成
			-type: 指定每个组件的数据类型，这里是GL_FLOAT，表示每个组件都是一个浮点数
			-normalized: 指定是否将整数数据归一化为[0,1]或[-1,1]之间的浮点数，这里是GL_FALSE，表示不进行归一化
			-stride: 指定连续顶点属性之间的字节偏移量，这里是3 * sizeof(float)，表示每个顶点属性占用3个浮点数的空间
			-pointer: 指定第一个组件的位置，这里是(void*)0，表示从当前绑定的顶点缓冲对象的起始位置开始读取数据
	*/
	

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	//VAO
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);// 生成一个VAO对象
	glGenBuffers(1, &VBO);// 生成一个VBO对象
	glBindVertexArray(VAO);// 绑定VAO对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);// 绑定VBO对象到GL_ARRAY_BUFFER目标
	
	/*
		将VAO绑定到当前上下文中，之后的顶点属性配置和顶点缓冲对象绑定都会被VAO记录下来
	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// 将用户定义的数据复制到当前绑定的缓冲中
	/*
		参数：
			-target: 指定缓冲对象的类型，GL_ARRAY_BUFFER表示该缓冲对象将被用作顶点属性数据
			-size: 指定要传输的数据的大小，以字节为单位
			-data: 指向要传输的数据的指针
			-usage: 指定数据的预期使用方式，GL_STATIC_DRAW表示数据将被修改一次，并使用多次
	*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);// 启用一个顶点属性数组，参数是要启用的顶点属性的索引，这里是0，表示第一个顶点属性


	// render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);// 设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT);// 清空颜色缓冲

		glUseProgram(shaderProgram);// 激活着色器程序对象，使其成为当前使用的程序
		glBindVertexArray(VAO);// 绑定VAO对象，使其成为当前使用的顶点数组对象
		glDrawArrays(GL_TRIANGLES, 0, 3);// 绘制图元

		glfwSwapBuffers(window);// 交换颜色缓冲
		glfwPollEvents();// 检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数
	}

	

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();// 释放GLFW分配的所有资源
		
	return 0;
}