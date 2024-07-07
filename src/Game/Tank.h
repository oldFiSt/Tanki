#pragma once 

#include <glm/vec2.hpp>
#include <memory>

namespace Renderer {
    class AnimatedSprite;
}


class Tank{
public:
    //для ориентации танка 
    enum class EOrientation {
        Top,
        Bottom,
        Left,
        Right
    };

    Tank(std::shared_ptr<Renderer::AnimatedSprite> pSprite, const float velocity, const glm::vec2& position);
 
    void render() const;
    void setOrientation(const EOrientation eOrientation);
    void move(const bool move);//для отслеживания нажатия кнопки 
    void update(const uint64_t delta);
    
private:
    EOrientation m_eOrientation; //для вычисления куда будет лететь снаряд 
    std::shared_ptr<Renderer::AnimatedSprite> m_pSprite;
    bool m_move;
    float m_velocity;// скорость 
    glm::vec2 m_position;
    glm::vec2 m_moveOffset;//вектор по которому будет двигаться танк 
};