#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    GLFWwindow* m_window;
};

#endif