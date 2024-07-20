#include "Timer.h"

/// @brief Функция конструктора Timer инициализирует объект Timer
Timer::Timer()
    : m_isRunning(false)
    , m_timeLeft(0)
{

}

/// @brief функция обновляет состояние таймера, уменьшая оставшееся время на значение
/// @param delta значение с последнего обновления 
void Timer::update(const double delta)
{
    if (m_isRunning)
    {
        m_timeLeft -= delta;
        if (m_timeLeft <= 0)
        {
            m_isRunning = false;
            m_callback();
        }
    }
}

/// @brief функция инициализирует таймер, устанавливая его продолжительность и активируя его
/// @param duration значение, представляющее продолжительность таймера в секундах 
void Timer::start(const double duration)
{
    m_timeLeft = duration;
    m_isRunning = true;
}

/// @brief функция устанавливает функцию обратного вызова для таймер
/// @param callback функция обратного вызова, которая будет вызвана, когда таймер истечет. 
void Timer::setCallback(std::function<void()> callback)
{
    m_callback = callback;
}