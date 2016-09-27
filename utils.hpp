#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

//�� stdout ���OpenGL,GLEW,GLFW�汾��Ϣ
void showEnviroment(){
    fprintf(stdout,"Working at:\n\t%s\n",glGetString(GL_RENDERER));
    fprintf(stdout,"Using Libraries:\n\tOpenGL %s\n",glGetString(GL_VERSION));
    fprintf(stdout,"\tGLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout,"\tGLFW %s\n",glfwGetVersionString());
}

//���GLSL�������
void checkShaderCompile(GLuint shaderID){
    GLint isSuccess;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS,&isSuccess);
    if(!isSuccess){
        GLchar infoLog[512];
        glGetShaderInfoLog(shaderID,512,nullptr,infoLog);
        cout<<"ERROR: Comlile Shader Error:"<<endl<<infoLog<<endl;
        exit(-1);
    }
}

//����Shader�������
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


#endif
