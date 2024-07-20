#include "Game.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include "GameObjects/Tank.h"
#include "GameObjects/Bullet.h"

#include "GameStates/Level.h"
#include "GameStates/StartScreen.h"
#include "../Physics/PhysicsEngine.h"
#include "../Renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include<random>
#include<ctime>

/// @brief конструктор для инициализации объектов игры (устанавливает начальные параметры\)
/// @param windowSize размер окна 
Game::Game(const glm::uvec2& windowSize)
    : m_windowSize(windowSize)
    , m_eCurrentGameState(EGameState::StartScreen)
    , m_currentLevelIndex(0)
{
    m_keys.fill(false);
}

/// @brief изменнения размеры экрана и обновление соответсвующего представления 
/// @param windowSize размер окна 
void Game::setWindowSize(const glm::uvec2& windowSize)
{
    m_windowSize = windowSize;
    updateViewport();
}

Game::~Game()
{

}

/// @brief функция для отрисовки текущего состояние игры 
void Game::render()
{
    m_pCurrentGameState->render();
}

/// @brief функция настраивает размеры и смещения области просмотра в зависимости от соотношения сторон окна и уровня
void Game::updateViewport()
{
    const float level_aspect_ratio = static_cast<float>(getCurrentWidth()) / getCurrentHeight();
    unsigned int viewPortWidth = m_windowSize.x;
    unsigned int viewPortHeight = m_windowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(m_windowSize.x) / m_windowSize.y > level_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(m_windowSize.y * level_aspect_ratio);
        viewPortLeftOffset = (m_windowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(m_windowSize.x / level_aspect_ratio);
        viewPortBottomOffset = (m_windowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setViewport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(getCurrentWidth()), 0.f, static_cast<float>(getCurrentHeight()), -100.f, 100.f);
    m_pSpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);
}

/// @brief функция для инициализации нового уровня в игре 
/// @param level выбранный уровень
void Game::startNewLevel(const size_t level, const EGameMode eGameMode)
{
    m_currentLevelIndex = level;
    int random_number = rand() % 5;
    auto pLevel = std::make_shared<Level>(ResourceManager::getLevels()[random_number], eGameMode);
    m_pCurrentGameState = pLevel;
    Physics::PhysicsEngine::setCurrentLevel(pLevel);
    updateViewport();
}


/// @brief функция для запуска режима 1 или 2 игрока
/// @param eGameMode выбор режима
void Game::nextLevel(const EGameMode eGameMode)
{
    startNewLevel(++m_currentLevelIndex, eGameMode);
}

/// @brief функция для обновления состояния игры на каждом кадре 
/// @param delta время прошедшее с последнего обновления кадра 
void Game::update(const double delta)
{
    m_pCurrentGameState->processInput(m_keys);
    m_pCurrentGameState->update(delta);

}

/// @brief функция отвечает за установку состояния клавиши в массиве
/// @param key код клавишы
/// @param action действие с клавишей (нажата или нет)
void Game::setKey(const int key, const int action)
{
    m_keys[key] = action;
}

/// @brief функция отвечает за инициализацию различных компонентов игры 
/// @return успешно ли произошла инициализиация или нет 
bool Game::init()
{
    ResourceManager::loadJSONResources("res/resources.json");

    m_pSpriteShaderProgram = ResourceManager::getShaderProgram("spriteShader");
    if (!m_pSpriteShaderProgram)
    {
        std::cerr << "Can't find shader program: " << "spriteShader" << std::endl;
        return false;
    }
    m_pSpriteShaderProgram->use();
    m_pSpriteShaderProgram->setInt("tex", 0);

    m_pCurrentGameState = std::make_shared<StartScreen>(ResourceManager::getStartScreen(), this);
    setWindowSize(m_windowSize);

    return true;
}

/// @brief функция получения ширины окошка для дальнейшего построения карты  
/// @return ширина окошка 
unsigned int Game::getCurrentWidth() const
{
    return m_pCurrentGameState->getStateWidth();
}

/// @brief функция получения высоты окошка для дальнейшего построения карты  
/// @return высота окошка 
unsigned int Game::getCurrentHeight() const
{
    return m_pCurrentGameState->getStateHeight();
}
