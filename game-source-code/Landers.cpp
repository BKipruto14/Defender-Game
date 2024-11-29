#include "Landers.h"
#include <cmath>
#include <cstdlib> // For random movement

Landers::Landers(sf::Texture &texture, sf::Texture &missileTexture, const sf::Vector2f &playerStartPosition)
    : missileTexture(missileTexture), speed(0.08f), shootCooldown(0)
{
    sprite.setTexture(texture);
    sprite.setScale(0.08f, 0.08f);
    sf::Vector2u size = sprite.getTexture()->getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sf::Vector2f spawnPosition;
    do
    {
        spawnPosition = sf::Vector2f(rand() % 800, rand() % 600);
    } while (sqrt(pow(spawnPosition.x - playerStartPosition.x, 2) + pow(spawnPosition.y - playerStartPosition.y, 2)) < 150);

    sprite.setPosition(spawnPosition);

    // Initialize direction and timer for random movement
    setRandomDirection();
    moveClock.restart();
}

void Landers::update(const sf::Vector2f &playerPosition)
{
    sprite.move(velocity);

    // Change direction after a certain duration
    if (moveClock.getElapsedTime().asSeconds() > 5.0f)
    { // Change direction every 2 seconds
        setRandomDirection();
        moveClock.restart();
    }
    // Check top boundary
    if (sprite.getPosition().y < 0)
    {
        sprite.setPosition(sprite.getPosition().x, 0);
        // Optionally change direction, e.g., reverse vertical velocity
        velocity.y = -velocity.y;
    }

    // Check bottom boundary
    if (sprite.getPosition().y + sprite.getGlobalBounds().height > 950)
    {
        sprite.setPosition(sprite.getPosition().x, 950 - sprite.getGlobalBounds().height);
        // Optionally change direction
        velocity.y = -velocity.y;
    }
    // Check left boundary
    if (sprite.getPosition().x < 0)
    {
        sprite.setPosition(0, sprite.getPosition().y);
        // Optionally change direction, e.g., reverse horizontal velocity
        velocity.x = -velocity.x;
    }

    // Check right boundary
    if (sprite.getPosition().x + sprite.getGlobalBounds().width > 1000)
    {
        sprite.setPosition(1000 - sprite.getGlobalBounds().width, sprite.getPosition().y);
        // Optionally change direction
        velocity.y = -velocity.y;
    }
    if (shootingClock.getElapsedTime().asSeconds() > nextShootTime)
    {
        shoot(playerPosition);
        resetShootingTimer();
    }
    // Occasionally shoot at the player
    if (shootCooldown <= 0)
    {
        if (rand() % 100 < 5) // 5% chance to shoot
        {
            shoot(playerPosition);
            shootCooldown = 16000; // Reset cooldown
        }
    }
    else
    {
        shootCooldown--;
    }

    // Update missiles
    for (auto &missile : missiles)
    {
        missile.update();
    }
}

void Landers::draw(sf::RenderWindow &window)
{
    window.draw(sprite);

    for (const auto &missile : missiles)
    {
        missile.draw(window);
    }
}

void Landers::shoot(const sf::Vector2f &playerPosition)
{
    // Calculate the direction vector
    sf::Vector2f direction = playerPosition - sprite.getPosition();
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normalize the vector

    Bullet missile(sprite.getPosition(), missileTexture, BulletType::LANDER_BULLET, direction); // Use Bullet class to handle Lander Missiles
    missiles.push_back(missile);
}

void Landers::resetShootingTimer()
{

    nextShootTime = 2.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / 3.0f)); // Reset Timer for Landers to shoot again
    shootingClock.restart();
}

void Landers::setRandomDirection()
{
    // Generate a random angle between 0 and 2*PI
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159265f; // 2*PI

    // Convert polar coordinates to Cartesian coordinates
    velocity.x = speed * cos(angle);
    velocity.y = speed * sin(angle);
}
