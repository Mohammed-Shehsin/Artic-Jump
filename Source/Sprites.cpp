#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<string>
#include <random>
#include <utility>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

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

  void update(const std::vector<std::unique_ptr<Immovable>>& platforms,const sf::RenderWindow& window,int &life)
    {
        moveInDirection();
        collision(platforms);
        life=getLives();

        // Check collision with the window boundaries
        sf::FloatRect playerBounds = getGlobalBounds();
        sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

        if (!windowBounds.contains(playerBounds.left, playerBounds.top)
            || !windowBounds.contains(playerBounds.left + playerBounds.width, playerBounds.top)
            || !windowBounds.contains(playerBounds.left, playerBounds.top + playerBounds.height)
            || !windowBounds.contains(playerBounds.left + playerBounds.width, playerBounds.top + playerBounds.height))
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
            float gravity=2.50f;
            sf::Vector2f gravityMove(0.0f,speed * gravity);
            this->move(gravityMove);

        }

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
        std::uniform_real_distribution<float> distribution(0.0f, 0.8f);

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
        std::uniform_real_distribution<float> speedDistribution(0.1f, 2.0f); // Adjust the range of speed as needed

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
     // update function to stay the heart inside the window
     void update(const sf::RenderWindow& window){
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
     void update(const sf::RenderWindow& window){
        // Check collision with the window boundaries
        sf::FloatRect goldBounds = getGlobalBounds();
        sf::FloatRect windowBounds(0.0f, 0.0f, window.getSize().x, window.getSize().y);

        if (!windowBounds.contains(goldBounds.left, goldBounds.top)
            || !windowBounds.contains(goldBounds.left + goldBounds.width, goldBounds.top)
            || !windowBounds.contains(goldBounds.left,goldBounds.top + goldBounds.height)
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
            else if (goldBounds.top +goldBounds.height > windowBounds.height)
                newPosition.y = windowBounds.height - goldBounds.height;
            else
                newPosition.y = getPosition().y;

            setPosition(newPosition);
        }


};
class Button : public Sprites
{
public:
    Button(const std::string& buttonText, const sf::Font& font, unsigned int characterSize, const sf::Vector2f& position)
    {
        text.setString(buttonText);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setPosition(position);
        text.setFillColor(sf::Color::White);

        // Create a background rectangle for the button
        background.setSize(sf::Vector2f(text.getLocalBounds().width + 20, text.getLocalBounds().height + 10));
        background.setPosition(position);
        background.setFillColor(sf::Color(50, 50, 50));

        // Center the text within the button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2, textBounds.top + textBounds.height / 2);
        text.setPosition(position.x + background.getSize().x / 2, position.y + background.getSize().y / 2);
    }

    bool isMouseOver(const sf::RenderWindow& window) const
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        return background.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }






private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(background, states);
        target.draw(text, states);
    }

    sf::RectangleShape background;
    sf::Text text;
};
