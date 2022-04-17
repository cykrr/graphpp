#include "gui/plane.hpp"

Plane::Plane(){
    //initialize shaders if we haven't
    if(!this->program) {
        this->program = new Program("plane"),
        this->program->use(),
        this->program->setMat4("View", glm::mat4(1.f)),
        this->program->setMat4("Projection", glm::mat4(1.f));
    }
    this->createBuffers(),
        this->bindBuffers(),
        this->allocateVertexData(),
        this->enableAttribArray();
}

// Initialize static member
float Plane::vertices[18] = {
         1.f,  1.f, 0.f,
        -1.f, -1.f, 0.f,
        -1.f,  1.f, 0.f,
        -1.f, -1.f, 0.f,
         1.f,  1.f, 0.f,
         1.f, -1.f, 0.f
    };


Program *Plane::program = NULL;

void Plane::createBuffers() {
    glGenVertexArrays(1, &Vao);
    glGenBuffers(1, &Vbo);
}

void Plane::bindBuffers() {
    glBindVertexArray(this->Vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->Vbo);
}

void Plane::enableAttribArray() {
    this->bindBuffers();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Plane::allocateVertexData() {
    this->bindBuffers();
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), this->vertices,
            GL_STATIC_DRAW);
}

void Plane::draw(){
	this->program->use();
        this->bindBuffers();

	glBufferSubData(GL_ARRAY_BUFFER, 0, 
                sizeof(float)*18, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
