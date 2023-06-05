std::pair<float, float> getRandomPosition()
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
           (y >= 300.0f && y <= 150.0f))
    {
        x = distX(gen);
        y = distY(gen);
    }

    return std::make_pair(x, y);
}
void createFireballs(std::string fireballTexturePath ,std::vector<std::unique_ptr<Fireball>> &fireballs ){
    
    std::unique_ptr<Fireball> fireball1 = std::make_unique<Fireball>(fireballTexturePath);
    fireball1->setPosition(-900.0f, 300.0f );
    fireball1->setScale(0.80f,0.80f);
    fireballs.push_back(std::move(fireball1));
    
    std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
    fireball2->setPosition(-900.0f, -300.0f );
    fireball2->setScale(0.80f,0.80f);
    fireballs.push_back(std::move(fireball2));
    std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
    fireball3->setPosition(-900.0f, 0.0f );
    fireball3->setScale(0.80f,0.80f);
    fireballs.push_back(std::move(fireball3));
    
    
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Platformer Game");

    // Load textures
    std::string playerTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\player_texture.png";
    std::string heartTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\BG_heart.png";
    std::string goldTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\BG_goldbag.png";
    std::string platformTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\wall.png";
    std::string fireballTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\BG_fireball.png";
    std::string backGroundTexurePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\actic.png";

    // Create objects
    std::unique_ptr<Player> player = std::make_unique<Player>(playerTexturePath);
    player->setPosition(500.0f, 350.0f);
    player->setScale(0.15f,0.15f);

    std:unique_ptr<Immovable> background = std::make_unique<Immovable>(backGroundTexurePath);
    background->setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


    std::vector<std::unique_ptr<Immovable>> platforms;
//    for (int i = 0; i < 6; i++) {
        std::unique_ptr<Immovable> platform1 = std::make_unique<Immovable>(platformTexturePath);
        platform1->setPosition(300,250);
        platform1->setScale(1.2f, 0.40f);
        platforms.push_back(std::move(platform1));
        std::unique_ptr<Immovable> platform2 = std::make_unique<Immovable>(platformTexturePath);
        platform2->setPosition( 120.0f, 650.0f);
        platform2->setScale(1.2f, 0.40f);
        platforms.push_back(std::move(platform2));
        std::unique_ptr<Immovable> platform3 = std::make_unique<Immovable>(platformTexturePath);
        platform3->setPosition( 650.0f, 500.0f);
        platform3->setScale(1.2f, 0.40f);
        platforms.push_back(std::move(platform3));
        std::unique_ptr<Immovable> platform4 = std::make_unique<Immovable>(platformTexturePath);
        platform4->setPosition( 1050.0f, 200.0f);
        platform4->setScale(1.2f, 0.40f);
        platforms.push_back(std::move(platform4));
        std::unique_ptr<Immovable> platform5 = std::make_unique<Immovable>(platformTexturePath);
        platform5->setPosition(1200.0f, 800.0f);
        platform5->setScale(1.2f, 0.40f);
        platforms.push_back(std::move(platform5));
//    }

   std::vector<std::unique_ptr<Fireball>> fireballs;
////    //for (int i = 0; i < 3; i++) {
        std::unique_ptr<Fireball> fireball1 = std::make_unique<Fireball>(fireballTexturePath);
        fireball1->setPosition(-900.0f, 300.0f );
        fireball1->setScale(0.80f,0.80f);
        fireballs.push_back(std::move(fireball1));
        std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
        fireball2->setPosition(-900.0f, -300.0f );
        fireball2->setScale(0.80f,0.80f);
        fireballs.push_back(std::move(fireball2));
        std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
        fireball3->setPosition(-900.0f, 0.0f );
        fireball3->setScale(0.80f,0.80f);
        fireballs.push_back(std::move(fireball3));


//        for (int i = 0; i < 3; i++) {

//        std::unique_ptr<Fireball> fireball1 = std::make_unique<Fireball>(fireballTexturePath);
//                fireball1->setPosition(-900.0f, 300.0f );
//                fireball1->setScale(0.80f,0.80f);
//                fireballs.push_back(std::move(fireball1));
//                std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
//                fireball2->setPosition(-900.0f, -300.0f );
//                fireball2->setScale(0.80f,0.80f);
//                fireballs.push_back(std::move(fireball2));
//                std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
//                fireball3->setPosition(-900.0f, 0.0f );
//                fireball3->setScale(0.80f,0.80f);
//                fireballs.push_back(std::move(fireball3));
//        }

   // }

//    std::vector<std::unique_ptr<Heart>> hearts;
//    for (int i = 0; i < 3; i++) {
//        std::unique_ptr<Heart> heart = std::make_unique<Heart>(heartTexturePath);
//        heart->setPosition(200.0f * (i + 1), 600.0f);
//        hearts.push_back(std::move(heart));
//    }



        std::unique_ptr<Gold> gold = std::make_unique<Gold>(goldTexturePath);
        std::pair<float, float> randomPosition = getRandomPosition();
        gold->setPosition(randomPosition.first, randomPosition.second);
        gold->setScale(0.40f, 0.40f);




//    std::unique_ptr<Gold> gold = std::make_unique<Gold>(goldTexturePath);
//    gold->setPosition(500.0f, 600.0f);
//    gold->setScale(0.25f,0.25f);
    // Create a vector of Sprites
    std::vector<Sprites*> objects;
    objects.push_back((background.get()));
    objects.push_back(player.get());
    for (const auto& platform : platforms) {
        objects.push_back(platform.get());
    }
    for (const auto& fireball : fireballs) {
        objects.push_back(fireball.get());
    }
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
        player->update(platforms);
//        // move the fire balls
//        for (const auto& fireball : fireballs) {
//            fireball->moveInDirection();
//        }

        for (const auto& fireball : fireballs) {
            fireball->moveInDirection();

            // Check if the fireball has passed the window's right edge
            if (fireball->getPosition().x > window.getSize().x) {
                // Set the fireball's position off-screen to the left
                sf::Vector2f pos= fireball->getPosition();
                fireball->setPosition(-900.0f, pos.y);

                // Update the position of the next fireball
                float lastFireballX = fireball->getPosition().x;
                float nextFireballX = lastFireballX - 300.0f;
                if (nextFireballX < -900.0f) {
                    nextFireballX = -900.0f;
                }
                fireball->setPosition(nextFireballX, pos.y);
            }
        }


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
