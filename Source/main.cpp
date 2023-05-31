
#include <iostream>
class Player : public Sprites
{
public:
    Player(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
        speed = 0.50f;
        jumpHeight = 10.0f;
        isJumping = false;
        jumpKeyPressed = false;
        lives = 3;
        bonusPoints = 0;
        gravity=4.5f;
        isOnPlatform=0;
        velocityY=0f;
    }

    void moveInDirection()
    {
        float direction = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction += 1.0f;
        }
        sf::Vector2f movement(speed * direction, 0.0f);
        this->move(movement);
    }

    bool collision(const sf::Sprite& other)
    {
        return this->getGlobalBounds().intersects(other.getGlobalBounds());
    }

    void jump()
    {
        if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isJumping = true;
            jumpDistance = jumpHeight;
        }
    }
    bool isOnPlatform(const Player& player, const std::vector<Platform>& platforms)
    {
        // Iterate through all the platforms
        for (const Platform& platform : platforms)
        {
            // Check if the player's bounding box intersects with the platform's bounding box
            if (player.getGlobalBounds().intersects(platform.getGlobalBounds()))
            {
                // Player is on a platform
                return true;
            }
        }

        // Player is not on any platform
        return false;
    }
    void update()
    {
        moveInDirection();
        if (isJumping)
        {
            float yMovement = -0.5f * jumpDistance;
            sf::Vector2f movement(0.0f, yMovement);
            this->move(movement);
            jumpDistance -= 1.0f;

            if (jumpDistance <= 0.0f)
            {
                isJumping = false;
            }
        }
        else if( !isOnPlatform())
            {
                // Updated update() to apply gravity and update vertical velocity
                velocityY += gravity;
                sf::Vector2f movement(0.0f, velocityY);
                this->move(movement);
            }
            }

    void incrementBonusPoints(int points)
    {
        bonusPoints += points;
    }

    void incrementLives()
    {
        if (lives < 3)
        {
            lives++;
        }
    }

    int getLives() const
    {
        return lives;
    }

    int getBonusPoints() const
    {
        return bonusPoints;
    }
    void applygravity()
    {
        sf::Vector2f movement(0.0f, gravity);
        this->move(movement);
    }
private:
    float speed;
    float jumpHeight;
    bool isJumping;
    float jumpDistance;
    bool jumpKeyPressed;
    int lives;
    int bonusPoints;
    float gravity;
    bool isOnPlatform;
    float velocityy;
};
