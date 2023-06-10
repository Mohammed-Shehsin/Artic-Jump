#include "Heart.hpp"

Heart::Heart(const std::string& texturePath) : Pickable(texturePath) {}

bool Heart::checkCollision(Player& player)
{
    //        if (player.getLives() < 3)
    //        {
    if (this->getGlobalBounds().intersects(player.getGlobalBounds()))
    {
        player.incrementLives(1);
        return true;
    }
    //        }
    return false;
}

void Heart::update(const sf::RenderWindow& window)
{
    // Check collision with the window boundaries
    sf::FloatRect heartBounds = getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

    if (!windowBounds.contains(heartBounds.left, heartBounds.top)
        || !windowBounds.contains(heartBounds.left + heartBounds.width, heartBounds.top)
        || !windowBounds.contains(heartBounds.left,heartBounds.top + heartBounds.height)
        || !windowBounds.contains(heartBounds.left + heartBounds.width, heartBounds.top + heartBounds.height))
    {
        // Adjust player position to stay within the window
        sf::Vector2f newPosition;

        if (heartBounds.left < 0.0f)
            newPosition.x = 0.0f;
        else if (heartBounds.left + heartBounds.width > windowBounds.width)
            newPosition.x = windowBounds.width - heartBounds.width;
        else
            newPosition.x = getPosition().x;

        if (heartBounds.top < 0.0f)
            newPosition.y = 0.0f;
        else if (heartBounds.top + heartBounds.height > windowBounds.height)
            newPosition.y = windowBounds.height - heartBounds.height;
        else
            newPosition.y = getPosition().y;

        setPosition(newPosition);
    }
}
