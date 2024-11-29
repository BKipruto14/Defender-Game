#include "Player.h"
#include "Bullet.h"
#include <cmath>



// Constructor initializes the player with textures for the player and bullets
Player::Player(sf::Texture &playerTexture, sf::Texture &bulletTexture)
    : bulletTexture(bulletTexture) // Initialize bulletTexture
{
    sprite.setTexture(playerTexture);
    sf::Vector2u size = sprite.getTexture()->getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setPosition(100, 100);
    initialPosition = sf::Vector2f(100, 100); // Initialize initialPosition
    sprite.setScale(0.25f, 0.25f);
    sprite.setRotation(90.f); // Rotate by 90 degrees
}

// Handle keyboard input for the player
void Player::handleInput(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            hasPlayerFired = true;
            shoot();
        }
    }
}

// Update the player's position and bullets
void Player::update()
{

    // Move the player based on arrow key inputs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        sprite.setRotation(-90.0f);
        sprite.move(-0.3, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        sprite.setRotation(90.0f);
        sprite.move(0.3, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sprite.move(0, -0.3);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sprite.move(0, 0.3);
    }

    for (Bullet &bullet : playerbullets)
    {
        if (bullet.getIsActive())
        {
            bullet.update();
        }
    }
}

// Draw the player and bullets on the window
void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);

    // Draw bullets
    for (auto &bullet : playerbullets)
    {
        if (bullet.getIsActive())
        {
            bullet.draw(window);
        }
    }
}

sf::Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

// Shoot a bullet from the player's current position
void Player::shoot()
{

    sf::Vector2f shipPosition = sprite.getPosition();
    // Calculate the direction vector based on the ship's rotation
    float rotationInRadians = (sprite.getRotation() - 90.0f) * (3.14159265f / 180.0f); // Convert to radians
    sf::Vector2f Direction(cos(rotationInRadians), sin(rotationInRadians));

    Bullet newBullet(shipPosition, bulletTexture, BulletType::DEFENDER_BULLET, Direction);
    sf::Vector2u shipSize = sprite.getTexture()->getSize();
    newBullet.setPosition(sf::Vector2f(shipPosition.x + shipSize.x / 16, shipPosition.y)); // Bullet emitted from tip of ship
    newBullet.setScale(0.05f, 0.05f);                                                      // Scale down the bullet
    playerbullets.push_back(newBullet);
}

void Player::reset()
{
    // Reset the player's position to its initial value
    sprite.setPosition(initialPosition); // Assuming you have an initialPosition variable
    // Clear any bullets or other attributes related to the player
    playerbullets.clear();
    // Reset any other attributes of the player to their initial values
    // ...
}

