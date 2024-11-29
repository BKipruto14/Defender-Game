#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H
class Player
{
public:
    Player(sf::Texture &playerTexture, sf::Texture &bulletTexture);
    sf::Vector2f getPosition() const;
    void handleInput(sf::Event event);
    void update();
    std::vector<Bullet> &getBullets() { return playerbullets; };
    void draw(sf::RenderWindow &window);
    void shoot();
    const sf::Sprite &getSprite() const { return sprite; };
    bool gethasPlayerFired() { return hasPlayerFired; };
    void reset();
    sf::Vector2f initialPosition;

private:
    bool hasPlayerFired = false;
    int lives;
    int score;
    const sf::Vector2f direction;
    BulletType bullettype;
    sf::Texture &bulletTexture;
    sf::Texture playerTexture;
    sf::Sprite sprite;
    std::vector<Bullet> playerbullets;
    float speed;
};
#endif
