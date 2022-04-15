#ifndef PLANE_H
#define PLANE_H
#include "gui/program.hpp"
class Plane {
    public:
        Plane();

    // we can't use the cube bc they use different vertices!
    // well we "can" but let's first use this plane..
    unsigned int Vao, Vbo;
    // unprojected rectangle vertices:
    static float vertices[18];

    static Program *program;

};
#endif
