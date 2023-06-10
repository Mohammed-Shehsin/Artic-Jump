#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <random>
#include <utility>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

#include "Sprites.hpp"
#include "Immovable.hpp"

class Player : public Sprites
{
public:
    Player(const std::string& texturePath);
    void resetScore();
    void moveInDirection();
    void collision(const std::vector<std::unique_ptr<Immovable>>& platforms);
    void incrementBonusPoints(int points);
    void incrementLives(const int x);
    void decreamentLive(const int x);
    int getLives() const;
    int getBonusPoints() const;
    void resetLives();
    void update(const std::vector<std::unique_ptr<Immovable>>& platforms, const sf::RenderWindow& window, int& life);

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

#endif // PLAYER_HPP
