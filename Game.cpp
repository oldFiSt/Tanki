#include "Game.h"
#include <stdexcept>
#include <iostream>

class Game{
    private:
    GLFWwindow* m_window;
    GLuint m_VAO, m_VBO;
    glm::mat4 m_projection, m_view, m_model;
    Ttank m_tank;
}
Game::Game()
{
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    m_window = glfwCreateWindow(640, 480, "Play with Tanki", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);
    // Инициализация OpenGL
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);

    glViewport(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);

    m_projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
    m_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_model = glm::mat4(1.0f);

    m_tank = Ttank(40, 11);
}

void Game::drawTank()
{
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Координаты вершин танка
    float vertices[] = {
        // Тело танка
        -0.5f, 0.0f, -0.5f,
        -0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, 0.5f,
        0.5f, 0.0f, -0.5f,
        // Дуло
        -0.2f, 0.0f, 0.0f,
        0.2f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(m_tank.x, m_tank.y, 0.0f));
    model = glm::rotate(model, glm::radians(90.0f * static_cast<float>(m_tank.dir)), glm::vec3(0.0f, 0.0f, 1.0f));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(m_view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(m_projection));

    glDrawArrays(GL_QUADS, 0, 4);
    glDrawArrays(GL_TRIANGLES, 4, 3);
    glBindVertexArray(0);
}

Game::~Game()
{
    glfwTerminate();
}

void Game::run()
{
    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawField();
        drawTank();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}