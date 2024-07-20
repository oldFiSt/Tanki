#include "Texture2D.h"

namespace RenderEngine {

    /// @brief Конструктор инициализирует объект текстуры 2D в OpenGL. 
    /// @param width ширина     
    /// @param height высота
    /// @param data указатель на данные текстуры 
    /// @param channels количество каналов (три или четрые)
    /// @param filter режим фильтрации текстуры 
    /// @param wrapMode режим обертки текстуры 
    Texture2D::Texture2D(const GLuint width, GLuint height,
        const unsigned char* data,
        const unsigned int channels,
        const GLenum filter,
        const GLenum wrapMode)
        : m_width(width)
        , m_height(height)
    {
        switch (channels)
        {
        case 4:
            m_mode = GL_RGBA;
            break;
        case 3:
            m_mode = GL_RGB;
            break;
        default:
            m_mode = GL_RGBA;
            break;
        }

        glGenTextures(1, &m_ID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_mode, m_width, m_height, 0, m_mode, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /// @brief Оператор присваивания перемещения реализует механизм перемещения для класса Texture2D.
    /// @param texture2d объект откуда перемещаются ресурсы
    /// @return возвращает ссылку на текущий объект
    Texture2D& Texture2D::operator=(Texture2D&& texture2d)
    {
        glDeleteTextures(1, &m_ID);
        m_ID = texture2d.m_ID;
        texture2d.m_ID = 0;
        m_mode = texture2d.m_mode;
        m_width = texture2d.m_width;
        m_height = texture2d.m_height;
        return *this;
    }

    /// @brief Конструктор перемещения реализует механизм перемещения для класса. Позволяет создавать новый объект
    /// @param texture2d ссылка на другой объект
    Texture2D::Texture2D(Texture2D&& texture2d)
    {
        m_ID = texture2d.m_ID;
        texture2d.m_ID = 0;
        m_mode = texture2d.m_mode;
        m_width = texture2d.m_width;
        m_height = texture2d.m_height;
    }

    /// @brief деструктор
    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &m_ID);
    }

    //Функция активирует текстуру 2D в OpenGL, связывая ее с текущим контекстом, чтобы она могла быть использована для рендеринга.
    void Texture2D::bind() const
    {
        glBindTexture(GL_TEXTURE_2D, m_ID);
    }

    /// @brief функция добавляет под-текстуру в объект Texture2D, используя заданные координаты UV
    /// @param name имя под-текстуры, которое будет использоваться для ее идентификации
    /// @param leftBottomUV координаты нижнего левого угла под-текстуры в UV-пространстве
    /// @param rightTopUV координаты верхнего правого угла под-текстуры в UV-пространстве
    void Texture2D::addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV)
    {
        m_subTextures.emplace(std::move(name), SubTexture2D(leftBottomUV, rightTopUV));
    }

    /// @brief возвращает ссылку на под-текстуру, идентифицированную по имени
    /// @param name ключ, по которому выполняется поиск.
    /// @return возвращает сслыку на объект 
    const Texture2D::SubTexture2D& Texture2D::getSubTexture(const std::string& name) const
    {
        auto it = m_subTextures.find(name);
        if (it != m_subTextures.end())
        {
            return it->second;
        }
        const static SubTexture2D defaultSubTexture;
        return defaultSubTexture;
    }
}