#include "Shader.h"

Shader::Shader(const char* vertexSrc, const char* fragmentSrc) {
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    compileShader(vertexShader, vertexSrc);
    compileShader(fragShader, fragmentSrc);
    
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    checkProgramLinking();
    glValidateProgram(program);
}

Shader::~Shader() {
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    glDeleteProgram(program);
}

void Shader::compileShader(GLuint& shader, const char* source) {
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    checkShaderCompilation(shader);
}

void Shader::checkShaderCompilation(GLuint& shader) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "OpenGL::Shader_compilation_error: " << infoLog << "\n";
    }
}

void Shader::checkProgramLinking() {
    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "OpenGL::Program_link_error: " << infoLog << "\n";
    }
}

void Shader::use() {
    glUseProgram(program);
}