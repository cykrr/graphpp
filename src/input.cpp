#include "input.hpp"
namespace Input {
    void process(vkfw::UniqueHandle<vkfw::Window> &window) {
        if(window->getKey(vkfw::Key::eQ)) 
            window->setShouldClose(true);
    }
}
