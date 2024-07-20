#include "VertexArray.h"

namespace RenderEngine {
    /// @brief Конструктор инициализирует объект массива вершин 
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    /// @brief деструктор
    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    /// @brief Оператор присваивания перемещения реализует механизм перемещения для класса VertexArray. 
    /// @param vertexArray ссылка на объект откуда будут перемещаться ресурсы 
    /// @return ссылка на текущий объект
    VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
    {
        m_id = vertexArray.m_id;
        vertexArray.m_id = 0;
        return *this;
    }

    /// @brief конструктор перемещения реализует механизм перемещения для класса
    /// @param vertexArray ссылка на объект откуда будут перемещаться ресурсы 
    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
    {
        m_id = vertexArray.m_id;
        vertexArray.m_id = 0;
    }

    /// @brief функция активирует объект массива вершин
    void VertexArray::bind() const
    {
        glBindVertexArray(m_id);
    }

    /// @brief функция отвязывает объект массива вершин
    void VertexArray::unbind() const
    {
        glBindVertexArray(0);
    }

    /// @brief функция добавляет буфер вершин к объекту массива вершин и настраивает атрибуты вершин в соответствии с заданным макет
    /// @param vertexBuffer ссылка на объект буфера вершин
    /// @param layout ссылка на объект, описывающий макет атрибутов вершин
    void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
    {
        bind();
        vertexBuffer.bind();
        const auto& layoutElements = layout.getLayoutElements();
        GLbyte* offset = nullptr;
        for (unsigned int i = 0; i < layoutElements.size(); ++i)
        {
            const auto& currentLayoutElement = layoutElements[i];
            GLuint currentAttribIndex = m_elementsCount + i;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);
            offset += currentLayoutElement.size;
        }
        m_elementsCount += static_cast<unsigned int>(layoutElements.size());
    }
}