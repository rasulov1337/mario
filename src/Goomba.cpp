#include "Goomba.h"

Goomba::Goomba(sf::Vector2f position) :
    Entity({position.x, position.y - 10, 16, 16}, 1, 1)
{
    _texture.loadFromFile("assets/enemy.png");
    sprite.setTexture(_texture);
    sprite.setPosition(position);
    if (!goomba_death_buf.loadFromFile("assets/sounds/mario_death.wav"))
        std::cout << "ERROR: GOOMBA DEATH SOUND FILE IS NOT LOADED!";
}

Goomba::Goomba(const Goomba& other) : Entity(other)
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

    sprite.setPosition(rect.left, rect.top);
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
}
