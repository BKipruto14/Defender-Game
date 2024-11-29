#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

enum class BulletType
{
    DEFENDER_BULLET,
    LANDER_BULLET
};

class Bullet
{
public:
    Bullet(const sf::Vector2f &startPosition, sf::Texture &texture, BulletType type = BulletType::DEFENDER_BULLET, const sf::Vector2f &bulletdirection = sf::Vector2f(0, -1));
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &position);
    void setScale(float x, float y);
    void update();
    void draw(sf::RenderWindow &window) const;
    const sf::Sprite &getSprite() const { return sprite; };
    void destroy() { isActive = false; };
    bool getIsActive() const { return isActive; };

private:
    const sf::Vector2f bulletDirection; // vector determining where bullet travels
    bool isActive = true;
    BulletType type;
    sf::Sprite sprite;
    float speed;
};

#endif
