#include "Pickable.hpp"

Pickable::Pickable(const std::string& texturePath) : Sprites()
{
    setTexture(texturePath);
}

bool Pickable::checkCollision(const Player& player)
{
    return this->getGlobalBounds().intersects(player.getGlobalBounds());
}
