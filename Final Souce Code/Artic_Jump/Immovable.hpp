#ifndef IMMOVABLE_HPP
#define IMMOVABLE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprites.hpp"

class Immovable : public Sprites
{
public:
    Immovable(const std::string& texturePath);
    void setPosition(float x, float y);
    void setScale(float scaleX, float scaleY);
};

#endif // IMMOVABLE_HPP
