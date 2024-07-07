#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <iostream>
#include <chrono>

#include"Game/Game.h"
#include"Resources/ResourceManager.h"

glm::ivec2 g_windowSize(640, 480);
Game g_game(g_windowSize);


void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, width, height); //для растягивания окошка 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)//проверка на клавишы
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);//выход из программы 
    }
    g_game.setkey(key,action);
}

int main(int argc, char** argv)
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }
    //для создания контекста OpenGl
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//то, какая версия используется 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//в случае если версия ниже окно не откроется 

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Танчики", nullptr, nullptr);//создание окна 
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD!" << std::endl;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 0, 0, 1);

    
    {
        ResourceManager::setExecutablePath(argv[0]);
        g_game.init();

        auto lastTime = std::chrono::high_resolution_clock::now();
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pWindow))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t duration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            g_game.update(duration);

            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            g_game.render();

            /* Swap front and back buffers */
            glfwSwapBuffers(pWindow);

            glfwPollEvents();//следит за движением курсора, нажатием клавиш, закрытие окна                                              
        }
        ResourceManager::unloadAllResources();
    }

    glfwTerminate();
    return 0;
}