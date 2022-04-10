#define VKFW_INCLUDE_GL
#include "vkfw/vkfw.hpp"
#include "gui/window.hpp"
#include "input.hpp"
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

    while(!window->shouldClose()) {
        Input::process(window);
        vkfw::pollEvents();
        window->swapBuffers();
    }
}
