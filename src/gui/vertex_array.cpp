#include "gui/vertex_array.hpp"
#include "glad/glad.h"
void VertexArray::create() {
    glGenVertexArrays(1, &this->id);
}

void VertexBuffer::create() {
    glGenBuffers(1, &this->id);
}

void VertexArray::bind() {
    glBindVertexArray(this->id);
}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
}

void VertexArray::enable() {
    this->bind();
    glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void VertexBuffer::allocate(GLuint vertices) {
    this->bind();
    this->vertexCount = vertices;
    glBufferData(GL_ARRAY_BUFFER, this->dim * vertices, nullptr,  GL_STATIC_DRAW);
}

void VertexBuffer::update(float *vertices) {
    glBufferSubData(GL_ARRAY_BUFFER, 0, 
            sizeof(float) * this->vertexCount * this->dim, vertices);
}


VertexArray::VertexArray(){}
VertexBuffer::VertexBuffer(){}
