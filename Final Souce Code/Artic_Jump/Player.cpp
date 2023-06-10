#include "Player.hpp"

Player::Player(const std::string& texturePath) : Sprites()
{
    setTexture(texturePath);
    speed = 0.80f;
    jumpHeight = 10.0f;
    isJumping = false;
    jumpKeyPressed = false;
    lives = 5;
    bonusPoints = 0;
    isIntersect = false;
}

void Player::resetScore()
{
    bonusPoints = 0;
}

void Player::moveInDirection()
{
    float directionx = 0.0f;
    float directiony = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        directionx -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        directionx += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        directiony -= 5.0f;
        isJumping = true;
    }
    sf::Vector2f movement(speed * directionx, 0.0f);
    sf::Vector2f jumpMove(0.0f, speed * directiony);
    this->move(movement);
    this->move(jumpMove);
    isJumping = false;
}

void Player::collision(const std::vector<std::unique_ptr<Immovable>>& platforms)
{
    for (const auto& platform : platforms)
    {
        sf::FloatRect playerBounds = getGlobalBounds();
        sf::FloatRect platformBounds = platform->getGlobalBounds();

        if (playerBounds.intersects(platformBounds))
        {
            // Calculate the overlap between the player and platform
            float overlapX = std::min(playerBounds.left + playerBounds.width, platformBounds.left + platformBounds.width) -
                             std::max(playerBounds.left, platformBounds.left);
            float overlapY = std::min(playerBounds.top + playerBounds.height, platformBounds.top + platformBounds.height) -
                             std::max(playerBounds.top, platformBounds.top);

            // Determine the axis of minimum penetration
            if (overlapX < overlapY)
            {
                // Adjust player position horizontally
                if (playerBounds.left < platformBounds.left)
                {
                    setPosition(platformBounds.left - playerBounds.width, getPosition().y);
                }
                else
                {
                    setPosition(platformBounds.left + platformBounds.width, getPosition().y);
                }
            }
            else
            {
                // Adjust player position vertically
                if (playerBounds.top < platformBounds.top)
                {
                    setPosition(getPosition().x, platformBounds.top - playerBounds.height);
                }
                else
                {
                    setPosition(getPosition().x, platformBounds.top + platformBounds.height);
                }
            }
        }
    }
}

void Player::incrementBonusPoints(int points)
{
    bonusPoints += points;
}

void Player::incrementLives(const int x)
{
    if (lives < 5)
    {
        lives = lives + x;
    }
}

void Player::decreamentLive(const int x)
{
    if (lives > 0)
    {
        lives = lives - x;
    }
}

int Player::getLives() const
{
    return lives;
}

int Player::getBonusPoints() const
{
    return bonusPoints;
}

void Player::resetLives()
{
    lives = 5;
}

void Player::update(const std::vector<std::unique_ptr<Immovable>>& platforms, const sf::RenderWindow& window, int& life)
{
    moveInDirection();
    collision(platforms);
    life = getLives();
    // Check collision with the window boundaries
    sf::FloatRect playerBounds = getGlobalBounds();
    sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

    if (!windowBounds.contains(playerBounds.left, playerBounds.top) ||
        !windowBounds.contains(playerBounds.left + playerBounds.width, playerBounds.top) ||
        !windowBounds.contains(playerBounds.left, playerBounds.top + playerBounds.height) ||
        !windowBounds.contains(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height))
    {
        // Adjust player position to stay within the window
        sf::Vector2f newPosition;

        if (playerBounds.left < 0.0f)
            newPosition.x = 0.0f;
        else if (playerBounds.left + playerBounds.width > windowBounds.width)
            newPosition.x = windowBounds.width - playerBounds.width;
        else
            newPosition.x = getPosition().x;

        if (playerBounds.top < 0.0f)
            newPosition.y = 0.0f;
        else if (playerBounds.top + playerBounds.height > windowBounds.height)
            newPosition.y = windowBounds.height - playerBounds.height;
        else
            newPosition.y = getPosition().y;

        setPosition(newPosition);
    }

    if (!isJumping)
    {
        float gravity = 2.50f;
        sf::Vector2f gravityMove(0.0f, speed * gravity);
        this->move(gravityMove);
    }
}
