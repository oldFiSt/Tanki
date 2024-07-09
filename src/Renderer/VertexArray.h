#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include<glad/glad.h>

namespace RenderEngine {

    class VertexArray {
    public:
        VertexArray();//Конструктор
        ~VertexArray();//Деструктор

        VertexArray(const VertexArray&) = delete;
        VertexArray& operator = (const VertexArray&) = delete;
        VertexArray& operator = (VertexArray&& vertexArray) noexcept;
        VertexArray(VertexArray&& vertexArray) noexcept;

        void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
        void bind() const;//функция будет биндить наш буфер
        void unbind() const;//Функция будет отвязывать наш буфер

    private:
        GLuint m_id = 0;
        unsigned int m_elementsCount = 0;
    };


}