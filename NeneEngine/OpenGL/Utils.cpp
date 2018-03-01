/*Copyright reserved by KenLee@2017 ken4000kl@gmail.com*/

// ͷ�ļ�
#include "Utils.h"

//��ʼ������
GLFWwindow* initWindow(const char* window_name, int w, int h,
                       int glMajor, int glMinor) {
    // ��ʼ��GLFW
    if(!glfwInit()) {
        printf("[ERROR]: Initialization of GLFW Failed!");
    }
    // ��ʾ���
    printf("[INFO]: Initializing window with OpenGL version %d.%d ...\n\n", glMajor, glMinor);
    // ����OpenGL�汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinor);
    // ������Resize
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    // ��������
    GLFWwindow *window = glfwCreateWindow(w, h, window_name, nullptr, nullptr);
    // ����Ƿ�ɹ�
    if(window == nullptr) {
        printf("[ERROR]: Fail to create GLFW window with OpenGL version %d.%d!\n", glMajor, glMinor);
        glfwTerminate();
        exit(-1);
    }
    // ��ȡ��ʾ����С
    const GLFWvidmode *screen;
    screen = glfwGetVideoMode(glfwGetPrimaryMonitor());
    // ���ô������м�
    glfwSetWindowPos(window, (screen->width - w) / 2, (screen->height - h) / 2);
    // ��ʼ����Ⱦ������
    glfwMakeContextCurrent(window);
    // ��ʼ��GLEW
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        printf("[ERROR]: Fail to init GLEW\n");
        exit(-1);
    }
    // ������glew�����INVALID_ENUM����
    glGetError();
    // ��ȡ��ǰ���ڴ�С������GLVIewport
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    return window;
}

// ���OpenGL,GLEW,GLFW�汾��Ϣ
void showEnviroment() {
    // ����Կ���Ӧ�ÿ������Ϣ
    printf("[INFO]:\n");
    printf("  Working at:\n");
    printf("    %s\n", glGetString(GL_RENDERER));
    printf("  Using:\n");
    printf("    OpenGL %s\n", glGetString(GL_VERSION));
    printf("    GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    printf("    GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("    GLFW %s\n\n", glfwGetVersionString());
    // ���ϸ�������Ϣ
    int glMajor;
    glGetIntegerv(GL_MAJOR_VERSION, &glMajor);
    if(glMajor >= 4) {
        int maxPatchVerticesNum, maxVerticeOutLen, maxPatchOutLen, maxTotalOutLen;
        glGetIntegerv(GL_MAX_PATCH_VERTICES, &maxPatchVerticesNum);
        glGetIntegerv(GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, &maxVerticeOutLen);
        glGetIntegerv(GL_MAX_TESS_PATCH_COMPONENTS, &maxPatchOutLen);
        glGetIntegerv(GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, &maxTotalOutLen);
        printf("[INFO]: \n");
        printf("  Tessellation Limitations:\n");
        printf("    Maximun Vertices Per-Patch: %d\n", maxPatchVerticesNum);
        printf("    Maximun TCS Per-Vertice Output Length: %d\n", maxVerticeOutLen);
        printf("    Maximun TCS Per-Patch Output Length: %d\n", maxPatchOutLen);
        printf("    Maximun TCS Total Output Length: %d\n\n", maxTotalOutLen);
    }
}

// ���OpenGL����
void _checkError(const char* fileName, const char* func, const int line) {
    printf("[Debug]:\n");
    std::string fileNameStr(fileName);
    int splashPos = fileNameStr.rfind('/');
    fileNameStr = fileNameStr.substr(splashPos + 1, std::string::npos);
    printf("  File: %s\n", fileNameStr.c_str());
    printf("  Func: %s(...)\n", func);
    printf("  Line: %d\n", line);
    printf("  glGetError(): %s\n\n", gluErrorString(glGetError()));
}

void _checkFileExist(const char* fileName) {
	if(access(fileName, F_OK)){
		printf("[Error] File not exist! (%s)\n\n", fileName);
		exit(-1);
	}
}

