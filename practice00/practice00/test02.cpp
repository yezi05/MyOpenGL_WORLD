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
	0.45f, 0.3f, 0.0f   // top 
	};
#pragma endregion

#pragma region //�����ݡ���������
	//������ͬ�����������Σ��������ǵ�����ʹ�ò�ͬ��VAO��VBO��
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

	//���ϣ��Ѿ��Ѷ������ݴ���ˣ�������������������ɫ����Ƭ����ɫ������������Щ���ݣ�
#pragma region ������ɫ������
	//TO DO
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

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
	//TO DO
	//Ƭ����ɫ��1
	unsigned int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader1);
	//Ƭ����ɫ��2
	unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShader2);

	//����Ƿ����ɹ�
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

#pragma region ������ɫ��������ɫ���������
	//������ɫ�����󶼱����ˣ�
	//�������ֱ������Ƭ����ɫ�������붥����ɫ���������ӵ�������Ⱦ����ɫ������Shader Program��
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


	//���������ɫ�������Ƿ�ʧ��check for linking errors
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

#pragma region //�ͷ���ɫ������  ��д������ˡ�
	//TO DO
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);
	glDeleteShader(fragmentShader2);

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

	//��ѡ��һ����Դ�����ˣ���ȡ��������Դ�ķ��䣺
	//TO DO
	glDeleteVertexArrays(2, VAOS);
	glDeleteBuffers(2, VBOS);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

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
