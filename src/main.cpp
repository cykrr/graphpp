#define VKFW_INCLUDE_GL
#include "gui/util.hpp"
#include "gui/window.hpp"
#include "gui/input.hpp"
#include "glad/glad.h"
#include "vkfw/vkfw.hpp"
#include "gui/program.hpp"
int main()
{
    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.openGLProfile = vkfw::OpenGLProfile::eCore;
    hints.contextVersionMajor = 3u;
    hints.contextVersionMinor = 3u;
    hints.focusOnShow = false;

    vkfw::UniqueHandle<vkfw::Window> window;
    
    try {
        window = vkfw::createWindowUnique(800, 600, "pong", hints);
    } catch(std::system_error &e) {
        printf("Exception: %s", e.what());
    }
    window->makeContextCurrent();

    if(!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress)
    ){
        fprintf(stderr, "Error loading GLAD\n");
    }

    Program program("main");
    program.use();

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                    3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };  
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glViewport(0, 0, 800, 600);
    glm::mat4 rotation(1.0f);

    gl::clearColorHex("#202020");
    while(!window->shouldClose()) {
        Input::process(window);
        glClear(GL_COLOR_BUFFER_BIT);

        rotation = glm::rotate(glm::mat4(1.0f), (float)vkfw::getTime(), glm::vec3(1.f, 2.f, 3.f));
        program.setMat4("Model", rotation);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        vkfw::pollEvents();
        window->swapBuffers();
    }
}
