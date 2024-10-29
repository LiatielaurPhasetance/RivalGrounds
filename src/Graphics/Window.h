#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
class Window {
public:
    Window(const char* title);
    ~Window();
    GLFWwindow* getWindow() const { return window; }
    void render();
    void clear();

private:
    GLFWwindow* window;
};

#endif