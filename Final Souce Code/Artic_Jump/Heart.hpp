#ifndef HEART_HPP
#define HEART_HPP

#include <SFML/Graphics.hpp>
#include "Pickable.hpp"
#include "Player.hpp"

class Heart : public Pickable
{
public:
    Heart(const std::string& texturePath);
    bool checkCollision(Player& player);
    void update(const sf::RenderWindow& window);
};

#endif // HEART_HPP
