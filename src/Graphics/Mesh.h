#include <vector>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(const std::vector<std::vector<GLfloat>>& attributeData,
         const std::vector<GLint>& attributeSizes,
         const std::vector<GLuint>& indices);
    ~Mesh();
    void draw() const;

private:
    GLuint VAO;
    std::vector<GLuint> VBOs;
    GLuint EBO;
    GLuint numElements;
    GLuint numAttributes;
    void setupBuffers(const std::vector<std::vector<GLfloat>>& attributeData,
                      const std::vector<GLuint>& indices, const std::vector<GLint>& attributeSizes);
};