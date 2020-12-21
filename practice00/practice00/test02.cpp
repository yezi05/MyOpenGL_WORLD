#include<GLFW/glfw3.h>
//#include<GL/glew.h>
#include <iostream>
#include<glad/glad.h>
#define MAXWIN_W 800
#define MAXWIN_H 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";


int main2()
{
#pragma region	//Init GLFW
	glfwInit();
	//配置GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//主版本号设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//次版本号设为3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//明确告诉GLFW使用核心模式（Core-profile）

#pragma endregion

#pragma region	//Creat a window 创建一个窗口对象
	GLFWwindow* window;		//In the accompany source code, this variable is global for simlicity.
	window = glfwCreateWindow(MAXWIN_W, MAXWIN_H, "WELLCOME TO THE NEW WORLD !", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);	//Initialize GLFW

	//注册这个Callback Function函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

#pragma region	//初始化GLAD
	//GLAD管理OpenGL的函数指针的，so调用任何OpenGL函数之前需要初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD. " << std::endl;
		return -1;
	}
#pragma endregion

#pragma region	//渲染窗口的尺寸大小，即视口：viewport
	//这样OpenGL才知道怎样根据窗口大小显示数据和坐标
	glViewport(0, 0, MAXWIN_W, MAXWIN_H);
#pragma endregion

#pragma region 顶点数据
	float vertices[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.3f, 0.0f   // top 
	};
#pragma endregion

#pragma region //存数据、解析数据
	//创建相同的两个三角形，但对它们的数据使用不同的VAO和VBO：
	//TO DO
	unsigned int VBOS[2], VAOS[2];
	glGenBuffers(2, VBOS);
	glGenVertexArrays(2, VAOS);

	//first triangle set up
	glBindVertexArray(VAOS[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//second triangle set up
	glBindVertexArray(VAOS[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion

	//以上，已经把顶点数据存好了，接下来，创建顶点着色器和片段着色器真正处理这些数据：
#pragma region 创建着色器对象
	//TO DO
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//检测在调用glCompileShader后编译是否成功
	int success;
	char infoLog[512];
	//检测
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region 片段着色器	：计算像素最后的颜色输出
	//TO DO
	//片段着色器1
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader1);
	//片段着色器2
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShader2);

	//检测是否编译成功
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT1::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT2::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion

#pragma region 链接着色器对象：着色器程序对象
	//三个着色器对象都编译了，
	//接下来分别把两个片段着色器对象与顶点着色器对象链接到用来渲染的着色器程序Shader Program中
	//TO DO
	unsigned int shaderProgramOrange = glCreateProgram();
	unsigned int shaderProgramYellow = glCreateProgram();

	//link
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShader1);
	glLinkProgram(shaderProgramOrange);

	//Link
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramYellow, fragmentShader2);
	glLinkProgram(shaderProgramYellow);


	//检测链接着色器程序是否失败check for linking errors
	glGetProgramiv(shaderProgramOrange, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramOrange, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAMO::LINK_FAILED\n" << infoLog << std::endl;
	}
	glGetProgramiv(shaderProgramYellow, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramYellow, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAMY::LINK_FAILED\n" << infoLog << std::endl;
	}

#pragma endregion

#pragma region //释放着色器对象  【写在这儿了】
	//TO DO
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

#pragma endregion

#pragma region Render Loop
	//不能只绘制一个图像后，应用程序就立即退出并关闭窗口，希望在主动关闭之前要不断绘制图像并能接受用户输入
	//so 添加while循环
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw
		//TO DO
		//now when we draw the triangle we first use the vertex and orange fragment shader from the first program
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAOS[0]);	// draw the first triangle using the data from our first VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);		// this call output an orange triangle

		// then we draw the second triangle using the data from the second VAO
		// when we draw the second triangle we want to use a different shader program ,
		//so we switch to the shader program with our yellow fragment shader.
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOS[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);	//output an yellow triangle

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	//可选：一旦资源用完了，就取消所有资源的分配：
	//TO DO
	glDeleteVertexArrays(2, VAOS);
	glDeleteBuffers(2, VBOS);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

	// glfw: terminate, clearing all previously allocated GLFW resources.//释放分配的所有资源
	glfwTerminate();
	return 0;
}

//回调函数 (Callback Function)，根据窗口的改变而改变视口大小
//这个function在每次窗口大小改变时被调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//处理所有输入：查询GLFW是否在此帧中按下/释放了相关的按键并做出相应的反应
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
