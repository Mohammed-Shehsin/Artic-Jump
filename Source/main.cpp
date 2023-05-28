#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


int main()
{  
    // Window
   sf::RenderWindow window(sf::VideoMode(1000, 1000), "Platformer Game");

   // Load textures
   std::string playerTexturePath = "player_texture.png";
   std::string heartTexturePath = "heart_texture.jpg";
   std::string goldTexturePath = "gold_texture.jpeg";
   std::string platformTexturePath = "platform_texture.jpeg";
   std::string fireballTexturePath = "fireball_texture.jpeg";

   // Create objects
   //Player
   std::unique_ptr<Player> player = std::make_unique<Player>(playerTexturePath);
   player->setPosition(100.0f, 400.0f);
   // 6 Platforms
   std::vector<std::unique_ptr<Immovable>> platforms;
   for (int i = 0; i < 6; i++) {
       std::unique_ptr<Immovable> platform = std::make_unique<Immovable>(platformTexturePath);
       platform->setPosition((i + 1) * 100.0f, 500.0f);
       platform->setScale(2.0f, 1.0f);
       platforms.push_back(std::move(platform));
   }
   // Fireballs
   std::vector<std::unique_ptr<Fireball>> fireballs;
   for (int i = 0; i < 3; i++) {
       std::unique_ptr<Fireball> fireball = std::make_unique<Fireball>(fireballTexturePath);
       fireball->setPosition(0.0f, 200.0f * i);
       fireballs.push_back(std::move(fireball));
   }
    // Heart
   std::vector<std::unique_ptr<Heart>> hearts;
   for (int i = 0; i < 3; i++) {
       std::unique_ptr<Heart> heart = std::make_unique<Heart>(heartTexturePath);
       heart->setPosition(200.0f * (i + 1), 600.0f);
       hearts.push_back(std::move(heart));
   }
  //gold
   std::unique_ptr<Gold> gold = std::make_unique<Gold>(goldTexturePath);
   gold->setPosition(500.0f, 600.0f);

   // Create a vector of Sprites
   std::vector<Sprites*> objects;
   objects.push_back(player.get());
   for (const auto& platform : platforms) {
       objects.push_back(platform.get());
   }
   for (const auto& fireball : fireballs) {
       objects.push_back(fireball.get());
   }
   for (const auto& heart : hearts) {
       objects.push_back(heart.get());
   }
   objects.push_back(gold.get());

   int score = 0;

   while (window.isOpen())
   {
       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();
       }

       // Update player movement and collision
       player->update();

       // Check collision with platforms
       for (const auto& platform : platforms) {
           if (player->collision(*platform)) {
               // Handle platform collision
           }
       }

       // Check collision with fireballs
       for (const auto& fireball : fireballs) {
           if (fireball->checkCollision(*player)) {
               // Handle fireball collision
           }
       }

       // Check collision with hearts
       for (const auto& heart : hearts) {
           if (heart->checkCollision(*player)) {
               // Handle heart collision
               hearts.erase(std::remove_if(hearts.begin(), hearts.end(), [&](const std::unique_ptr<Heart>& h) {
                                return h.get() == heart.get();
                            }), hearts.end());

               score++;
           }
       }

       // Check collision with gold
       if (gold->checkCollision(*player)) {
           // Handle gold collision
           score += 5;
       }

       window.clear();

       // Draw all the objects
       for (const auto& object : objects) {
           window.draw(*object);
       }

       window.display();
   }

   return 0;
}
