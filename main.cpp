#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<iostream>

int g_WindowSizeX = 640;
int g_WindowSizeY = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int widht, int height)
{
    g_WindowSizeX = widht;
    g_WindowSizeY = height;
    glViewport(0, 0, g_WindowSizeX/2, g_WindowSizeY);//Где мы хотим рисовать(в какой области окна). Изначально левый нижний угол окна
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout<<"glfwInit failed!"<<std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_WindowSizeX, g_WindowSizeY, "Battle City", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout<<"glfwCreateWindow falied!"<<std::endl;    
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout<<"Can't load GLAD!"<<std::endl;
        return -1;
    }
    std::cout<<"Renderer: "<<glGetString(GL_RENDERER)<<std::endl;
    std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

    glClearColor(1, 1, 0, 1);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(pWindow))//Цикл отрисовки(рендеринг(отрисовка на экране))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);//Очищаем буфер цвета

        /* Swap front and back buffers */
        glfwSwapBuffers(pWindow);//то есть меняет местами передний и задний буфер цвета

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}