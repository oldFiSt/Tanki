#include "Renderer.h"

namespace RenderEngine {

    /// @brief функция отвечает за отрисовку объектов в OpenGl
    /// @param vertexArray ссылка на объект массива вершин
    /// @param indexBuffer ссылка на объект буфера индексов 
    /// @param shader ссылка на объект шейдерной программы
    void Renderer::draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderProgram& shader)
    {
        shader.use();
        vertexArray.bind();
        indexBuffer.bind();

        glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
    }

    /// @brief функция устанавливает цвет очистки для буфера цвета в OpenGL. 
    /// @param r красный компонент
    /// @param g зеленый компонент
    /// @param b синий компонент
    /// @param a прозрачность
    void Renderer::setClearColor(const float r, const float g, const float b, const float a)
    {
        glClearColor(r, g, b, a);
    }

    /// @brief функция управляет тестированием глубины в OpenGL, включая или отключая его в зависимости от переданного параметра
    /// @param enable нужно ли включить тестирование или нет
    void Renderer::setDepthTest(const bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    /// @brief функция очищает буферы цвета и глубины в OpenGL
    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    /// @brief Функция устанавливает область просмотра (viewport) в OpenGL, определяя левую и нижнюю координаты, а также ширину и высоту области просмотра
    /// @param width  ширина
    /// @param height высота
    /// @param leftOffset левая координата области просмотра
    /// @param bottomOffset нижняя координата области просмотра
    void Renderer::setViewport(const unsigned int width, const unsigned int height, const unsigned int leftOffset, const unsigned int bottomOffset)
    {
        glViewport(leftOffset, bottomOffset, width, height);
    }

    /// @brief функция возвращает строку, содержащую информацию о рендерере, используемом в OpenGL
    /// @return возвращает строку, содержащую информацию о рендерере
    std::string Renderer::getRendererStr()
    {
        return (const char*)glGetString(GL_RENDERER);
    }

    /// @brief функция возвращает строку, содержащую версию рендерера
    /// @return возвращает строку, содержащую информацию о рендерере
    std::string Renderer::getVersionStr()
    {
        return (const char*)glGetString(GL_VERSION);
    }
}