#include "gui/camera.hpp"

Camera::Camera() {
    this->position = glm::vec3(0.f, 0.f, 3.f),
    this->up = glm::vec3(0.f, 1.f, 0.f),
    this->worldUp = this->up,
    this->yaw = -90.f,
    this->pitch = 0.f,
    this->speed = 2.5f;
    this->sensitivity=0.1f;
    this->zoom = 45.f;
    this->updateVectors();
    this->firstTime = true;
    this->lastX = 0;
    this->lastY = 0;


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


    this->view = glm::lookAt(
            this->position, 
            this->position + this->front, 
            this->up);
}

void Camera::processInput(Direction dir) {
    float deltaSpeed = this->speed * Time::dt;
    switch(dir) {
        case(Forward):
            this->position += this->front * deltaSpeed;
        break;
        case(Backwards):
            this->position -= this->front * deltaSpeed;
        break;
        case(Left):
            this->position-= this->right * deltaSpeed;
        break;
        case(Right):
            this->position += this->right * deltaSpeed;
        break;
        default:
        break;
        
    }
    updateVectors();
}


void Camera::mouse(double x, double y) {

        x *= this->sensitivity;
        y *= this->sensitivity;

        yaw   += x;
        pitch += y;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateVectors();

}

