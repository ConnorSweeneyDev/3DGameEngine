#pragma once

#include <vector>

#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

class GameObject
{
    public:
        void specifyVertices(std::vector<GLfloat> vertexData, std::vector<GLuint>indexData);

        void setShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);

        void preDraw();

        void draw();

        void moveUp(float speed);
        void moveDown(float speed);
        void moveLeft(float speed);
        void moveRight(float speed);
        void moveForward(float speed);
        void moveBackward(float speed);

        void rotateXPos(float speed);
        void rotateXNeg(float speed);
        void rotateYPos(float speed);
        void rotateYNeg(float speed);
        void rotateZPos(float speed);
        void rotateZNeg(float speed);

        void scaleUp(float speed);
        void scaleDown(float speed);

        void reset();

        void init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scale);

        void cleanup();

    private:
        GLuint vertexArrayObject = 0;
        GLuint vertexBufferObject = 0;
        GLuint indexBufferObject = 0;
        GLuint shaderProgram = 0;
        
        float translationX = 0.0f;
        float translationY = 0.0f;
        float translationZ = 0.0f;
        float rotationX = 0.0f;
        float rotationY = 0.0f;
        float rotationZ = 0.0f;
        float scale = 1.0f;
};
extern GameObject player1;
extern GameObject player2;
