#ifndef PICKABLE_HPP
#define PICKABLE_HPP

#include <SFML/Graphics.hpp>
#include "Sprites.hpp"
#include "Player.hpp"

class Pickable : public Sprites
{
public:
    Pickable(const std::string& texturePath);
    bool checkCollision(const Player& player);
};

#endif // PICKABLE_HPP
