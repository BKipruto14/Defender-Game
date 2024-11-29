#include <SFML/Graphics.hpp>
#include "Player.h"
#include "UserInterface.h"
#include "Landers.h"
#ifndef GAME_H
#define GAME_H
class Game
{
public:
    Game();
    bool isRunning() const;
    sf::Keyboard::Key lastEventHandled() const;
    sf::Vector2f getPlayerPosition() const;
    ~Game();
    void update();
    void handleEvents();
    void run();
    void checkCollisions();
    void DisplayGameOverScreen();
    void spawnLander();
    const float landerSpawnInterval = 2.0f; // 3 seconds
    int TotalDestroyedLanders;
    void resetGame();

private:
    
    static int highScore;
    int destroyedLanders = 0;
    sf::Clock gameClock;
    float timeSinceLastLander = 0.0f;
    std::vector<Landers> landers;
    void endRound();
    void draw();
    void displayStartScreen(sf::RenderWindow &window, sf::Font &font, sf::Texture &shipTexture);
    sf::Event eventQueue;
    sf::Texture bulletTexture;
    sf::Texture landerBulletTexture;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Clock clock;
    sf::RenderWindow window;
    Player *player; // Pointer to Player
    UserInterface ui;
    sf::Texture playerTexture;
    sf::Font uiFont;
    sf::Texture landerTexture;
};

#endif
