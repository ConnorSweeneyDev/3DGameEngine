#include "Player.hpp"

PlayerList players;

Player::Player(std::string name) { this->name = name; }

const std::string& Player::getName() const { return name; }
GLuint& Player::getVertexArrayObject() { return vertexArrayObject; }
GLuint& Player::getVertexBufferObject() { return vertexBufferObject; }
GLuint& Player::getIndexBufferObject() { return indexBufferObject; }
GLuint& Player::getShaderProgram() { return shaderProgram; }
float& Player::getTranslationX() { return translationX; }
float& Player::getTranslationY() { return translationY; }
float& Player::getTranslationZ() { return translationZ; }
float& Player::getRotationX() { return rotationX; }
float& Player::getRotationY() { return rotationY; }
float& Player::getRotationZ() { return rotationZ; }
float& Player::getScaleX() { return scaleX; }
float& Player::getScaleY() { return scaleY; }
float& Player::getScaleZ() { return scaleZ; }

void Player::MoveUp() { translationY += speed * time_util.getDeltaTime(); }
void Player::MoveDown() { translationY -= speed * time_util.getDeltaTime(); }
void Player::MoveLeft() { translationX -= speed * time_util.getDeltaTime(); }
void Player::MoveRight() { translationX += speed * time_util.getDeltaTime(); }
void Player::MoveForward() { translationZ -= speed * time_util.getDeltaTime(); }
void Player::MoveBackward() { translationZ += speed * time_util.getDeltaTime(); }

void Player::ResetPosition()
{
    translationX = initialPosition[0];
    translationY = initialPosition[1];
    translationZ = initialPosition[2];
    rotationX = initialPosition[3];
    rotationY = initialPosition[4];
    rotationZ = initialPosition[5];
    scaleX = initialPosition[6];
    scaleY = initialPosition[7];
    scaleZ = initialPosition[8];
}
void Player::ResetStats()
{
    health = initialStats[0];
    speed = initialStats[1];
}

void Player::init(
                  float health, float speed,
                  std::vector<float> defaultPosition
                 )
{
    initialPosition.push_back(this->translationX = defaultPosition[0]);
    initialPosition.push_back(this->translationY = defaultPosition[1]);
    initialPosition.push_back(this->translationZ = defaultPosition[2]);
    initialPosition.push_back(this->rotationX = defaultPosition[3]);
    initialPosition.push_back(this->rotationY = defaultPosition[4]);
    initialPosition.push_back(this->rotationZ = defaultPosition[5]);
    initialPosition.push_back(this->scaleX = defaultPosition[6]);
    initialPosition.push_back(this->scaleY = defaultPosition[7]);
    initialPosition.push_back(this->scaleZ = defaultPosition[8]);

    initialStats.push_back(this->health = health);
    initialStats.push_back(this->speed = speed);
}

PlayerPtr getPlayerByName(const std::string &name)
{
    for (auto &player : players)
    {
        if (player->getName() == name)
        {
            return player;
        }
    }
    return nullptr;
}
