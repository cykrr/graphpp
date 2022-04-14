#include "gui/input.hpp"
namespace Input {
    void keyboard(vkfw::UniqueHandle<vkfw::Window> &window) {
        Container *container = static_cast<Container*>(window->getUserPointer());
        if(window->getKey(vkfw::Key::eQ)) 
            window->setShouldClose(true);
        if(window->getKey(vkfw::Key::eW)){
            container->camera->processInput(Camera::Direction::Forward);
        }
        if(window->getKey(vkfw::Key::eS))
            container->camera->processInput(Camera::Direction::Backwards);
        if(window->getKey(vkfw::Key::eA))
            container->camera->processInput(Camera::Direction::Left);
        if(window->getKey(vkfw::Key::eD))
            container->camera->processInput(Camera::Direction::Right);
    }

    int Input::Mouse::lastx = 0,
        Input::Mouse::lasty   = 0,
        Input::Mouse::xoffset = 0,
        Input::Mouse::yoffset = 0;

    void mouse(const vkfw::Window &window, double x, double y) {
        Mouse::xoffset = x - Mouse::lastx;
        Mouse::yoffset = y - Mouse::lasty;
        Mouse::lastx = x;
        Mouse::lasty = y;
        Container *container = static_cast<Container*>(window.getUserPointer());
        container->camera->mouse(Mouse::xoffset, -Mouse::yoffset);
        
    }

}
