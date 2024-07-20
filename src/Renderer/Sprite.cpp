#include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderEngine {
    /// @brief Конструктор инициализирует объект спрайта, который представляет изображение, используя текстуру, шейдерную программу и координаты вершин.
    /// @param pTexture указатель на объект текстуры, который будет использоваться спрайтом.
    /// @param initialSubTexture имя под-текстуры, которую нужно использовать.
    /// @param pShaderProgram указатель на шейдерную программу, которая будет применяться к спрайту.
    Sprite::Sprite(std::shared_ptr<Texture2D> pTexture,
                   std::string initialSubTexture,
                   std::shared_ptr<ShaderProgram> pShaderProgram)
        : m_pTexture(std::move(pTexture))
        , m_pShaderProgram(std::move(pShaderProgram))
        , m_lastFrameId(0)
    {
        const GLfloat vertexCoords[] = {
            // 1---2
            // | / |
            // 0  -3

            // X  Y
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f
        };

        auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

        const GLfloat textureCoords[] = {
            // U  V
            subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
            subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,   subTexture.rightTopUV.y,
            subTexture.rightTopUV.x,   subTexture.leftBottomUV.y,
        };

        const GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

        m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.addElementLayoutFloat(2, false);
        m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

        m_indexBuffer.init(indices, 6);

        m_vertexArray.unbind();
        m_indexBuffer.unbind();
    }

    Sprite::~Sprite()
    {
    }

    /// @brief функция для отрисовки спрайта на экране, используя представленные параметры
    /// @param position позиция в игре 
    /// @param size размер
    /// @param rotation угол поворота
    /// @param layer слой рендеринга
    void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer, const size_t frameId) const
    {
        if (m_lastFrameId != frameId)
        {
            m_lastFrameId = frameId;
            const FrameDescription& currentFrameDescription = m_framesDescriptions[frameId];

            const GLfloat textureCoords[] = {
                // U  V
                currentFrameDescription.leftBottomUV.x, currentFrameDescription.leftBottomUV.y,
                currentFrameDescription.leftBottomUV.x, currentFrameDescription.rightTopUV.y,
                currentFrameDescription.rightTopUV.x,   currentFrameDescription.rightTopUV.y,
                currentFrameDescription.rightTopUV.x,   currentFrameDescription.leftBottomUV.y,
            };

            m_textureCoordsBuffer.update(textureCoords, 2 * 4 * sizeof(GLfloat));
        }

        m_pShaderProgram->use();

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
        model = glm::scale(model, glm::vec3(size, 1.f));

        m_pShaderProgram->setMatrix4("modelMat", model);
        m_pShaderProgram->setFloat("layer", layer);

        glActiveTexture(GL_TEXTURE0);
        m_pTexture->bind();

        Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
    }

    /// @brief функция для добалвение кадров анимации спрайтов, используя вектор описания кадров
    /// @param framesDescriptions вектор описания кадров
    void Sprite::insertFrames(std::vector<FrameDescription> framesDescriptions)
    {
        m_framesDescriptions = std::move(framesDescriptions);
    }

    /// @brief функция для подсчета продолжительности кадра анимации спрайта
    /// @param frameId индекс кадра для которого нужно получить продолжительность 
    /// @return возвращает продолжительность  определенного кадра анимации спрайта 
    double Sprite::getFrameDuration(const size_t frameId) const
    {
        return m_framesDescriptions[frameId].duration;
    }

    /// @brief функция для подсчета количества кадров которые содержит спрайт
    /// @return возвращает количество кадров которые содержит спрайт
    size_t Sprite::getFramesCount() const
    {
        return m_framesDescriptions.size();
    }
}