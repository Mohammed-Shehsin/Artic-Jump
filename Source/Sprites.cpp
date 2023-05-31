#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<string>

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


//Player class

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

    bool collision(const sf::Sprite& other)
    {
        return this->getGlobalBounds().intersects(other.getGlobalBounds());
    }

//    void jump()
//    {
//        if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//        {
//            isJumping = true;
//            jumpDistance = jumpHeight;
//        }
//    }

    void update()
    {
        moveInDirection();

        if (!isJumping)
        {
            float gravity=1.0f;
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
    int lives;
    int bonusPoints;
};



//Fireball class

class Fireball : public Sprites
{
public:
    Fireball(const std::string& texturePath) : Sprites()
    {
        setTexture(texturePath);
        speed = 5.0f;
    }
    
    void moveInDirection()
    {
        sf::Vector2f movement(speed, 0.0f);
        this->move(movement);
    }
    
    bool checkCollision(const Player& player)
    {
        return this->getGlobalBounds().intersects(player.getGlobalBounds());
    }
    
private:
    float speed;
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

