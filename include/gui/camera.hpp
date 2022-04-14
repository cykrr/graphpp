#ifndef CAM_H
#define CAM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "util.hpp"
class Camera {
    public:
    Camera();

    // Possible camera movements to abstract keyboard
    enum Direction {
        Forward, // W
        Backwards, // S
        Left, // A
        Right // D
    };

    glm::mat4 
        projection, view;

    glm::vec3
        position, up, front, right, worldUp;

    float yaw = -90.0f, pitch = 0.f;

    float speed = 2.5f, sensitivity = 0.1f, zoom = 45.0f;

    void resizeCallback(int width, int height);

    void look(void);
    void updateVectors(void);

    void processInput(Direction dir);
};

#endif
