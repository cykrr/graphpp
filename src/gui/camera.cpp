#include "gui/camera.hpp"

Camera::Camera() {
    this->position = glm::vec3(0.f, 0.f, 3.f),
    this->up = glm::vec3(0.f, 1.f, 0.f),
    this->worldUp = this->up,
    this->updateVectors(),
    this->yaw = -90.f,
    this->pitch = 0.f,
    this->speed = 2.5f,
    this->sensitivity=0.1f,
    this->zoom = 45.f,
    this->updateVectors();


}

/* Updates the camera's projection matrix, which depends
 * on the width and height of the OpenGL Viewport */

void Camera::resizeCallback(int width, int height) 
{
    this->projection = glm::perspective(
            glm::radians(this->zoom), // Field of View
            (float)width/height,  // Aspect Ratio
            0.1f, 100.f); // zFar. zNear planes.
}

void Camera::updateVectors(void) {

    // Calculate each component of the front vector
    this->front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front.y = sin(glm::radians(pitch));
    this->front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // Normalize as we only need the direction
    this->front = glm::normalize(front);


    // right is a orthogonal vector of front and up
    this->right = glm::normalize(
            glm::cross(
                this->front, 
                this->worldUp));

    // up is a orthogonal vector of front and right;
    this->up = glm::normalize(
            glm::cross(
                this->right,
                this->front
                )
            );


}

void Camera::look(void) {

    this->updateVectors();

    this->view = glm::lookAt(
            this->position, 
            this->position + this->front, 
            this->up);
}

void Camera::processInput(Direction dir) {
    this->speed = this->speed * Time::dt;
    switch(dir) {
        case(Forward):
            this->position += this->front * this->speed;
        break;
        case(Backwards):
        break;
        case(Left):
        break;
        case(Right):
        break;
        default:
        break;
        
    }
}


