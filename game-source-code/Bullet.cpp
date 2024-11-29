#include "Bullet.h"
#include <cmath>

// Constructor initializes the bullet with a starting position texture, bullet type and bullet direction
Bullet::Bullet(const sf::Vector2f &startPosition, sf::Texture &texture, BulletType bullettype, const sf::Vector2f &direction)
    : speed(0.65f), type(bullettype), bulletDirection(direction)
{

    sprite.setTexture(texture);
    sf::Vector2u size = sprite.getTexture()->getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setPosition(startPosition);
    sprite.setRotation(90.f); // Rotate by 90 degrees
    if (type == BulletType::LANDER_BULLET)
    {
        speed = 0.08f; // Lander Missiles are slower
    }
    if (type == BulletType::DEFENDER_BULLET)
    {
        sprite.setScale(0.25f, 0.25f); // Adjust the scale for defender bullets
    }
    if (type == BulletType::LANDER_BULLET)
    {
        sprite.setScale(0.1f, 0.1f); // Adjust the scale for lander bullets
    }
}
// Getter for the bullet's current position
sf::Vector2f Bullet::getPosition() const
{
    return sprite.getPosition();
}

// Setter for the bullet's position
void Bullet::setPosition(const sf::Vector2f &position)
{
    sprite.setPosition(position);
}

// Setter for the bullet's scale
void Bullet::setScale(float x, float y)
{
    sprite.setScale(x, y);
}

// Update the bullet's position
void Bullet::update()
{
    sf::Vector2f movement(bulletDirection.x * speed, bulletDirection.y * speed);
    sprite.move(movement);
}

// Draw the bullet on the window
void Bullet::draw(sf::RenderWindow &window) const
{
    window.draw(sprite);
}
