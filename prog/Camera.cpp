#include "Camera.hpp" // Camera

Camera camera;

glm::mat4 Camera::getViewMatrix() const { return glm::lookAt(position, position + direction, up); }

void Camera::moveUp(float speed) { position.y += speed; }       // Movements are on the global axes, since the camera cannot rotate
void Camera::moveDown(float speed) { position.y -= speed; }
void Camera::moveLeft(float speed) { position.x -= speed; }
void Camera::moveRight(float speed) { position.x += speed; }
void Camera::moveForward(float speed) { position.z -= speed; }
void Camera::moveBackward(float speed) { position.z += speed; }

void Camera::resetPosition()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::init()
{
    position = glm::vec3(0.0f, 0.0f, 3.0f);
    direction = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}