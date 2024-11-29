#include <SFML/Graphics.hpp>
#ifndef USERINTERFACE_H
#define USERINTERFACE_H
class UserInterface
{
public:
    UserInterface();
    UserInterface(sf::Font &font);
    sf::Text getScoreText() const;
    sf::Text getLivesText() const;
    void displayScore(int score, sf::RenderWindow &window);
    void displayLives(int lives, sf::RenderWindow &window);
    
private:
    sf::Font uiFont;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
   
};
#endif
