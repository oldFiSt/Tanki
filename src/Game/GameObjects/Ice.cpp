#include "Ice.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

/// @brief Конструктор инициализирует объект льда в игре
/// @param position позиция в игре
/// @param size размер
/// @param rotation угол поворота 
/// @param layer слой рендеринга 
Ice::Ice(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(IGameObject::EObjectType::Ice, position, size, rotation, layer)
    , m_sprite(ResourceManager::getSprite("ice"))
    , m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
                       glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(m_size.x / 2.f, 0) }
{
}

/// @brief функция отвечает за отрисовку отдельного блока льда в игре
/// @param eBlockLocation тип льда (какой блок)
void Ice::renderBlock(const EBlockLocation eBlockLocation) const
{
    m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer);
}

/// @brief функция для отрисовки льда из четырех блоков 
void Ice::render() const
{
    renderBlock(EBlockLocation::TopLeft);
    renderBlock(EBlockLocation::TopRight);
    renderBlock(EBlockLocation::BottomLeft);
    renderBlock(EBlockLocation::BottomRight);
}
