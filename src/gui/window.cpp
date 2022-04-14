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

        hints.scaleToMonitor = vkfw::eTrue;

        hints.floating = vkfw::eTrue;

        hints.focusOnShow = vkfw::eFalse;

        try {
            return vkfw::createWindowUnique(FIXED_WIDTH, FIXED_HEIGHT, "new");

        }
        catch (std::system_error &err) {
            char error_message[] = "An error has occured: ";
            strcat(error_message, err.what());
            fprintf(stderr, "%s", error_message);
        }
    }
}
void Container::addProgram(Program *program) {
    this->programs.push_back(program);
}
