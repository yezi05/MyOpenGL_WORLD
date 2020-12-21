#include<GLFW/glfw3.h>
//#include<GL/glew.h>
#include <iostream>
#include<glad/glad.h>
#define MAXWIN_W 800
#define MAXWIN_H 600

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//const char* vertexShaderSource = "version 330 core\n"
//"layout (location=0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"	gl_Position=vec4(aPos.x, aPos.y,aPos.z,1.0);\n"
//"}\0";
//const char* fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
//"}\n\0";

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
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
	if (window==NULL)
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
		std::cout<<"Failed to initialize GLAD. "<<std::endl;
		return -1;
	}
	#pragma endregion

	#pragma region	//渲染窗口的尺寸大小，即视口：viewport
	//这样OpenGL才知道怎样根据窗口大小显示数据和坐标
	glViewport(0, 0, MAXWIN_W, MAXWIN_H);
	#pragma endregion

	////注册这个Callback Function函数，告诉GLFW我们希望每当窗口调整大小的时候调用这个函数
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

#pragma region 顶点数据
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};

#pragma endregion

	//把这些数据都存到缓存里，
#pragma region VBO
	//生成一个VBO对象：
	unsigned int VBO;	//无符号整型变量（非负）
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);					//bind上这个VAO
	glGenBuffers(1, &VBO);	//生成一个缓冲对象，并把对象绑定在整形变量VBO上
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	//指定缓冲类型，把新创建的缓冲绑定到这个类型上。OpenGL有很多缓冲对象类型，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	//专门复制用户定义的数据，复制到当前绑定缓冲
	//现在我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理。
#pragma endregion
#pragma region 解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
#pragma endregion

#pragma region	Creat a VAO object
	//unsigned int VAO;
	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);				//bind上这个VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);		
	glBindVertexArray(0);					// to unbind 
#pragma endregion
	//unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &VBO);
	//glBindVertexArray(VAO);				//bind进来
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);	//绑上VAO  把要操作的VBO指定为现在的ARRAY_BUFFER,才能为当下的VAO服务。
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);   //拷贝用户数据
	//glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0); //解析数据
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//以上，已经把顶点数据存好了，接下来，创建顶点着色器和片段着色器真正处理这些数据：
#pragma region 创建着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		//着色器源码附加到着色器对象上，
	glCompileShader(vertexShader);									//然后编译它。
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
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//检测是否编译成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region 链接着色器对象：着色器程序对象
	//两个着色器对象都编译了，接下来把两个着色器对象链接到一个用来渲染的着色器程序Shader Program中
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();				//create函数创建一个程序，并返回一个程序对象的ID引用
	glAttachShader(shaderProgram, vertexShader);	//编译好的着色器附加到程序对象上，
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);					//然后链接它们。
	//检测链接着色器程序是否失败check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region //释放着色器对象  【写在这儿了】
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
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
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	#pragma endregion

	//可选：一旦资源用完了，就取消所有资源的分配：
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
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
	if (glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
