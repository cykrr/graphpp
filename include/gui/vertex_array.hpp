#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "glad/glad.h"
class VertexObject {
    protected:
    virtual void create() = 0;
    virtual void bind() = 0;
    virtual void enable(){};
    GLuint id = 0;
    GLuint dim = 3;
    GLuint vertexCount = 0;
};

class VertexArray : public VertexObject {
public:
    VertexArray();
    void bind();
    void create();
    void enable();
protected:
};

class VertexBuffer : public VertexArray {
public: 
    VertexBuffer();
    void bind();
    void update(float *vertices);
    void allocate(GLuint vertices);
    void create();
protected:
};
#endif
