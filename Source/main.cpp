int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Platformer Game");

    // Load textures
    std::string playerTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\player_texture.png";
    std::string heartTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\heart_texture.png";
    std::string goldTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\gold_texture.png";
    std::string platformTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\platform_texture.png";
    std::string fireballTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\fireball_texture.png";
    std::string backGroundTexurePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\actic.png";

    // Create objects
    std::unique_ptr<Player> player = std::make_unique<Player>(playerTexturePath);
    player->setPosition(500.0f, 350.0f);
    player->setScale(0.15f,0.15f);

//std:unique_ptr<Immovable> background = std::make_unique<Immovable>(backGroundTexurePath);

    std::vector<std::unique_ptr<Immovable>> platforms;
//    for (int i = 0; i < 6; i++) {
        std::unique_ptr<Immovable> platform1 = std::make_unique<Immovable>(platformTexturePath);
        platform1->setPosition( 500.0f, 500.0f);
        platform1->setScale(1.0f, 1.0f);
        platforms.push_back(std::move(platform1));
        std::unique_ptr<Immovable> platform2 = std::make_unique<Immovable>(platformTexturePath);
        platform2->setPosition( 100.0f, 100.0f);
        platform2->setScale(1.0f, 1.0f);
        platforms.push_back(std::move(platform2));
        std::unique_ptr<Immovable> platform3 = std::make_unique<Immovable>(platformTexturePath);
        platform3->setPosition( 500.0f, 100.0f);
        platform3->setScale(1.0f, 1.0f);
        platforms.push_back(std::move(platform3));
        std::unique_ptr<Immovable> platform4 = std::make_unique<Immovable>(platformTexturePath);
        platform4->setPosition( 100.0f, 500.0f);
        platform4->setScale(1.0f, 1.0f);
        platforms.push_back(std::move(platform4));
        std::unique_ptr<Immovable> platform5 = std::make_unique<Immovable>(platformTexturePath);
        platform5->setPosition( 0.0f, 850.0f);
        platform5->setScale(5.0f, 1.0f);
        platforms.push_back(std::move(platform5));
//    }

//    std::vector<std::unique_ptr<Fireball>> fireballs;
//    //for (int i = 0; i < 3; i++) {
//        std::unique_ptr<Fireball> fireball1 = std::make_unique<Fireball>(fireballTexturePath);
//        fireball1->setPosition(0.0f, 200.0f );
//        fireball1->setScale(0.80f,0.80f);
//        fireballs.push_back(std::move(fireball1));
//        std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
//        fireball2->setPosition(0.0f, 400.0f );
//        fireball2->setScale(0.80f,0.80f);
//        fireballs.push_back(std::move(fireball2));
//        std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
//        fireball3->setPosition(0.0f, 600.0f );
//        fireball3->setScale(0.80f,0.80f);
//        fireballs.push_back(std::move(fireball3));
   // }

//    std::vector<std::unique_ptr<Heart>> hearts;
//    for (int i = 0; i < 3; i++) {
//        std::unique_ptr<Heart> heart = std::make_unique<Heart>(heartTexturePath);
//        heart->setPosition(200.0f * (i + 1), 600.0f);
//        hearts.push_back(std::move(heart));
//    }

    std::unique_ptr<Gold> gold = std::make_unique<Gold>(goldTexturePath);
    gold->setPosition(500.0f, 600.0f);

    // Create a vector of Sprites
    std::vector<Sprites*> objects;
    objects.push_back(player.get());
 //   objects.push_back((background.get()));
    for (const auto& platform : platforms) {
        objects.push_back(platform.get());
    }
//    for (const auto& fireball : fireballs) {
//        objects.push_back(fireball.get());
//    }
//    for (const auto& heart : hearts) {
//        objects.push_back(heart.get());
//    }
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
        //for (const auto& platform : platforms) {
          //  if (player->collision(*platform)) {
//                sf::FloatRect playerborders = player->getGlobalBounds();
//                sf::FloatRect platformborders = platform->getGlobalBounds();
//               // if(player->getGlobalBounds().intersects(platformborders)){
//                    if(playerborders.top > platformborders.top + platformborders.height && playerborders.left + playerborders.width > platformborders.left
//                        && playerborders.left < platformborders.left + platformborders.width){
//                        player->setPosition(player->getPosition().x, platformborders.top + platformborders.height);
//                        break;
//                    }
//                    else if(playerborders.top < platformborders.top - playerborders.height && playerborders.left > platformborders.left - playerborders.width
//                             && playerborders.left < platformborders.left +platformborders.width){
//                        player->setPosition(player->getPosition().x,platformborders.top - playerborders.height);
//                        break;
//                    }
//                    else if(playerborders.left < platformborders.left - playerborders.width && playerborders.top > platformborders.top - platformborders.height
//                             && playerborders.top < platformborders.top + platformborders.height){
//                        player->setPosition(platformborders.left -playerborders.width, player->getPosition().y);
//                        break;
//                    }
//                    else if(playerborders.left > platformborders.left + platformborders.width && playerborders.top > platformborders.top - playerborders.height
//                             && playerborders.top < platformborders.top + platformborders.height){
//                        player->setPosition(platformborders.left + platformborders.width, player->getPosition().y);
//                        break;
//                    }

//      //  }
          //}
            player->collision(platforms);

     //   }
        // Check collision with fireballs
//        for (const auto& fireball : fireballs) {
//            if (fireball->checkCollision(*player)) {
//                // Handle fireball collision
//            }
//        }

        // Check collision with hearts
//        for (const auto& heart : hearts) {
//            if (heart->checkCollision(*player)) {
//                // Handle heart collision
//                hearts.erase(std::remove_if(hearts.begin(), hearts.end(), [&](const std::unique_ptr<Heart>& h) {
//                                 return h.get() == heart.get();
//                             }), hearts.end());

//                score++;
//            }
//        }

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
