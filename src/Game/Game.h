#pragma once
 
#include <glm/vec2.hpp>
#include <array>
#include <cstdint>
#include <memory>

class Tank;

class Game{//Отображает игровой мир
public:
    Game(const glm::ivec2& windowSize);
    ~Game();

    void render();
    void update(const uint64_t delta);
    void setkey(const int key,const int action);
    bool init();
    
private:
    std::array<bool, 349> m_keys;//для хранения нажатых кнопок 

    enum class EGameState{
        Active,
        Pause
    };

    glm::ivec2 m_windowSize;
    EGameState m_eCurrentGameState;//Состояние нашего игрового мира
    std::unique_ptr<Tank> m_pTank;//Игровой объект(пока что только один)
}; 