#ifndef SPRITES_HPP
#define SPRITES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Sprites : public sf::Sprite
{
public:
    Sprites();
    virtual ~Sprites();
    void setTexture(const std::string& texturePath);

protected:
    void adjustPositionWithinBounds(const sf::FloatRect& bounds);

private:
    sf::Texture texture;
};

#endif // SPRITES_HPP
