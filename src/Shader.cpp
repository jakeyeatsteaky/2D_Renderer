#include <SDL2/SDL.h>

#include "Shader.hpp"
#include "Utility.hpp"
#include "glad.h"

int Shader::construct(const char *vertexSource, const char *fragmentSource)
{
    // return 1 on success;
    int success = -1;
    char infoLog[512];
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        ERR("Error compiling shader: ", infoLog);
        return success;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        ERR("Error compiling shader: ", infoLog);
        return success;
    }

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        ERR("Error linking shader program: ", infoLog);
        return success;
    }

    this->_id = program;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return success;
}