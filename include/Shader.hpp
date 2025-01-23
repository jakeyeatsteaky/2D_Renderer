#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>


struct Shader {
public:
    Shader() = default;
    ~Shader() = default;

    Shader(const Shader& copy) = delete;
    Shader& operator=(Shader& other) = delete;

    int construct(const char* vertexSource, const char* fragmentSource);
    unsigned int id;

private:

};

#endif // SHADER_HPP
