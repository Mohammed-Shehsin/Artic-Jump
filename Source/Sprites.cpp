

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include<iostream>
#include<string>

class Sprites{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    double scalex;
    double scaley;
    double x;
    double y;
public:
    Sprite(sf::Texture& texture)
    {

        sprite.setTexture(texture);
        sprite.setScale(scalex,scaley);
        sprite.setPosition(x, y);

    }
};


// //Parent Class Sprite

// class Sprites : public sf::Sprite
// {
// public:
//     Sprites() {}
    
//     void setTexture(const std::string& texturePath)
//     {
//         if (!texture.loadFromFile(texturePath))
//         {
//             std::cerr << "Could not load texture" << std::endl;
//             return 1;
//         }
        
//         // Set the texture for the sprite
//         this->sf::Sprite::setTexture(texture);
//     }
    
// protected:
//     sf::Texture texture;
// };




class Player: public Sprites{
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    double scalex;
    double scaley;
    double x;
    double y;
    double speedx;
    double speedy;


public:
    Player(sf::Sprite spite,sf::Texture texture):Sprites(sprite,texture,scalex,scaley,x,y),speedx(speedx),speedy(speedy){}

    void movePlayer()
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            sprite.move(-1*speedx, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            sprite.move(speedx, 0);
        }
    }

    void jump()
    {if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            sprite.move(0,speedy);
        }
    }

};

// //Player class

// class Player : public Sprites
// {
// public:
//     Player(const std::string& texturePath) : Sprites()
//     {
//         setTexture(texturePath);
//         speed = 5.0f;
//         jumpHeight = 10.0f;
//         isJumping = false;
//         jumpKeyPressed = false;
//     }
    
//     void moveInDirection()
//     {
//         float direction = 0.0f;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//         {
//             direction -= 1.0f;
//         }
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//         {
//             direction += 1.0f;
//         }
//         sf::Vector2f movement(speed * direction, 0.0f);
//         this->move(movement);
//     }
    
//     bool collision(const sf::Sprite& other)
//     {
//         return this->getGlobalBounds().intersects(other.getGlobalBounds());
//     }
    
//     void jump()
//     {
//         if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
//         {
//             isJumping = true;
//             jumpDistance = jumpHeight;
//         }
//     }
    
//     void update()
//     {
//         moveInDirection();
        
//         if (isJumping)
//         {
//             float yMovement = -0.5f * jumpDistance;
//             sf::Vector2f movement(0.0f, yMovement);
//             this->move(movement);
//             jumpDistance -= 1.0f;
            
//             if (jumpDistance <= 0.0f)
//             {
//                 isJumping = false;
//             }
//         }
//     }
    
// protected:
//     float speed;
//     float jumpHeight;
//     bool isJumping;
//     float jumpDistance;
//     bool jumpKeyPressed;
// };







