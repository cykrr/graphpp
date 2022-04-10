#define VKFW_INCLUDE_GL
#include "gui/util.hpp"
#include "gui/window.hpp"
#include "gui/input.hpp"
#include "glad/glad.h"
#include "vkfw/vkfw.hpp"
int main()
{
    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.openGLProfile = vkfw::OpenGLProfile::eCore;
    hints.contextVersionMajor = 3u;
    hints.contextVersionMinor = 3u;

    
    auto window = vkfw::createWindowUnique(800, 600, "pong", hints);
    window->makeContextCurrent();

    if(!gladLoadGLLoader(
        (GLADloadproc)vkfw::getProcAddress)
    ){
        fprintf(stderr, "Error loading GLAD\n");
    }

    glViewport(0, 0, 800, 600);



    gl::clearColorHex("#202020");
    while(!window->shouldClose()) {
        Input::process(window);
        glClear(GL_COLOR_BUFFER_BIT);

        vkfw::pollEvents();
        window->swapBuffers();
    }
}
