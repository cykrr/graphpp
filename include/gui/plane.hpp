#ifndef PLANE_H
#define PLANE_H
#include "gui/program.hpp"
class Plane {
public:
    Plane();
    // unprojected rectangle vertices: (-1 -1 to 1 1)
    static float vertices[18];
    void draw();

    // we can't use the cube bc they use different vertices!
    // well we "can" but let's first use this plane..
    unsigned int Vao, Vbo;
    static Program *program;
private:

    void createBuffers();
    void bindBuffers();
    void enableAttribArray();
    void allocateVertexData();

};
#endif
