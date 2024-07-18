#include "PhysicsEngine.h"

#include "../Game/GameObjects/IGameObject.h"
#include "../Game/GameStates/Level.h"

namespace Physics{
    std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
    std::shared_ptr<Level> PhysicsEngine::m_pCurrentLevel;


    void PhysicsEngine::init()
    {

    }

    void PhysicsEngine::terminate()
    {
        m_dynamicObjects.clear();
        m_pCurrentLevel.reset();
    }

    void PhysicsEngine::setCurrentLevel(std::shared_ptr<Level> pLevel)
    {
        m_pCurrentLevel.swap(pLevel);
        m_dynamicObjects.clear();
        m_pCurrentLevel->initPhysics();
    }

    void PhysicsEngine::update(const double delta)//Свойства игрового объекта, в зависимости от этих свойств(скорость, ускорение) может быть изменена позиция. Например, кничтожить объект при попадании в него пули
    {
        for (auto& currentDynamicObject : m_dynamicObjects)//Пройдёмся по всем динамическим объектам
        {
            if (currentDynamicObject->getCurrentVelocity() > 0)//getCurrentVelocity - это скорость текущего объекта
            {   //танк движется вправо или влево 
                if (currentDynamicObject->getCurrentDirection().x != 0.f)
                {
                    //округление до ближайщего целого
                    currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 4.f + 0.5f)* 4.f);
                }
                else if (currentDynamicObject->getCurrentDirection().y != 0.f)
                {
                    currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f, currentDynamicObject->getCurrentPosition().y);
                }
                 
                const auto newPosition = currentDynamicObject->getCurrentPosition() + currentDynamicObject->getCurrentDirection() * static_cast<float>(currentDynamicObject->getCurrentVelocity() * delta);
                
                std::vector<std::shared_ptr<IGameObject>> objectsToCheck = m_pCurrentLevel->getObjectsInArea(newPosition, newPosition + currentDynamicObject->getSize());
                
                const auto& colliders = currentDynamicObject->getColliders();
                bool hasCollision = false;

                ECollisionDirection dynamicObjectCollisionDirection = ECollisionDirection::Right;
                if (currentDynamicObject->getCurrentDirection().x < 0) dynamicObjectCollisionDirection = ECollisionDirection::Left;
                else if (currentDynamicObject->getCurrentDirection().y > 0) dynamicObjectCollisionDirection = ECollisionDirection::Top;
                else if (currentDynamicObject->getCurrentDirection().y < 0) dynamicObjectCollisionDirection = ECollisionDirection::Bottom;

                ECollisionDirection objectCollisionDirection = ECollisionDirection::Left;
                if (currentDynamicObject->getCurrentDirection().x < 0) objectCollisionDirection = ECollisionDirection::Right;
                else if (currentDynamicObject->getCurrentDirection().y > 0) objectCollisionDirection = ECollisionDirection::Bottom;
                else if (currentDynamicObject->getCurrentDirection().y < 0) objectCollisionDirection = ECollisionDirection::Top;
                
                for (const auto& currentDynamicObjectCollider : colliders)
                {
                    for (const auto& currentObjectToCheck : objectsToCheck)
                    {
                        const auto& collidersToCheck = currentObjectToCheck->getColliders();
                        if (currentObjectToCheck->collides(currentDynamicObject->getObjectType()) && !collidersToCheck.empty())
                        {
                            for (const auto& currentObjectCollider : currentObjectToCheck->getColliders())
                            {
                                if (currentObjectCollider.isActive && hasIntersection(currentDynamicObjectCollider, newPosition, currentObjectCollider, currentObjectToCheck->getCurrentPosition()))
                                {
                                    hasCollision = true;
                                    if (currentObjectCollider.onCollisionCallback)
                                    {
                                        currentObjectCollider.onCollisionCallback(*currentDynamicObject, objectCollisionDirection);
                                    }
                                    if (currentDynamicObjectCollider.onCollisionCallback)
                                    {
                                        currentDynamicObjectCollider.onCollisionCallback(*currentObjectToCheck, dynamicObjectCollisionDirection);
                                    }
                                }
                            }
                        }
                    }
                }

                
                if (!hasCollision)
                {
                    currentDynamicObject->getCurrentPosition() = newPosition;
                }
                else
                {
                    if(currentDynamicObject->getCurrentDirection().x != 0.f)
                    {
                        currentDynamicObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().x/ 8.f + 0.5f) * 8.f, currentDynamicObject->getCurrentPosition().y);
                    }
                    else if (currentDynamicObject->getCurrentDirection().y != 0.f)
                    {
                        currentDynamicObject->getCurrentPosition() = glm::vec2(currentDynamicObject->getCurrentPosition().x, static_cast<unsigned int>(currentDynamicObject->getCurrentPosition().y / 8.f + 0.5f)* 8.f);
                    }
                }
            }
        }   
    }

    void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
    {
        m_dynamicObjects.insert(std::move(pGameObject));
    }
    bool PhysicsEngine::hasIntersection(const Collider& collider1, const glm::vec2& position1,
                                        const Collider& collider2, const glm::vec2& position2)
    {
            const glm::vec2 currentCollider1_bottomLeft_world = collider1.boundingBox.bottomLeft + position1;
            const glm::vec2 currentCollider1_topRight_world = collider1.boundingBox.topRight     + position1;
            
            const glm::vec2 currentCollider2_bottomLeft_world = collider2.boundingBox.bottomLeft + position2;
            const glm::vec2 currentCollider2_topRight_world = collider2.boundingBox.topRight     + position2;
            
            if (currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x)
            {
                return false;
            }
            if (currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x)
            {
                return false;
            }
            if (currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y)
            {
                return false;
            }
            if (currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y)
            {
                return false;
            } 

            return true;   
        
    }
}

