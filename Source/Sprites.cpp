#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<string>
#include <random>
#include <utility>


//Parent Class Sprite

class Sprites : public sf::Sprite
{
public:
    Sprites() {}
    
    void setTexture(const std::string& texturePath)
    {
        if (!texture.loadFromFile(texturePath))
        {
            std::cerr << "Could not load texture" << std::endl;

        }
        
        // Set the texture for the sprite
        this->sf::Sprite::setTexture(texture);
    }
    
private:
    sf::Texture texture;
};


//InMovable -For Platform

class Immovable : public Sprites
{
public:
    Immovable(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
    }

    void setPosition(float x, float y)
    {
        sf::Sprite::setPosition(x, y);
    }

    void setScale(float scaleX, float scaleY)
    {
        sf::Sprite::setScale(scaleX, scaleY);
    }
};

//Player class

class Player : public Sprites
{
public:
    Player(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
        speed = 0.80f;
        jumpHeight = 10.0f;
        isJumping = false;
        jumpKeyPressed = false;
        lives = 3;
        bonusPoints = 0;
        isIntersect=false;
    }

    void moveInDirection()
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            directiony -= 5.0f;
            isJumping=true;
        }
        sf::Vector2f movement(speed * directionx, 0.0f);
        sf::Vector2f jumpMove(0.0f,speed * directiony);
        this->move(movement);
        this->move(jumpMove);
        isJumping=false;
    }

//    void collision(const sf::Sprite& others)
//    {
// for (const auto& other : others) {
    void collision(const std::vector<std::unique_ptr<Immovable>>& platforms) {
        for (const auto& platform : platforms) {
            sf::FloatRect playerBounds = getGlobalBounds();
            sf::FloatRect platformBounds = platform->getGlobalBounds();

            if (playerBounds.intersects(platformBounds)) {
                // Calculate the overlap between the player and platform
                float overlapX = std::min(playerBounds.left + playerBounds.width, platformBounds.left + platformBounds.width) -
                                 std::max(playerBounds.left, platformBounds.left);
                float overlapY = std::min(playerBounds.top + playerBounds.height, platformBounds.top + platformBounds.height) -
                                 std::max(playerBounds.top, platformBounds.top);

                // Determine the axis of minimum penetration
                if (overlapX < overlapY) {
                    // Adjust player position horizontally
                    if (playerBounds.left < platformBounds.left) {
                        setPosition(platformBounds.left - playerBounds.width, getPosition().y);
                    } else {
                        setPosition(platformBounds.left + platformBounds.width, getPosition().y);
                    }
                } else {
                    // Adjust player position vertically
                    if (playerBounds.top < platformBounds.top) {
                        setPosition(getPosition().x, platformBounds.top - playerBounds.height);
                    } else {
                        setPosition(getPosition().x, platformBounds.top + platformBounds.height);
                    }
                }
            }
        }
    }


//    void jump()
//    {
//        if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            isJumping = true;
//            jumpDistance = jumpHeight;
//        }
//    }

    void update(const std::vector<std::unique_ptr<Immovable>>& platforms)
    {
        moveInDirection();
        collision(platforms);

        if (!isJumping)
        {
         float gravity=2.50f;
            sf::Vector2f gravityMove(0.0f,speed * gravity);
            this->move(gravityMove);

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

private:
    float speed;
    float jumpHeight;
    bool isJumping;
    float jumpDistance;
    bool jumpKeyPressed;
    bool isIntersect;
    int lives;
    int bonusPoints;
};



//Fireball class

//Fireball class

class Fireball : public Sprites
{
public:
    Fireball(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
        speed = getRandomSpeed();
    }

    void moveInDirection()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distribution(0.0f, 2.0f);

        float randomValue = distribution(gen);
        sf::Vector2f movement(randomValue+speed,0.0f );
        this->move(movement);
    }

    bool checkCollision(const Player& player)
    {
        return this->getGlobalBounds().intersects(player.getGlobalBounds());
    }



private:
    float speed;

    float getRandomSpeed()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> speedDistribution(0.1f, 2.5f); // Adjust the range of speed as needed

        return speedDistribution(gen);
    }
};
//Pickable

class Pickable : public Sprites
{
public:
    Pickable(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
    }

    bool checkCollision(const Player& player)
    {
        return this->getGlobalBounds().intersects(player.getGlobalBounds());
    }
};

//Heart - Pickable

class Heart : public Pickable
{
public:
    Heart(const std::string& texturePath) : Pickable(texturePath) {}

    bool checkCollision(Player& player)
    {
        if (player.getLives() < 3)
        {
            if (this->getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                player.incrementLives();
                return true;
            }
        }
        return false;
    }
};

//Gold - Pickable

class Gold : public Pickable
{
public:
    Gold(const std::string& texturePath) : Pickable(texturePath) {}

    bool checkCollision(Player& player)
    {
        if (this->getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            player.incrementBonusPoints(5);
            return true;
        }
        return false;
    }
};
