#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// �����ζ���
GLfloat vertices[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};
// ������ɫ��
const char*vsSource =
    "layout (location = 0) in vec3 pos;\n"
    "void main(){\n"
    "   gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);\n"
    "}\n";
// ������ɫ��
const char*fsSource =
    "out vec4 color;\n"
    "void main(){\n"
    "   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n";

int main(){
    // ��ʼ��
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // ��������
    GLFWwindow *window = glfwCreateWindow(800, 600, "T", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    // ��ȡ��ǰ���ڴ�С������GLVIewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //
    glewExperimental = true;
    glewInit();
    // ���뻺��(�ɼ����Ϊ�����Դ�)
    GLuint vbo, vao;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    // д�붥������
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // ��������Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1 ,&vsSource,nullptr);
    glCompileShader(vertexShader);
    //����fragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader,1,&fsSource,nullptr);
    glCompileShader(fragmentShader);
    //����ShaderProgram
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // ��ѭ��
    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(1.0, 0.1, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    return 0;
}


/*
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//FreeImage
#include <FreeImage.h>
//C++ Library
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
//Helper Classes
#include "wmdge/FPSCounter.h"
#include "wmdge/Shader.h"
#include "wmdge/TextureManager.h"
#include "wmdge/Camera.h"
#include "wmdge/CameraController.h"
#include "wmdge/CoordinateAxes.h"
#include "wmdge/Object.h"
#include "wmdge/Texture.h"
#include "wmdge/Model.h"
#include "wmdge/Geometry.h"
#include "wmdge/utils.hpp"
#include "wmdge/ControlPanel.h"
#include "wmdge/CurveCollection.h"
//Tutorial and exercises
#include "tutorials/Benchmark.hpp"
#include "tutorials/HelloTriangle.hpp"
#include "tutorials/Shaders.hpp"
#include "tutorials/Textures.hpp"
#include "tutorials/Transformations.hpp"
#include "tutorials/CoordinateSystem.hpp"
#include "tutorials/Camera.hpp"
#include "tutorials/Colors.hpp"
#include "tutorials/BasicLighting.hpp"
#include "tutorials/Materials.hpp"
#include "tutorials/LightMaps.hpp"
#include "tutorials/LightCasters.hpp"
#include "tutorials/MultipleLights.hpp"
#include "tutorials/ModelLoading.hpp"
#include "tutorials/DepthTest.hpp"
#include "tutorials/StencilTest.hpp"
#include "tutorials/Blending.hpp"
#include "tutorials/FaceCulling.hpp"
#include "tutorials/Framebuffers.hpp"
#include "tutorials/Mirror.hpp"
#include "tutorials/Cubemaps.hpp"
#include "tutorials/AdvancedData.hpp"
#include "tutorials/AdvancedGLSL.hpp"
#include "tutorials/GeometryShader.hpp"
#include "tutorials/Instancing.hpp"
#include "tutorials/AntiAliasing.hpp"
//#include "tutorials/Stella.hpp"
#include "tutorials/BlinnPhong.hpp"
#include "tutorials/GammaCorrection.hpp"
#include "tutorials/NormalMapping.hpp"
#include "tutorials/ShadowMapping.hpp"
#include "tutorials/PointShadows.hpp"
#include "tutorials/ParallaxMapping.hpp"
#include "tutorials/HDR.hpp"
#include "tutorials/Bloom.hpp"
#include "tutorials/PBR.hpp"
#include "tutorials/DeferredShading.hpp"
#include "tutorials/SSAO.hpp"
*/
