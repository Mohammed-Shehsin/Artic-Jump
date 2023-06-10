#include "Fireball.hpp"

Fireball::Fireball(const std::string& texturePath) : Sprites()
{
    setTexture(texturePath);
    speed = getRandomSpeed();
}

void Fireball::moveInDirection()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 0.5f);

    float randomValue = distribution(gen);
    sf::Vector2f movement(randomValue + speed, 0.0f);
    this->move(movement);
}

bool Fireball::checkCollision(const Player& player)
{
    return this->getGlobalBounds().intersects(player.getGlobalBounds());
}

float Fireball::getRandomSpeed()
{
    static std::random_device rd; // Static object to ensure it's initialized only once
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> speedDistribution(0.5f, 2.8f); // Adjust the range of speed as needed

    return speedDistribution(gen);
}
