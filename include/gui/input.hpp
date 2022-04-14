#ifndef INPUT_H
#define INPUT_H
#include "vkfw/vkfw.hpp"
#include "gui/window.hpp"
namespace Input {
    void keyboard(vkfw::UniqueHandle<vkfw::Window> &window);
    namespace Mouse {
        extern int xoffset, lastx, yoffset, lasty;
    }

    void mouse(const vkfw::Window &window, double x, double y);
}
#endif
