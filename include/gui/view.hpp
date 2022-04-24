#ifndef VIEW_H
#define VIEW_H
#include <string>
#include "gui/program.hpp"
#include "gui/vertex_array.hpp"
class View {
    std::string name = "View";
    Program *program;
    VertexArray vao;
    VertexBuffer vbo;
};
#endif
