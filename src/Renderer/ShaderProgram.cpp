#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace RenderEngine {
    /// @brief конструктор отвечает за создание и компиляцию шейдреной программы OpenGl
    /// @param vertexShader cтрока, содержащая код вершинного шейдера
    /// @param fragmentShader cтрока, содержащая код фрагментного шейдера
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fragmentShaderID;
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        m_ID = glCreateProgram();
        glAttachShader(m_ID, vertexShaderID);
        glAttachShader(m_ID, fragmentShaderID);
        glLinkProgram(m_ID);

        GLint success;
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
        }
        else
        {
            m_isCompiled = true;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    /// @brief функция отвечает за создание, компиляцию и проверку шейдера в OpenGL.
    /// @param source исходный код шейдера 
    /// @param shaderType тип шейдера (GL_VERTEX_SHADER или GL_FRAGMENT_SHADER)
    /// @param shaderID ссылка на переменную, в которую будет записан иентификатор
    /// @return возвращает успешно ли был загружен шейдер
    bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr);
        glCompileShader(shaderID);

        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetProgramInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }
    /// @brief деструктор 
    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(m_ID);
    }
    /// @brief Функция активирует шейдерную программу в OpenGL, позволяя использовать ее для рендеринга объектов.
    void ShaderProgram::use() const
    {
        glUseProgram(m_ID);
    }

    /// @brief Оператор присваивания перемещения реализует механизм перемещения для класса ShaderProgram.
    /// @param shaderProgram ссылка для перемещения ресурсов из временного объекта 
    /// @return возвращает ссылку на текущий объект ShaderProgram, который был модифицирован.
    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
    {
        glDeleteProgram(m_ID);
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
        return *this;
    }

    /// @brief Конструктор перемещения реализует механизм перемещения для класса ShaderProgram
    /// @param shaderProgram ссылка для перемещения ресурсов из временного объекта 
    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        m_ID = shaderProgram.m_ID;
        m_isCompiled = shaderProgram.m_isCompiled;

        shaderProgram.m_ID = 0;
        shaderProgram.m_isCompiled = false;
    }

    /// @brief Функция устанавливает значение для переменной типа int в шейдерной программе.
    /// @param name имя переменной в шейдере
    /// @param value значение которое нужно установить
    void ShaderProgram::setInt(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    /// @brief Функция устанавливает значение для переменной типа float в шейдерной программе OpenGL.
    /// @param name Имя переменной в шейдере, для которой нужно установить значение.
    /// @param value Значение, которое будет установлено для переменной.
    void ShaderProgram::setFloat(const std::string& name, const GLfloat value)
    {
        glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
    }

    /// @brief Функция  устанавливает значение для переменной типа mat4 в шейдерной программе OpenGL. 
    /// @param name  Имя переменной в шейдере, для которой нужно установить значение.
    /// @param matrix Матрица, которая будет установлена для переменной.
    void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
