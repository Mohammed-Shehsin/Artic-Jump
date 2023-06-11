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
    void collision(const std::vector<std::unique_ptr<Immovable>>& platforms);
    void update(const std::vector<std::unique_ptr<Immovable>>& platforms,const sf::RenderWindow& window);
};

#endif // HEART_HPP
