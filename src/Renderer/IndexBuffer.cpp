#include "IndexBuffer.h"

namespace RenderEngine {
    /// @brief конструктор инициализирует объект индексации в графической системе 
    IndexBuffer::IndexBuffer()
        : m_id(0)
        , m_count(0)
    {
    }
    /// @brief деструктор   
    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    /// @brief функция реализует оператор присваивания для перемещения 
    /// @param indexBuffer ресурсы из временного объекта 
    /// @return возвращает текущее перемещение
    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
    {
        m_id = indexBuffer.m_id;
        indexBuffer.m_id = 0;
        m_count = indexBuffer.m_count;
        indexBuffer.m_count = 0;
        return *this;
    }

    /// @brief конструктор перемещения  реализует механизм перемещения для класса IndexBuffer
    /// @param indexBuffer временный объект 
    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
    {
        m_id = indexBuffer.m_id;
        indexBuffer.m_id = 0;
        m_count = indexBuffer.m_count;
        indexBuffer.m_count = 0;
    }

    /// @brief функция инициализирует объект индексации, создавая и заполняя буфер индексов в OpenGL. 
    /// @param data указатель на данные которые будут загружены в буфер
    /// @param count количество индексов которые будут загружены 
    void IndexBuffer::init(const void* data, const unsigned int count)
    {
        m_count = count;
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
    }
    /// @brief функция привязывает буфер индексов к OpenGl
    void IndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
    /// @brief функция отвязывает буфер индексов от OpenGl
    void IndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}