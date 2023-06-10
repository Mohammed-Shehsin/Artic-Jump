#ifndef FIREBALL_HPP
#define FIREBALL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Sprites.hpp"
#include "Player.hpp"

class Fireball : public Sprites
{
public:
    Fireball(const std::string& texturePath);
    void moveInDirection();
    bool checkCollision(const Player& player);

private:
    float speed;
    float getRandomSpeed();
};

#endif // FIREBALL_HPP
