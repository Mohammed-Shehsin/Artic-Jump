
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
    Sprite(Texture& texture)

    {

    void set_Texture()
    {
        sf::sprite.setTexture(texture);


    }
    void set_Scale()
    {
        sf::sprite.setScale(scalex,scaley);
    }
    void set_Position()
    {
        sf::sprite.setPosition(x, y);
    }
    }
};
class Player: public Sprite{
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
    Player(Sprite spite,Texture texture):Sprites(sprite,texture,scalex,scaley,x,y),speedx(speedx),speedy(speedy)

        void movePlayer()
    {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        character->move(-1*speedx, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        character->move(speedx, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        character->move(0, -1*speedy);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        character->move(0, speedy);
    }
    }





};


