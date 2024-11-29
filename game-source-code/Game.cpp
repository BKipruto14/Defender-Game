#include "Game.h"
#include "Player.h"
#include "UserInterface.h"
#include "Landers.h"
#include <iostream>
#include <SFML/Graphics.hpp>

// Constructor Initializes the Game window and loads resources
Game::Game() : window(sf::VideoMode(1100, 900), "Defender")
{
    // Load textures

    playerTexture.loadFromFile("Resources/spaceship.png");
    landerBulletTexture.loadFromFile("Resources/LandersBullet.jpg");
    bulletTexture.loadFromFile("Resources/bullet.png");
    uiFont.loadFromFile("Resources/PressStart2P-Regular.ttf");
    backgroundTexture.loadFromFile("Resources/spacebackground.png");
    landerTexture.loadFromFile("Resources/Landers.jpg");

    gameClock.restart();
    timeSinceLastLander = 0.0f;

    // Initialize game objects
    player = new Player(playerTexture, bulletTexture); // Dynamically allocate Player
    sf::Vector2f playerPos = player->getPosition();
    Landers Lander(landerTexture, landerBulletTexture, playerPos); // Load Landers and pass lander bullet texture
    ui = UserInterface(uiFont);                                    // Pass the loaded font to the UI
    backgroundSprite.setTexture(backgroundTexture);
    backgroundTexture.setRepeated(true);
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
}

void Game::displayStartScreen(sf::RenderWindow &window, sf::Font &font, sf::Texture &shipTexture)
{
    // Draw game title
    sf::Text title;
    title.setFont(font);
    title.setString("Defender");
    title.setCharacterSize(48);
    title.setPosition(200, 200);
    window.draw(title);

    // Draw ship sprite
    sf::Sprite shipSprite;
    shipSprite.setTexture(shipTexture);
    shipSprite.setPosition(350, 250);
    window.draw(shipSprite);

    // Draw instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Press Enter to Start\nUse Arrow Keys to Move\nSpace to Shoot");
    instructions.setCharacterSize(24);
    instructions.setPosition(50, 500);
    window.draw(instructions);

    sf::Text instructionText;
    instructionText.setString("Fire Once the game starts to \n start spawning Landers!");
    instructions.setCharacterSize(24);
    instructionText.setPosition(50, 600);
    instructionText.setFont(font);
    window.draw(instructionText);
}


// Main Game loop
void Game::run()
{
    // Display start screen
    while (window.isOpen())
    {
        float deltaTime = gameClock.restart().asSeconds();
        
        timeSinceLastLander += deltaTime;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                goto MainGameLoop;
            }
        }
        window.clear();
        displayStartScreen(window, uiFont, playerTexture);
        window.display();
    }

    // Main game loop
MainGameLoop:
    while (window.isOpen())
    {

        // Comment: Update the timer for lander spawning here
        float deltaTime = gameClock.restart().asSeconds();
        timeSinceLastLander += deltaTime;

        if (timeSinceLastLander >= landerSpawnInterval && player->gethasPlayerFired())
        {
            spawnLander(); // This function will handle the creation of a new lander
            timeSinceLastLander = 0.0f;
        }
        handleEvents();
        update();
        draw();
    }
}

// Returns if game window is running
bool Game::isRunning() const
{
    return window.isOpen();
}

void Game::spawnLander()
{
    sf::Vector2f playerPos = player->getPosition();
    landers.push_back(Landers(landerTexture, landerBulletTexture, playerPos));
}

// Handle SFML events
void Game::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        // Update lastKeyEvent
        player->handleInput(event);
    }
}

// Returns Players Position
sf::Vector2f Game::getPlayerPosition() const
{
    return player->getPosition();
}

// Update Game State
void Game::update()
{
    // Update game objects
    player->update();
    checkCollisions();
    for (auto &lander : landers)
    {
        if (lander.getisActive())
        {
            lander.update(player->getPosition());
        }
    }

    // Update UI (pass in current score and lives)
    int currentScore = 0; // Replace with actual score
    int currentLives = 1; // Replace with actual lives
    ui.displayScore(currentScore, window);
    ui.displayLives(currentLives, window);
}

// Draw Game State
void Game::draw()
{
    window.clear();

    // Draw the background first
    window.draw(backgroundSprite);

    // Draw game objects
    player->draw(window);

    for (auto &lander : landers)
    {
        if (lander.getisActive())
        {
            lander.draw(window);
        }
    }
    // Draw UI with updated score
    int currentScore = destroyedLanders * 100; // Get the updated score
    int currentLives = 1;
    ui.displayScore(currentScore, window);
    ui.displayLives(currentLives, window);

    window.display();
}

Game::~Game()
{
    delete player; // Delete the dynamically allocated Player
}

void Game::checkCollisions()
{
    // Access player bullets
    std::vector<Bullet> &playerBullets = player->getBullets();

    // Check collisions between player bullets and landers
    for (auto &bullet : playerBullets)
    {
        for (auto &lander : landers)
        {
            // Skip destroyed landers
            if (!lander.getisActive())
                continue;

            // Check collision between player and lander
            if (player->getSprite().getGlobalBounds().intersects(lander.getSprite().getGlobalBounds()))
            {
                DisplayGameOverScreen();
                return;
            }

            // Check collision between player bullet and lander
            if (bullet.getSprite().getGlobalBounds().intersects(lander.getSprite().getGlobalBounds()))
            {
                lander.destroy();
                destroyedLanders++;
                if (destroyedLanders*100>highScore){
                    highScore=destroyedLanders*100;
                }
                if (destroyedLanders == 15)
                {
                    DisplayGameOverScreen();
                    return;
                }

                bullet.destroy();
                continue; // Skip checking this bullet against lander missiles since it's destroyed
            }

            // Check collisions between lander missiles and player
            const std::vector<Bullet> &landerMissiles = lander.getLanderMissiles();
            for (auto &missile : landerMissiles)
            {
                if (missile.getSprite().getGlobalBounds().intersects(player->getSprite().getGlobalBounds()))
                {
                    DisplayGameOverScreen();
                    return;
                }
            }
        }
    }
}

void Game::DisplayGameOverScreen()
{
    window.clear();

    sf::Text gameOverText;
    gameOverText.setFont(uiFont);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(48);
    gameOverText.setPosition(300, 50);

    sf::Text scoreText; // Create a separate text object for the score
    scoreText.setFont(uiFont);
    scoreText.setString("Score: " + std::to_string(destroyedLanders * 100));
    scoreText.setCharacterSize(30);
    scoreText.setPosition(300, 120); // Adjust position so it's below the "Game Over" text

    sf::Text RestartGameText;
    RestartGameText.setFont(uiFont);
    RestartGameText.setString("Press R to play again");
    RestartGameText.setCharacterSize(12);
    RestartGameText.setPosition(10, 30); // Adjust position
    window.draw(RestartGameText);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
            {
                resetGame(); // Reset the game state
                window.close();
                Game game;
                game.run();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                window.close(); // Close the window if Enter is pressed
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(RestartGameText);
        window.display();
    }
}

void Game::resetGame()
{
    // Clear the list of active landers
    landers.clear();

    // Reset the player's attributes (position, health, etc.)
    player->reset();

    // Reset game timers or counters
    timeSinceLastLander = 0.0f;
    destroyedLanders = 0;

    // Any other game state resets can be added here
}