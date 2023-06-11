std::pair<float, float> getRandomPosition(const sf::RenderWindow& window )   //To get Random positions {Fireballs}
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
    fireball1->setPosition(0.0f, 420.0f );
    fireball1->setScale(0.50f,0.50f);
    fireballs.push_back(std::move(fireball1));
    std::unique_ptr<Fireball> fireball2 = std::make_unique<Fireball>(fireballTexturePath);
    fireball2->setPosition(0.0f, 780.0f );
    fireball2->setScale(0.50f,0.50f);
    fireballs.push_back(std::move(fireball2));
    std::unique_ptr<Fireball> fireball3 = std::make_unique<Fireball>(fireballTexturePath);
    fireball3->setPosition(0.0f, 10.0f );
    fireball3->setScale(0.50f,0.50f);
    fireballs.push_back(std::move(fireball3));


}

void resetFireballs(std::vector<std::unique_ptr<Fireball>>& fireballs) {
    // Reset fireballs to their initial positions
    fireballs[0]->setPosition(0.0f, 450.0f);
    fireballs[1]->setPosition(0.0f, 700.0f);
    fireballs[2]->setPosition(0.0f, 0.0f);
}


// void restartGame(const std::unique_ptr<Player> &player,std::string fireballTexturePath ,std::vector<std::unique_ptr<Fireball>> &fireballs) {    
//     // Reset the player's position and other game states
//     player->setPosition(700.0f, 350.0f);
//     fireballs.clear();
//     createFireballs(fireballTexturePath,fireballs);  // Function to create initial fireballs
    
// }   
void createGold(std::unique_ptr<Gold> &gold ,const sf::RenderWindow& window ){   // Creating Gold object
    std::pair<float, float> position = getRandomPosition(window);
    gold->setPosition(position.first, position.second);
    gold->setScale(0.40f, 0.40f);
}
void createHeart(std::unique_ptr<Heart> &heart ,const sf::RenderWindow& window ){   //Creating Heart object
    std::pair<float, float> position = getRandomPosition(window);
    heart->setPosition(position.first, position.second);
    heart->setScale(0.20f, 0.20f);
}


int main()
{
    const int windowWidth = 1500;
    const int windowHeight = 900;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Artic Jump");

    // Load textures
    std::string playerTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\player_texture.png";
    std::string heartTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\CroppedHeart1.png";
    std::string goldTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\CroppedGoldBag1.png";
    std::string platformTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\wall.png";
    std::string fireballTexturePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\CroppedFireball.png";
    std::string backGroundTexurePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\actic.png";
    std::string startbgTexurePath = "C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\Arctic_Jump.png";
    // Create objects
     std::unique_ptr<Player> player = std::make_unique<Player>(playerTexturePath);
    player->setPosition(700.0f, 350.0f);
    player->setScale(0.15f,0.15f);
    std::unique_ptr<Immovable> startbg= std::make_unique<Immovable>(startbgTexurePath);
    startbg->setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    std::unique_ptr<Immovable> background = std::make_unique<Immovable>(backGroundTexurePath);
    background->setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


        std::vector<std::unique_ptr<Immovable>> platforms;                                             // Platforms {5}
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

        std::vector<std::unique_ptr<Fireball>> fireballs;      // Fireball objects
        createFireballs(fireballTexturePath,fireballs);

        std::unique_ptr<Heart> hearts = std::make_unique<Heart>(heartTexturePath);;  //Heart object
        createHeart(hearts,window);
        std::unique_ptr<Gold> gold = std::make_unique<Gold>(goldTexturePath);   // Gold object
        createGold(gold,window);

    // Create a vector of Sprites
    std::vector<Sprites*> objects;
    objects.push_back((startbg.get()));
    objects.push_back((background.get()));
    objects.push_back(player.get());
    for (const auto& platform : platforms) {
        objects.push_back(platform.get());
    }
    for (const auto& fireball : fireballs) {
        objects.push_back(fireball.get());
    }
    objects.push_back(hearts.get());

    objects.push_back(gold.get());

    const int bonus = 5;
    int life;
     // Blast sprite
    sf::Texture blastTexture;
    if (!blastTexture.loadFromFile("C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\blast_.png")) {
        return EXIT_FAILURE;
    }

    sf::Sprite blastSprite(blastTexture);
    int blastFrame = 0;
    int blastFrameCounter = 0;
    bool blasting = false;
    blastSprite.setTextureRect(sf::IntRect(0, 0, blastTexture.getSize().x / numBlastFrames, blastTexture.getSize().y));
    blastSprite.setOrigin(blastSprite.getTextureRect().width / 2, blastSprite.getTextureRect().height / 2);
    blastSprite.setPosition(windowWidth / 2, windowHeight / 2);

    sf::Vector2f blastPosition
    // For music
    sf::Music music;
    if (!music.openFromFile("C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\2gucu-s4oo4.wav"))
    {
        return EXIT_FAILURE;
    }
    music.setLoop(true);
    music.play();
    // Inside the main function or the game loop, initialize the font and set properties for the text objects:
    sf::Font font;
    if (!font.loadFromFile("C:\\Users\\moham\\OneDrive\\Documents\\build-game11-Desktop_Qt_6_4_3_MinGW_64_bit-Debug\\Arial.ttf") ){
        // Error handling for font loading failure
        std::cerr << "Failed to load font" << std::endl;
    }

    // Start Text

    sf::Text startText;
    startText.setFont(font);
    startText.setCharacterSize(60);
    startText.setFillColor(sf::Color::Red);
    startText.setString("START");
    startText.setPosition(880.0f, 620.0f);
    bool gameEnded = false;
    bool gameStarted = false;

    // Restart button
    sf::Text restartButton;
    restartButton.setFont(font);
    restartButton.setCharacterSize(60);
    restartButton.setFillColor(sf::Color::Red);
    restartButton.setString("RESTART");
    restartButton.setPosition(840.0f, 620.0f);
    bool restartClicked = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    if (startText.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {

                        gameStarted = true;
                    }
                    if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {

                        // Reset game variables
                        player->resetLives();
                        player->resetLives();

                        restartClicked = true;
                    }
                }
            }
        }

        // Update player movement and collision
       player->update(platforms,window,life);
        hearts->update(platforms,window);
        gold->update(platforms,window);
               //Text initializing
        sf::Text scoreText;
        sf::Text livesText;
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);

        livesText.setFont(font);
        livesText.setCharacterSize(24);
        livesText.setFillColor(sf::Color::White);

        // Inside the game loop or wherever you update the score and lives
        int score = player->getBonusPoints();
        int remainingLives = player->getLives();

        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setPosition(10.0f, 10.0f); // Adjust the position as needed

        livesText.setString("Lives: " + std::to_string(remainingLives));
        livesText.setPosition(10.0f, 40.0f); // Adjust the position as needed
