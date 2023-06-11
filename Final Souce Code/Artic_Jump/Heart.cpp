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
void Heart::collision(const std::vector<std::unique_ptr<Immovable>>& platforms) //check collision with Platforms and Heart objects for avoiding the platforms
{
    for (const auto& platform : platforms)
    {
        sf::FloatRect heartBounds = getGlobalBounds();
        sf::FloatRect platformBounds = platform->getGlobalBounds();

        if (heartBounds.intersects(platformBounds))
        {
            // Calculate the overlap between the player and platform
            float overlapX = std::min(heartBounds.left + heartBounds.width, platformBounds.left + platformBounds.width) -
                             std::max(heartBounds.left, heartBounds.left);
            float overlapY = std::min(heartBounds.top + heartBounds.height, platformBounds.top + platformBounds.height) -
                             std::max(heartBounds.top, heartBounds.top);

            // Determine the axis of minimum penetration
            if (overlapX < overlapY)
            {
                // Adjust player position horizontally
                if (heartBounds.left < platformBounds.left)
                {
                    setPosition(platformBounds.left - heartBounds.width, getPosition().y);
                }
                else
                {
                    setPosition(platformBounds.left + platformBounds.width, getPosition().y);
                }
            }
            else
            {
                // Adjust player position vertically
                if (heartBounds.top < platformBounds.top)
                {
                    setPosition(getPosition().x, platformBounds.top - heartBounds.height);
                }
                else
                {
                    setPosition(getPosition().x, platformBounds.top + platformBounds.height);
                }
            }
        }
    }
}
void Heart::update(const std::vector<std::unique_ptr<Immovable>>& platforms, const sf::RenderWindow& window)        // Keep heart objects inside the window
{
    collision(platforms);                           //implementing collision with platform
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
