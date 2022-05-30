#include "gui/window.hpp"
namespace Window
{ 
    vkfw::UniqueHandle<vkfw::Window> init()
    {
        auto instance = vkfw::initUnique();
        vkfw::WindowHints hints;

        hints.contextVersionMajor = 3u;
        hints.contextVersionMinor = 3u;

        hints.clientAPI = vkfw::ClientAPI::eOpenGL;
        hints.openGLProfile = vkfw::OpenGLProfile::eCore;

        hints.transparentFramebuffer = true;

        hints.floating = true;

        hints.focusOnShow = false;

        try {
            return vkfw::createWindowUnique(FIXED_WIDTH, FIXED_HEIGHT, "new");

        }
        catch (std::system_error &err) {
            char error_message[] = "An error has occured: ";
            strcat(error_message, err.what());
            fprintf(stderr, "%s", error_message);
        }

        // IDK needed for light. Global OpenGL State.
        glEnable(GL_DEPTH_TEST);
    }
}
void Container::addProgram(Program *program) {
    this->programs.push_back(program);
}

mWindow::mWindow() {
    vkfw::init();
    vkfw::WindowHints hints; 

    hints.contextVersionMajor = 3u;
    hints.contextVersionMinor = 3u;
    hints.openGLProfile = vkfw::OpenGLProfile::eCore;
    hints.transparentFramebuffer = true;

    //vkfw extra & wayland bullshit
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.focusOnShow = false;

    vkfw::UniqueHandle<vkfw::Window> window;
    
    try {
        this->window = vkfw::createWindowUnique(800, 600, "pong", hints);
    } catch(std::system_error &e) {
        printf("Exception: %s", e.what());
    }

    this->window->makeContextCurrent();

    if (!gladLoadGLLoader((GLADloadproc)vkfw::getProcAddress)) {
        printf("Error initializing glad\n");
    }
    glEnable(GL_DEPTH_TEST);
}
