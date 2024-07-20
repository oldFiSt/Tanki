#include "VertexBufferLayout.h"

namespace RenderEngine {
    /// @brief конструктор инициализирует объект, который используется для определения макета атрибутов вершин в буфере вершин
    VertexBufferLayout::VertexBufferLayout()
        : m_stride(0)
    {}

    /// @brief Функция V резервирует место в векторе для добавления count элементов макета атрибутов
    /// @param count количество элементов
    void VertexBufferLayout::reserveElements(const size_t count)
    {
        m_layoutElments.reserve(count);
    }

    /// @brief Функция добавляет элемент макета атрибута с типом данных float в вектор , который хранит информацию о том, как организованы данные в буфере вершин
    /// @param count количество компонентов 
    /// @param normalized указывает нужно ли нормализовать данные
    void VertexBufferLayout::addElementLayoutFloat(const unsigned int count, const bool normalized)
    {
        m_layoutElments.push_back({ static_cast<GLint>(count), GL_FLOAT, normalized, count * static_cast<unsigned int>(sizeof(GLfloat)) });
        m_stride += m_layoutElments.back().size;
    }
}
