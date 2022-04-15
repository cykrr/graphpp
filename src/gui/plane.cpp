#include "gui/plane.hpp"

Plane::Plane(){
    //initialize shaders if we haven't
    if(!this->program) {
        this->program = new Program("plane");
        this->program->use();
        this->program->setMat4("View", glm::mat4(1.f));
        this->program->setMat4("Projection", glm::mat4(1.f));
    }
    // create buffers
    glCreateVertexArrays(1, &Vao);
    glGenBuffers(1, &Vbo);

    // bind buffers
    glBindVertexArray(Vao);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    
    // send vertex data  to vbo
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), 
            this->vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
            3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);
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
