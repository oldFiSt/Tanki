#include "Water.h"

#include "../../Resources/ResourceManager.h"
#include "../../Renderer/Sprite.h"

/// @brief конструктор для инициализации объекта воды
/// @param position позиция в игре
/// @param size размер в игре 
/// @param rotation угол поворота 
/// @param layer слой рендеринга 
Water::Water(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : IGameObject(IGameObject::EObjectType::Water, position, size, rotation, layer)
    , m_sprite(ResourceManager::getSprite("water"))
    , m_spriteAnimator(m_sprite)
    , m_blockOffsets { glm::vec2(0, m_size.y / 2.f),
                       glm::vec2(m_size.x / 2.f, m_size.y / 2.f),
                       glm::vec2(0, 0),
                       glm::vec2(m_size.x / 2.f, 0) }
{
    m_colliders.emplace_back(glm::vec2(0), m_size);
}

/// @brief функция для отобржения воды в зависимости от состояния блока
/// @param eBlockLocation состояние воды
void Water::renderBlock(const EBlockLocation eBlockLocation) const
{
    m_sprite->render(m_position + m_blockOffsets[static_cast<size_t>(eBlockLocation)], m_size / 2.f, m_rotation, m_layer, m_spriteAnimator.getCurrentFrame());
}

/// @brief функция для отрисовки воды из четырех блоков 
void Water::render() const
{
    renderBlock(EBlockLocation::TopLeft);
    renderBlock(EBlockLocation::TopRight);
    renderBlock(EBlockLocation::BottomLeft);
    renderBlock(EBlockLocation::BottomRight);
}

/// @brief функция отвечает за обновление состояния объекта воды в игре
/// @param delta время от последнего обновления
void Water::update(const double delta)
{
    m_spriteAnimator.update(delta);
}

/// @brief функция для определения сталкивается ли вода с другим объектом (дальнейшии действия этого объекта с водой)
/// @param objectType объект который столкнулся с водой 
/// @return возвращает является ли этот объект пулей
bool Water::collides(const EObjectType objectType)
 {
     return objectType != IGameObject::EObjectType::Bullet;
 }
