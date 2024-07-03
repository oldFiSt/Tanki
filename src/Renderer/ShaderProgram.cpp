#include "ShaderProgram.h"

#include<glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Renderer{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderId;
        if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId))
        {
            std::cerr << "VERTEX SHADER compile time error " << std::endl;
            return;
        }
        GLuint fragmentShaderId;
        if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId))
        {
            std::cerr << "FRAGMENT SHADER compile time error " << std::endl;
            glDeleteShader(vertexShaderId);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderId);
        glAttachShader(m_ID, fragmentShaderId);
        glLinkProgram(m_ID);
        
        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar Infolog [1024];
            glGetShaderInfoLog(m_ID, 1024, nullptr, Infolog);
            std::cerr<<"ERROR::SHADER: Link time error :\n" << Infolog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);
    }
    
    bool ShaderProgram::createShader(const std::string& source,const GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1 , &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success){
            GLchar Infolog [1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, Infolog);
            std::cerr<<"ERROR::SHADER: Compile time error :\n" << Infolog << std::endl;
            return false;
        }
        return true;    
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }

    void ShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }

    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    } 

    void ShaderProgram::setInt(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));//Здесь glUniformMatrix4fv - f - этот идёт за float, а v - это то, что мы передаём в вектор згачений
    }

}