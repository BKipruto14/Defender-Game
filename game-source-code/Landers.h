#ifndef LANDER_H
#define LANDER_H

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>

class Landers
{
public:
    Landers(sf::Texture &texture, sf::Texture &missileTexture, const sf::Vector2f &playerStartPosition);
    void update(const sf::Vector2f &playerPosition);
    void draw(sf::RenderWindow &window);
    const std::vector<Bullet> &getLanderMissiles() const { return missiles; };
    const sf::Sprite &getSprite() const { return sprite; };
    void shoot(const sf::Vector2f &playerPosition);
    void resetShootingTimer();
    void destroy() { isActive = false; };
    bool getisActive() const { return isActive; };
    bool BulletDirection;
    sf::Vector2f getPosition() const { return sprite.getPosition(); };
    const std::vector<Bullet> &getMissiles() const { return missiles; };

private:
    bool isActive = true;
    void setRandomDirection();
    sf::Clock moveClock;
    sf::Clock shootingClock; // Timer for shooting
    float nextShootTime;     // Time (in seconds) for the next shot
    sf::Sprite sprite;
    sf::Texture &missileTexture;
    std::vector<Bullet> missiles;
    float speed;
    sf::Vector2f velocity;
    int shootCooldown; // Cooldown timer to control shooting frequency
};

#endif
