#include <iostream>
#include <vector>
#include <incbin.h>
#include "Graphics/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"

INCTXT(DefaultVert, "shaders/default.vert");
INCTXT(DefaultFrag, "shaders/default.frag");

int main () {
    Window window("Game");

    std::vector<std::vector<GLfloat>> attributeData = {
        // Positions
        {
            -1.0f, -1.0f, 0.0f,
             1.0f, -1.0f, 0.0f,
             0.0f,  1.0f, 0.0f
        },
        // Colors
        {
             1.0f, 0.0f, 0.0f,
             0.0f, 1.0f, 0.0f,
             0.0f, 0.0f, 1.0f
        }
    };
    std::vector<int> attributeSizes = {3, 3};
    std::vector<unsigned int> indices = {0, 1, 2};

    Mesh mesh(attributeData, attributeSizes, indices);

    Shader shader(gDefaultVertData, gDefaultFragData);
    shader.use();

    while (!glfwWindowShouldClose(window.getWindow())) {
        window.clear();
        mesh.draw();
        window.render();
    };

    exit(EXIT_SUCCESS);
}