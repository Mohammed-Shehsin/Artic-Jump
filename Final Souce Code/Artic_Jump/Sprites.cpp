#include "Sprites.hpp"

Sprites::Sprites()
{
}

Sprites::~Sprites()
{
}

void Sprites::setTexture(const std::string& texturePath)
{
    if (!texture.loadFromFile(texturePath))
    {
        std::cerr << "Could not load texture" << std::endl;
    }

    // Set the texture for the sprite
    sf::Sprite::setTexture(texture);
}

void Sprites::adjustPositionWithinBounds(const sf::FloatRect& bounds)
{
    sf::Vector2f newPosition;

    if (getGlobalBounds().left < bounds.left)
        newPosition.x = bounds.left;
    else if (getGlobalBounds().left + getGlobalBounds().width > bounds.left + bounds.width)
        newPosition.x = bounds.left + bounds.width - getGlobalBounds().width;
    else
        newPosition.x = getPosition().x;

    if (getGlobalBounds().top < bounds.top)
        newPosition.y = bounds.top;
    else if (getGlobalBounds().top + getGlobalBounds().height > bounds.top + bounds.height)
        newPosition.y = bounds.top + bounds.height - getGlobalBounds().height;
    else
        newPosition.y = getPosition().y;

    setPosition(newPosition);
}
