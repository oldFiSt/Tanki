#pragma once
class Tank;
/// @brief Чтобы изменять состояние компонента искусственного интелекта
class AIComponent
{
public:
    AIComponent(Tank* pParentTank);//Конструктор, он будет принимать указатель на класс танка, чтобы иметь к нему доступ

    void update(const double delta);
private:
    Tank* m_pParentTank;
};