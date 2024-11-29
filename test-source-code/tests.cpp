#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Game.h"
#include "Player.h"
#include "bullet.h"
#include "Bullet.h"
#include "UserInterface.h"

using namespace std;

////////////// Game Tests
TEST_CASE("Game initializes correctly")
{
    Game game;
    CHECK(game.isRunning() == true);  //create game object and check if it is running
}

TEST_CASE("Game updates state")
{
    Game game;
    game.update();
    // Check that some state has changed, e.g., player position, score, etc.
    CHECK(game.getPlayerPosition() != sf::Vector2f(0, 0));
}

TEST_CASE("Player Initialization")
{
    sf::Texture playerTexture;
    playerTexture.loadFromFile("spaceship.png");
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("bullet.png");
    Player player(playerTexture, bulletTexture);                 // Check if Player object is created correctly

    CHECK(player.getPosition() == sf::Vector2f(100, 100));
}

TEST_CASE("Player Shooting")
{
    sf::Texture playerTexture;
    playerTexture.loadFromFile("spaceship.png");
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("bullet.png");
    Player player(playerTexture, bulletTexture);

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Space;

    player.handleInput(event);
    CHECK(player.getBullets().size() == 1);                       //Check if bullet object is created from spacebar press
}

////////// Bullet tests

TEST_CASE("Bullet Initialization")
{
    sf::Texture texture;
    texture.loadFromFile("bullet.png");
    sf::Vector2f position(100, 100);
    Bullet bullet(position, texture);          // Create bullet object and check if it is created properly

    CHECK(bullet.getPosition() == position);
}

TEST_CASE("Bullet Movement")
{
    sf::Texture texture;
    texture.loadFromFile("bullet.png");
    sf::Vector2f position(100, 100);
    Bullet bullet(position, texture, BulletType::DEFENDER_BULLET, sf::Vector2f(0, -1));         // Create Bullet object and check if it moves

    bullet.update();
    CHECK(bullet.getPosition().y <= 100);
}

/////////UserInterfaceTests

TEST_CASE("UserInterface Initialization")
{
    sf::Font font;
    font.loadFromFile("PressStart2P-Regular.ttf");
    UserInterface ui(font);                               // Check if font is loaded accurately and Score and Lives are intialized correctly

    CHECK(ui.getScoreText().getString() == "Score: 0");
    CHECK(ui.getLivesText().getString() == "Lives: 3");
}

TEST_CASE("UserInterface Display Score")
{
    sf::Font font;
    font.loadFromFile("Resources/PressStart2P-Regular.ttf");
    UserInterface ui(font);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");           // Check if score displays accurate information
    ui.displayScore(100, window);

    CHECK(ui.getScoreText().getString() == "Score: 100");
}

TEST_CASE("UserInterface Display Lives")
{
    sf::Font font;
    font.loadFromFile("Resources/PressStart2P-Regular.ttf");
    UserInterface ui(font);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window") ;           // Check if lives displays accurate information
    ui.displayLives(2, window);

    CHECK(ui.getLivesText().getString() == "Lives: 2");
}

////Lander Tests

TEST_CASE("Test Lander Initialization") {
    sf::Texture texture, missileTexture;
    sf::Vector2f playerPos(1,1) ;
    Landers lander(texture, missileTexture,playerPos);

    CHECK(lander.getPosition().x >= 0);
    CHECK(lander.getPosition().x <= 800);
    CHECK(lander.getPosition().y >= 0);
    CHECK(lander.getPosition().y <= 600);
}

TEST_CASE("Test Lander Movement") {
    sf::Texture texture, missileTexture;
    sf::Vector2f playerPos(1,1) ;
    Landers lander(texture, missileTexture,playerPos);

    sf::Vector2f initialPosition = lander.getPosition();
    lander.update(sf::Vector2f(400, 300));  // Passing player position for shooting logic

    // Ensure the lander has moved
    CHECK(lander.getPosition() != initialPosition);
}

TEST_CASE("Test Lander Shooting") {
    sf::Texture texture, missileTexture;
    sf::Vector2f playerPos(1,1) ;
    Landers lander(texture, missileTexture,playerPos);

    int initialMissileCount = lander.getMissiles().size();
    lander.shoot(sf::Vector2f(400, 300));

    // Ensure a missile has been shot
    CHECK(lander.getMissiles().size() == initialMissileCount + 1);
}
