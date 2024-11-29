#include "UserInterface.h"
#include "iostream"

// Default constructor
UserInterface::UserInterface()
{

    font.loadFromFile("Resources/PressStart2P-Regular.ttf");

    // Initialize score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    // Initialize lives text
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(700, 10);

}

UserInterface::UserInterface(sf::Font &font)
{
    // Initialize with the given font
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10); // Top-left corner
    scoreText.setString("Score: 0");

    // Initialize lives text
    livesText.setFont(font);
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(300, 10); // middle 
    livesText.setString("Lives: 3");

}

// Returns Score
sf::Text UserInterface::getScoreText() const
{
    return scoreText;
}

// Returns Lives
sf::Text UserInterface::getLivesText() const
{
    return livesText;
}

// displays score
void UserInterface::displayScore(int score, sf::RenderWindow &window)
{
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);
}

// Displays lives
void UserInterface::displayLives(int lives, sf::RenderWindow &window)
{
    livesText.setString("Lives: " + std::to_string(lives));
    window.draw(livesText);
}