//         if (life==0){
//             player->resetLives();
//             window.close();

//         } 
        if (gameStarted){
        if (!gameEnded){
        
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
        for (const auto& fireball : fireballs) {
            if (fireball->checkCollision(*player)) {
                player->decreamentLive(1);
                player->setPosition(700.0f, 350.0f);
                resetFireballs(fireballs);
                 blastPosition = player->getPosition();

                blasting = true;
                //blastSound.play();

                blastFrame = 0;
                blastFrameCounter = 0;
//                // Create blast animation
//                Blast blast(blastTextures, 10.0f);  // Adjust the frame rate as needed
//                blast.setPosition(fireball->getPosition());

                createGold(gold,window);
                createHeart(hearts,window);
                
                break;
            }
        }


  // Check collision with hearts
        
        //
        if (hearts->checkCollision(*player)) {
            createHeart(hearts,window);
            player->incrementLives();
          //  std::cout<<"heart"<<std::endl;
       }

        // Check collision with gold
        if (gold->checkCollision(*player)) {
            // Handle gold collision
            createGold(gold,window);
            player->incrementBonusPoints(bonus);
          
        }

        window.clear();

         for (const auto& object : objects) {
            window.draw(*object);
        }
             if (blasting) {
            blastFrameCounter++;
            if (blastFrameCounter >= blastFrameDuration) {
                blastFrame++;
                blastFrameCounter = 0;
                if (blastFrame >= numBlastFrames) {
                    blasting = false;
                    blastFrame = 0;
                }
            }
            blastSprite.setTextureRect(sf::IntRect(blastFrame * blastSprite.getTextureRect().width, 0, blastSprite.getTextureRect().width, blastSprite.getTextureRect().height));
            blastSprite.setPosition(blastPosition);
            window.draw(blastSprite);
        }
        window.draw(scoreText);
        window.draw(livesText);


        if   (life==0){
            player->resetLives();
            gameEnded = true;

//            window.close();
            window.draw(*startbg);
            window.draw(restartButton);
        }
        window.display();

        }

        if (restartClicked) {

        // Reset game variables
        player->resetScore();
        player->resetLives();

        gameEnded = false;
        restartClicked = false;
        }

        }
        else {
        window.clear();
        window.draw(*startbg);
        window.draw(startText);
        window.display();
        }


    }

    return 0;
}

