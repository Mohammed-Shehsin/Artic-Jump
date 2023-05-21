

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
