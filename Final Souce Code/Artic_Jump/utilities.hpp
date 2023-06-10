#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <memory>
#include "Fireball.hpp"
#include "Gold.hpp"
#include "Heart.hpp"

std::pair<float, float> getRandomPosition(const sf::RenderWindow& window);
void createFireballs(std::string fireballTexturePath, std::vector<std::unique_ptr<Fireball>>& fireballs);
void resetFireballs(std::vector<std::unique_ptr<Fireball>>& fireballs);
void createGold(std::unique_ptr<Gold>& gold, const sf::RenderWindow& window);
void createHeart(std::unique_ptr<Heart>& heart, const sf::RenderWindow& window);

#endif // UTILITIES_HPP
