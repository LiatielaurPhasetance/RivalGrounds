#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
class Shader {
public:
    Shader(const char* vertexSrc, const char* fragmentSrc);
    ~Shader();
    GLuint getProgram() const { return program; }
    void use();

private:
    GLuint vertexShader, fragShader, program;

    void compileShader(GLuint& shader, const char* source);
    void checkShaderCompilation(GLuint& shader);
    void checkProgramLinking();
};

#endif