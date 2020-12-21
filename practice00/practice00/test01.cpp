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

int main1()
{
#pragma region	//Init GLFW
	glfwInit();
	//����GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	//���汾����Ϊ3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//�ΰ汾����Ϊ3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	//��ȷ����GLFWʹ�ú���ģʽ��Core-profile��

#pragma endregion

#pragma region	//Creat a window ����һ�����ڶ���
	GLFWwindow* window;		//In the accompany source code, this variable is global for simlicity.
	window = glfwCreateWindow(MAXWIN_W, MAXWIN_H, "WELLCOME TO THE NEW WORLD !", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);	//Initialize GLFW

	//ע�����Callback Function����������GLFW����ϣ��ÿ�����ڵ�����С��ʱ������������
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
#pragma endregion

#pragma region	//��ʼ��GLAD
	//GLAD����OpenGL�ĺ���ָ��ģ�so�����κ�OpenGL����֮ǰ��Ҫ��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD. " << std::endl;
		return -1;
	}
#pragma endregion

#pragma region	//��Ⱦ���ڵĳߴ��С�����ӿڣ�viewport
	//����OpenGL��֪���������ݴ��ڴ�С��ʾ���ݺ�����
	glViewport(0, 0, MAXWIN_W, MAXWIN_H);
#pragma endregion

#pragma region ��������
	float vertices[] = {
		-0.9f, -0.5f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f,  // right
		-0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
	0.0f, -0.5f, 0.0f,  // left
	0.9f, -0.5f, 0.0f,  // right
	0.45f, 0.5f, 0.0f   // top 
	};
#pragma endregion

#pragma region //�����ݡ���������
	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);

	//
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	//glBindVertexArray(0);//Ҳ���Ǳ���ģ���Ҫע���ʱ���ܻ�Ӱ��VAO�ĵ��ã����磬��Ԫ�ػ��������������/���ö������ԣ�
#pragma endregion

	//���ϣ��Ѿ��Ѷ������ݴ���ˣ�������������������ɫ����Ƭ����ɫ������������Щ���ݣ�
#pragma region ������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		//��ɫ��Դ�븽�ӵ���ɫ�������ϣ�
	glCompileShader(vertexShader);									//Ȼ���������
	//����ڵ���glCompileShader������Ƿ�ɹ�
	int success;
	char infoLog[512];
	//���
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region Ƭ����ɫ��	����������������ɫ���
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//����Ƿ����ɹ�
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATTION_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region ������ɫ��������ɫ���������
	//������ɫ�����󶼱����ˣ���������������ɫ���������ӵ�һ��������Ⱦ����ɫ������Shader Program��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();				//create��������һ�����򣬲�����һ����������ID����
	glAttachShader(shaderProgram, vertexShader);	//����õ���ɫ�����ӵ���������ϣ�
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);					//Ȼ���������ǡ�
	//���������ɫ�������Ƿ�ʧ��check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}
#pragma endregion

#pragma region //�ͷ���ɫ������  ��д������ˡ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
#pragma endregion

#pragma region Render Loop
	//����ֻ����һ��ͼ���Ӧ�ó���������˳����رմ��ڣ�ϣ���������ر�֮ǰҪ���ϻ���ͼ���ܽ����û�����
	//so ���whileѭ��
	while (!glfwWindowShouldClose(window))
	{
		//Input
		processInput(window);

		//render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Draw
		glUseProgram(shaderProgram);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
#pragma endregion

	//��ѡ��һ����Դ�����ˣ���ȡ��������Դ�ķ��䣺
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram);
	// glfw: terminate, clearing all previously allocated GLFW resources.//�ͷŷ����������Դ
	glfwTerminate();
	return 0;
}

//�ص����� (Callback Function)�����ݴ��ڵĸı���ı��ӿڴ�С
//���function��ÿ�δ��ڴ�С�ı�ʱ������
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//�����������룺��ѯGLFW�Ƿ��ڴ�֡�а���/�ͷ�����صİ�����������Ӧ�ķ�Ӧ
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
