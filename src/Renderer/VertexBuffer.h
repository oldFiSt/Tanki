#pragma once

#include<glad/glad.h>

namespace RenderEngine {

    class VertexBuffer {
    public:
        VertexBuffer();//Конструктор
        ~VertexBuffer();//Деструктор

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer& operator = (const VertexBuffer&) = delete;
        VertexBuffer& operator = (VertexBuffer&& vertexBiffer) noexcept;
        VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

        void init(const void* data, const unsigned int size);
        void update(const void* data, const unsigned int size) const;
        void bind() const;//функция будет биндить наш буфер
        void unbind() const;//Функция будет отвязывать наш буфер

    private:
        GLuint m_id;
    };


}