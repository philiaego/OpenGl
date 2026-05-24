#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

unsigned int VBO=0;
unsigned int VAO = 0;
unsigned int shaderProgram = 0;


void rend() {
	glUseProgram(shaderProgram);
	float _time = glfwGetTime();
	float _green = sin(_time) * 0.5f + 0.5f;
	int _location = glGetUniformLocation(shaderProgram, "ourColor");

	glUniform4f(_location, 0.0f, _green, 0.0f, 1.0f);

	glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	glUseProgram(0);
}

void initModel() {
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);//生成一个VAO对象，并将其ID存储在VAO变量中
	glBindVertexArray(VAO);//将生成的VAO对象绑定到当前上下文中，表示我们将使用这个VAO来存储顶点属性配置



	glGenBuffers(1, &VBO);//生成一个VBO对象，并将其ID存储在VBO变量中
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将生成的VBO对象绑定到GL_ARRAY_BUFFER目标上，表示我们将使用这个VBO来存储顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点数据复制到当前绑定的VBO中，参数分别是目标类型、数据大小、数据指针和使用方式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);//定义顶点属性指针，参数分别是属性位置、每个顶点属性的组件数量、数据类型、是否归一化、步长和偏移量，即告诉OpenGL如何解释顶点数据
	glEnableVertexAttribArray(0);//启用顶点属性数组，参数是属性位置
	glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑VBO，防止误操作
	glBindVertexArray(0);//解绑VAO，防止误操作

}

void initShader(const char* _vertexPath, const char* fragPath) {



    std::string _vertexCode("");
    std::string _fragCode("");

    std::ifstream _vShaderFile;
    std::ifstream _fShaderFile;

    _vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    _fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        _vShaderFile.open(_vertexPath);
        _fShaderFile.open(fragPath);

        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << _vShaderFile.rdbuf();
        fShaderStream << _fShaderFile.rdbuf();

        _vertexCode = vShaderStream.str();
        _fragCode = fShaderStream.str();

    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
	const char* _vShaderStr = _vertexCode.c_str();
	const char* _fShaderStr = _fragCode.c_str();

    //shader编译链接
	unsigned int _vertexID=0, _fragID=0;
	char _infoLog[512];
	int _successFlag=0;

	_vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_vertexID, 1, &_vShaderStr, NULL);
    glCompileShader(_vertexID);

	_fragID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_fragID, 1, &_fShaderStr, NULL);
	glCompileShader(_fragID);

	glGetShaderiv(_vertexID, GL_COMPILE_STATUS, &_successFlag);
    if (!_successFlag) {
        glGetShaderInfoLog(_vertexID, 512,NULL, _infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << _infoLog << std::endl;
    }

	glGetShaderiv(_fragID, GL_COMPILE_STATUS, &_successFlag);
    if (!_successFlag) {
        glGetShaderInfoLog(_fragID, 512, NULL, _infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << _infoLog << std::endl;
	}
	//链接shader
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, _vertexID);
	glAttachShader(shaderProgram, _fragID);
	glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &_successFlag);
    if (!_successFlag) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, _infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _infoLog << std::endl;
	}
	glDeleteShader(_vertexID);
	glDeleteShader(_fragID);
    std::cout << "vertex size = " << _vertexCode.size() << std::endl;
    std::cout << "frag size = " << _fragCode.size() << std::endl;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}



int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    } 

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
		std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	initModel();
    initShader(
        "vertexShader.glsl","fragmentShader.glsl" );

    while (!glfwWindowShouldClose(window))
    {
		processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		rend();

        glfwSwapBuffers(window);
		glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}