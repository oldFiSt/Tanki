#include "IGameObject.h"


/// @brief конструктор инициализирует базовый класс для всех игровых объектов в игре
/// @param objectType тип объекта (стена, орел, пуля и др.)
/// @param position  позиция в игре
/// @param size размер объекта
/// @param rotation угол поворота 
/// @param layer слой рендеринга
IGameObject::IGameObject(const EObjectType objectType, const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
    : m_pOwner(nullptr)
    , m_position(position)
    , m_targetPosition(position)
    , m_size(size)
    , m_rotation(rotation)
    , m_layer(layer)
    , m_objectType(objectType)
    , m_direction(0, 1.f)
    , m_velocity(0)
{
}

IGameObject::~IGameObject()
{
}


/// @brief функция для проверки на столкновение со своей пулей
/// @param pOwner позиция
void IGameObject::setOwner(IGameObject* pOwner)
{
    m_pOwner = pOwner;
}

/// @brief функция для установки скорости объекта 
/// @param velocity скорость 
void IGameObject::setVelocity(const double velocity)
{
    m_velocity = velocity;
}