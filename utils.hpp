#ifndef UTILS_HPP
#define UTILS_HPP

using namespace std;

//FPS������
class FPSCounter{
public:
    FPSCounter(){
        init();
    }
    void init(){
        lastTime=currentTime=glfwGetTime();
        frameCounter=0;
    }
    //Call in main loop.
    void update(){
        deltaTime=glfwGetTime()-currentTime;
        currentTime=glfwGetTime();
        ++frameCounter;
        if(currentTime-lastTime>=1.0){
            printf("%f ms/frame\n",1000.0/double(frameCounter));
            frameCounter=0;
            lastTime+=1.0;
        }
    }
public:
    double lastTime,currentTime,deltaTime;//�ϴ����FPS��ʱ�䣬��ǰʱ�䣬���2֡�ļ��ʱ��
    int frameCounter;
};


//��ʼ������
GLFWwindow* initWindow(const char* window_name,int w,int h,void (*key_callback)(GLFWwindow*,int,int,int,int)=nullptr,void (*mouse_callback)(GLFWwindow*,double,double)=nullptr){
    //��ʼ��GLFW������GLFW������GL�汾3.3��ֻʹ��CORE_PROFILE������Resize
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    //��������
    GLFWwindow *window = glfwCreateWindow(w,h,window_name,nullptr,nullptr);
    //��ȡ��ʾ����С
    const GLFWvidmode *screen;
    screen=glfwGetVideoMode(glfwGetPrimaryMonitor());
    //���ô������м�
    glfwSetWindowPos(window,(screen->width-w)/2,(screen->height-h)/2);
    //����Ƿ�ɹ�
    if(window == nullptr){
        cout<<"ERROR: Fail to create GLFW window"<<endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    //�󶨰����ص�����
    glfwSetKeyCallback(window,key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    //��ʼ��GLEW�� ʹ��Experimental�����������Ǹ��õ�ʹ��core_profile
    glewExperimental = GL_TRUE;
    if(glewInit()!=GLEW_OK){
        cout<<"ERROR: Fail to init GLEW"<<endl;
        exit(-1);
    }
    glGetError();//������glew�����INVALID_ENUM����
    //��ȡ��ǰ���ڴ�С������GLVIewport
    int width,height;
    glfwGetFramebufferSize(window,&width,&height);
    glViewport(0,0,width,height);
    return window;
}



//���OpenGL,GLEW,GLFW�汾��Ϣ
void showEnviroment(){
    fprintf(stdout,"Working at:\n\t%s\n",glGetString(GL_RENDERER));
    fprintf(stdout,"Using Libraries:\n\tOpenGL %s\n",glGetString(GL_VERSION));
    fprintf(stdout,"\tGLEW %s\n", glewGetString(GLEW_VERSION));
    fprintf(stdout,"\tGLFW %s\n",glfwGetVersionString());
}

//��ȡGL״̬������
void checkError(){
    cout<<"ERROR Check: "<<gluErrorString(glGetError())<<endl;
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



#endif
