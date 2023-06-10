#include "utilities.hpp"

std::pair<float, float> getRandomPosition(const sf::RenderWindow& window)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> distX(-800.0f, 1200.0f);
    static std::uniform_real_distribution<float> distY(-800.0f, 800.0f);

    float x = distX(gen);
    float y = distY(gen);

    // Check if the generated position falls within the restricted range
    while ((x >= -250.0f && x <= 250.0f) ||
           (x >= -800.0f && x <= 150.0f) ||
           (x >= -650.0f && x <= -300.0f) ||
           (x >= 10.0f && x <= -150.0f) ||
           (x >= 300.0f && x <= 150.0f) ||
           (y >= -250.0f && y <= 250.0f) ||
           (y >= -800.0f && y <= 150.0f) ||
           (y >= -650.0f && y <= -300.0f) ||
           (y >= 10.0f && y <= -150.0f) ||
           (y >= 300.0f && y <= 150.0f) ||
           (x < 0.0f || x > window.getSize().x) ||
           (y < 0.0f || y > window.getSize().y))
    {
        x = distX(gen);
        y = distY(gen);
    }

    return std::make_pair(x, y);
}


void createFireballs(std::string fireballTexturePath, std::vector<std::unique_ptr<Fireball>>& fireballs)
{
    std::unique_ptr<Fireball> fireball1 = std::make_unique<Fireball>(fireballTexturePath);
    fireball1->setPosition(0.0f, 420.0f);
    fireball1->setScale(0.50f, 0.50f);
    fireballs.push_back(std::move(fireball1));

    std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
    fireball2->setPosition(0.0f, 780.0f);
    fireball2->setScale(0.50f, 0.50f);
    fireballs.push_back(std::move(fireball2));

    std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
    fireball3->setPosition(0.0f, 10.0f);
    fireball3->setScale(0.50f, 0.50f);
    fireballs.push_back(std::move(fireball3));
}

void resetFireballs(std::vector<std::unique_ptr<Fireball>>& fireballs)
{
    // Reset fireballs to their initial positions
    fireballs[0]->setPosition(0.0f, 450.0f);
    fireballs[1]->setPosition(0.0f, 700.0f);
    fireballs[2]->setPosition(0.0f, 0.0f);
}

void createGold(std::unique_ptr<Gold>& gold, const sf::RenderWindow& window)
{
    std::pair<float, float> position = getRandomPosition(window);
    gold->setPosition(position.first, position.second);
    gold->setScale(0.30f, 0.30f);
}

void createHeart(std::unique_ptr<Heart>& heart, const sf::RenderWindow& window)
{
    std::pair<float, float> position = getRandomPosition(window);
    heart->setPosition(position.first, position.second);
    heart->setScale(0.10f, 0.10f);
}
