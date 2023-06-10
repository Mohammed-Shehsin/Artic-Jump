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

void Gold::update(const sf::RenderWindow& window)
{
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
