#include "Mesh.h"

Mesh::Mesh(const std::vector<std::vector<GLfloat>>& attributeData,
           const std::vector<GLint>& attributeSizes,
           const std::vector<GLuint>& indices)
    : numAttributes(attributeData.size()) {
    glCreateVertexArrays(1, &VAO);
    VBOs.resize(numAttributes);
    glCreateBuffers(numAttributes, VBOs.data());
    glCreateBuffers(1, &EBO);
    setupBuffers(attributeData, indices, attributeSizes);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(numAttributes, VBOs.data());
    glDeleteBuffers(1, &EBO);
}

void Mesh::setupBuffers(const std::vector<std::vector<GLfloat>>& attributeData,
                        const std::vector<GLuint>& indices, const std::vector<GLint>& attributeSizes) {
    for (GLuint i = 0; i < numAttributes; ++i) {
        const std::vector<GLfloat>& data = attributeData[i];
        glNamedBufferStorage(VBOs[i], data.size() * sizeof(GLfloat), data.data(), GL_DYNAMIC_STORAGE_BIT);
        glVertexArrayVertexBuffer(VAO, i, VBOs[i], 0, sizeof(GLfloat) * attributeSizes[i]);
        glEnableVertexArrayAttrib(VAO, i);
        glVertexArrayAttribFormat(VAO, i, attributeSizes[i], GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(VAO, i, i);
    }

    numElements = indices.size();
    glNamedBufferStorage(EBO, indices.size() * sizeof(GLuint), indices.data(), GL_DYNAMIC_STORAGE_BIT);
    glVertexArrayElementBuffer(VAO, EBO);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}