#include "Immovable.hpp"

Immovable::Immovable(const std::string& texturePath) : Sprites()
{
    setTexture(texturePath);
}

void Immovable::setPosition(float x, float y)
{
    sf::Sprite::setPosition(x, y);
}

void Immovable::setScale(float scaleX, float scaleY)
{
    sf::Sprite::setScale(scaleX, scaleY);
}
