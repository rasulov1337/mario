
#include "Goomba.h"

Goomba::Goomba(sf::Vector2f position) :
    Entity({ position.x, position.y - 10, 16, 16 }, 1, 1),
    currentFrame(0),
    timeElapsed(0)
{
    _texture.loadFromFile("assets/enemy.png");

    sprite.setTexture(_texture);
    sprite.setScale(0.5, 0.5);

    sprite.setPosition(position);
}



Goomba::Goomba(const Goomba& other) :
    Entity(other),
    timeElapsed(0),
    currentFrame(0)
{
    if (this == &other)
        return;

    _texture = other._texture;
    sprite.setTexture(_texture);
    sprite.setPosition(other.sprite.getPosition());

}

Goomba& Goomba::operator=(const Goomba& other)
{
    if (this == &other)
        return *this;

    return *this;
}

void Goomba::Update(float dt)
{
    _velocity.x = -_moveSpeed;

    if (!is_on_ground)
        _velocity.y += dt * 981.0f;

    rect.left += _velocity.x * dt * 10;
    rect.top += _velocity.y * dt;

    const float oneFrameLength = 0.4;
    const int numberOfFrames = 2;

    timeElapsed += dt;
    if (timeElapsed >= oneFrameLength * numberOfFrames) {
        timeElapsed = 0;
    }

    int frameIndex = timeElapsed / oneFrameLength;
    sprite.setTextureRect(sf::IntRect(frameIndex * 32, 0, 32, 32));
    sprite.setScale(0.5f, 0.5f);

    timeElapsed += dt;
    if (timeElapsed >= 2) {
        timeElapsed = 0;
    }

    sprite.setPosition(rect.getPosition());
}

void Goomba::OnCollision(sf::Vector2f direction)
{
    if (direction.y > 0) {
        Die();
    }
    if (direction.x != 0.0f)
        _moveSpeed = -_moveSpeed;

    if (direction.y < 0) {
        _velocity.y = 0;
        is_on_ground = true;
    }

}

void Goomba::Die()
{
    if (dead) {
        return;
    }

    AudioManager::Play("goomba_death");
    __delete = true;
    dead = true;
    _collider.disabled = true;

    sf::IntRect deathRect(64, 0, 32, 32);
    sprite.setTextureRect(deathRect);
}