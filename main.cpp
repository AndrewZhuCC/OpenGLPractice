//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//C++ Library
#include <cstdio>
#include <cstdlib>
#include <iostream>
//Tool set
#include "utils.hpp"

using namespace std;

//���ж�������
GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,  // Top Right
     0.5f, -0.5f, 0.0f,  // Bottom Right
    -0.5f, -0.5f, 0.0f,  // Bottom Left
    -0.5f,  0.5f, 0.0f   // Top Left
};
//���ƶ���˳��
GLuint indices[]={
    0,1,3,
    1,2,3
};
//vertexShader GLSL
const GLchar *vertexShaderSource=
    "#version 330 core\n"
    "layout (location=0) in vec3 position;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
    "}\0";
//fragmentShader GLSL
const GLchar *fragmentShaderSource=
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color=vec4(1.0f,0.5f,0.2f,1.0f);\n"
    "}\n";
//��ʼ������
GLFWwindow* initWindow(const char* window_name,int w,int h){
    //��ʼ��GLFW������GLFW������GL�汾3.3��ֻʹ��CORE_PROFILE������Resize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    //��������
    GLFWwindow *window = glfwCreateWindow(w,h,window_name,nullptr,nullptr);
    //����Ƿ�ɹ�
    if(window == nullptr){
        cout<<"ERROR: Fail to create GLFW window"<<endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    //��ʼ��GLEW�� ʹ��Experimental�����������Ǹ��õ�ʹ��core_profile
    glewExperimental = GL_TRUE;
    if(glewInit()!=GLEW_OK){
        cout<<"ERROR: Fail to init GLEW"<<endl;
        exit(-1);
    }
    //��ȡ��ǰ���ڴ�С������GLVIewport
    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    glViewport(0,0,width,height);
    return window;
}
//���GLSL�������
void checkShaderCompile(GLuint shaderID){
    GLint isSuccess;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&isSuccess);
    if(!isSuccess){
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID,512,nullptr,infoLog);
        cout<<"ERROR: Comlile VertexShader Error:"<<endl<<infoLog<<endl;
        exit(-1);
    }
}
void checkProgramLink(GLuint programID){
    GLint isSuccess;
    glGetProgramiv(programID,GL_LINK_STATUS,&isSuccess);
    if(!isSuccess){
        GLchar infoLog[512];
        glGetProgramInfoLog(programID,512,nullptr,infoLog);
        cout<<"ERROR: Link Program Error:"<<endl<<infoLog<<endl;
        exit(-1);
    }
}
int main(){
    //��ʼ������
    GLFWwindow *window=initWindow("HelloKenLee!",800,600);
    showEnviroment();
    //����
    //GLfloat r=0.0f,g=0.0f,b=0.0f;
    //����VBO �����Դ����
    GLuint VBO;
    glGenBuffers(1,&VBO);
    //����VAO
    GLuint VAO;
    glGenVertexArrays(1,&VAO);
    //����EBO
    GLuint EBO;
    glGenBuffers(1,&EBO);
    //��VAO,VBO,����VAO
    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),(GLvoid*)0);//�󶨶�������(һ����˵���������԰��� λ�ã����ߣ���ɫ����������ȣ�����ֻ��λ������)
        glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    //��������Shader
    GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexShaderSource,nullptr);
    glCompileShader(vertexShader);
    checkShaderCompile(vertexShader);
    //����fragmentShader
    GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fragmentShaderSource,nullptr);
    glCompileShader(fragmentShader);
    checkShaderCompile(fragmentShader);
    //����ShaderProgram
    GLuint shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgramLink(shaderProgram);
    //ɾ��Shader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //��ѭ��
    while(!glfwWindowShouldClose(window)){
        //��ѯ�����߼��̵�����
        glfwPollEvents();
        glClearColor(1.0f,1.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //ʹ��Shader����
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_QUADS,0,4);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //˫�����û�
        glfwSwapBuffers(window);
    }
    //��ֹ��Ⱦ
    glfwTerminate();
    return 0;
}
