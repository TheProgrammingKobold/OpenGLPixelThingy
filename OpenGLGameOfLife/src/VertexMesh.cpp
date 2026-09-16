#include "VertexMesh.h"


VertexMesh::VertexMesh()
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    float vertices[] = {
        // positions         // texture coords
         1.0f,  1.0f, 0.0f,  1.0f, 0.0f, // top right
         1.0f, -1.0f, 0.0f,  1.0f, 1.0f, // bottom right
        -1.0f, -1.0f, 0.0f,  0.0f, 1.0f, // bottom left
        -1.0f,  1.0f, 0.0f,  0.0f, 0.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void VertexMesh::bind()
{
    glBindVertexArray(_VAO);
}