#include "VertexBuffer.h"

namespace RenderEngine {
    /// @brief конструктор  инициализирует объект буфера вершин 
    VertexBuffer::VertexBuffer()
        : m_id(0)
    {
    }

    /// @brief деструктор
    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    /// @brief Оператор присваивания перемещения реализует механизм перемещения для класса VertexBuffer. Этот оператор позволяет перемещать ресурсы из одного объекта VertexBuffer в другой, вместо их копирования
    /// @param vertexBuffer ссылка на объект откуда перемещать ресурсы
    /// @return ссылка на текущий объект
    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
    {
        m_id = vertexBuffer.m_id;
        vertexBuffer.m_id = 0;
        return *this;
    }

    /// @brief Оператор присваивания перемещения реализует механизм перемещения для класса VertexBuffer. Этот оператор позволяет перемещать ресурсы из одного объекта VertexBuffer в другой, вместо их копирования
    /// @param vertexBuffer ссылка на объект откуда перемещать ресурсы
    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    {
        m_id = vertexBuffer.m_id;
        vertexBuffer.m_id = 0;
    }

    /// @brief функция инициализирует объект буфера вершин
    /// @param data указатель на данные которые будут загружены в буфер
    /// @param size размер данных в байтах
    void VertexBuffer::init(const void* data, const unsigned int size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    /// @brief функция обновляет данные в уже существующем объекте буфера вершин
    /// @param data указатель на новые данные
    /// @param size размер новых данных в байтах
    void VertexBuffer::update(const void* data, const unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    /// @brief функция привязывает объект буфера вершин
    void VertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    /// @brief функция отвязывает объект буфера вершин
    void VertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}