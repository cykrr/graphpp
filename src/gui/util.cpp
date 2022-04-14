#include "gui/util.hpp"
namespace gl {
    void clearColorHex(std::string fmt)
    {
        int b,c,d;
        sscanf(fmt.c_str(), "#%02x%02x%02x", &b, &c, &d);
        glClearColor((float)b/0xff,
                (float)c/0xff, 
                (float)d/0xff, 
                1.0f);
    }
}
namespace Time {
    float dt = 0.f;
    double now = 0.f;
    double then = 0.f;
    void update() {
        now = vkfw::getTime();
        dt = now - then; 
        then = now;
    }
}
