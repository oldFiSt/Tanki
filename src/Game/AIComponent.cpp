#include "AIComponent.h"
#include "GameObjects/Tank.h"

/// @brief конструктор для создания вражеского танка 
/// @param pParentTank указатель на танк 
AIComponent::AIComponent(Tank* pParentTank)//Конструктор
    : m_pParentTank(pParentTank)
{

}

/// @brief функция для чтобы вражеский танк стрелял во время каждого последующего кадра
/// @param delta время с последнего кадра
void AIComponent::update(const double delta)
{
    m_pParentTank->fire();//На каждый update танк будет делать выстрел
}