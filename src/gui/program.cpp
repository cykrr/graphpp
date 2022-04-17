#include "gui/program.hpp"

void checkErrors(unsigned int id, std::string type)
{
    GLint success; GLchar log[512];
    if(type != "program") {

        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id, 512, NULL, log);
            std::cout << "Error compiling " << type << "\n" 
                << log << '\n';
        } 
   } else  {
       glGetProgramiv(id, GL_LINK_STATUS, &success);
       if(!success){
           glGetProgramInfoLog(id, 512, NULL, log);
           std::cout << log << '\n';
       }
   }
    if (!success) {
        exit(1);
    }
}

void Program::use()
{
    glUseProgram(this->id);
}

Program::Program(std::string name)
{
    unsigned int vertex, frag;

    std::ifstream vertexFile, fragFile;
    std::stringstream vertexStream, fragStream;
    std::string tmp;

    const char *src;

    vertexFile.open("./res/shaders/" + name + ".vert");
    fragFile.open("./res/shaders/" + name + ".frag");

    if (!(vertexFile && fragFile)){
        std::cout << "Shader " + name + " not found\n";
        exit(1);
    }

    vertexStream << vertexFile.rdbuf();
    fragStream << fragFile.rdbuf();

    vertexFile.close(); fragFile.close();

    tmp = vertexStream.str();
    src = tmp.c_str();

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &src, NULL);
    glCompileShader(vertex);
    checkErrors(vertex, "vertex");

    tmp = fragStream.str();
    src = tmp.c_str();

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &src, NULL);
    glCompileShader(frag);
    checkErrors(frag, "fragment");

    this->id = glCreateProgram();

    glAttachShader(id, vertex);
    glAttachShader(id, frag);

    glLinkProgram(id);

    checkErrors(id, "program");

    glDeleteShader(vertex);
    glDeleteShader(frag);
}

