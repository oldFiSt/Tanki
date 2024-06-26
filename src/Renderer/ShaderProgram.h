#pragma once //чтобы файл подгружался 1 раз 

#include<glad/glad.h>
#include<string>

namespace Renderer {
    class ShaderProgram {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderProgram();
        bool isCompiled() const { return m_isCompiled; }
        void use() const;

        ShaderProgram() = delete; //чтобы нельзя было создать пустой шейдер
        ShaderProgram(ShaderProgram&) = delete;//чтобы нельзя было приравнять шейдеры
        ShaderProgram& operator=(const ShaderProgram&) = delete;//чтобы нельзя было приравнять шейдеры
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;

    private:
        bool createShader(const std::string& source,const GLenum shaderType, GLuint& shaderID);
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };
}
