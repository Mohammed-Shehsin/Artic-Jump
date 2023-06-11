#include "Gold.hpp"

Gold::Gold(const std::string& texturePath) : Pickable(texturePath) {}

bool Gold::checkCollision(Player& player)
{
    if (this->getGlobalBounds().intersects(player.getGlobalBounds()))
    {
        player.incrementBonusPoints(5);
        return true;
    }
    return false;
}

void Gold::collision(const std::vector<std::unique_ptr<Immovable>>& platforms)       //check collision with Platforms and Gold objects for avoiding the platforms
{
    for (const auto& platform : platforms)
    {
        sf::FloatRect goldBounds = getGlobalBounds();
        sf::FloatRect platformBounds = platform->getGlobalBounds();

        if (goldBounds.intersects(platformBounds))
        {
            // Calculate the overlap between the player and platform
            float overlapX = std::min(goldBounds.left + goldBounds.width, platformBounds.left + platformBounds.width) -
                             std::max(goldBounds.left, goldBounds.left);
            float overlapY = std::min(goldBounds.top + goldBounds.height, platformBounds.top + platformBounds.height) -
                             std::max(goldBounds.top, goldBounds.top);

            // Determine the axis of minimum penetration
            if (overlapX < overlapY)
            {
                // Adjust player position horizontally
                if (goldBounds.left < platformBounds.left)
                {
                    setPosition(platformBounds.left - goldBounds.width, getPosition().y);
                }
                else
                {
                    setPosition(platformBounds.left + platformBounds.width, getPosition().y);
                }
            }
            else
            {
                // Adjust player position vertically
                if (goldBounds.top < platformBounds.top)
                {
                    setPosition(getPosition().x, platformBounds.top - goldBounds.height);
                }
                else
                {
                    setPosition(getPosition().x, platformBounds.top + platformBounds.height);
                }
            }
        }
    }
}

void Gold::update(const std::vector<std::unique_ptr<Immovable> > &platforms, const sf::RenderWindow& window)              // Make the gold object always inside the window
{
    collision(platforms);
    // Check collision with the window boundaries
    sf::FloatRect goldBounds = getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

    if (!windowBounds.contains(goldBounds.left, goldBounds.top)
        || !windowBounds.contains(goldBounds.left + goldBounds.width, goldBounds.top)
        || !windowBounds.contains(goldBounds.left, goldBounds.top + goldBounds.height)
        || !windowBounds.contains(goldBounds.left + goldBounds.width, goldBounds.top + goldBounds.height))
    {
        // Adjust player position to stay within the window
        sf::Vector2f newPosition;

        if (goldBounds.left < 0.0f)
            newPosition.x = 0.0f;
        else if (goldBounds.left + goldBounds.width > windowBounds.width)
            newPosition.x = windowBounds.width - goldBounds.width;
        else
            newPosition.x = getPosition().x;

        if (goldBounds.top < 0.0f)
            newPosition.y = 0.0f;
        else if (goldBounds.top + goldBounds.height > windowBounds.height)
            newPosition.y = windowBounds.height - goldBounds.height;
        else
            newPosition.y = getPosition().y;

        setPosition(newPosition);
    }
}
