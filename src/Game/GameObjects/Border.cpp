#include "Border.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

/// @brief Конструктор инициализирует объект границы (border) в игре
/// @param position позиция в игре 
/// @param size размер объекта 
/// @param rotation угол поворота
/// @param layer слой рендеринга
Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(IGameObject::EObjectType::Border, position, size, rotation, layer)
    , m_sprite(ResourceManager::getSprite("border"))
{
    m_colliders.emplace_back(glm::vec2(0), m_size);
}

/// @brief функция для отрисовки объекта границы  
void Border::render() const
{
    m_sprite->render(m_position, m_size, m_rotation, m_layer);
}
