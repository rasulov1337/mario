#include "Goomba.h"

Goomba::Goomba(sf::Vector2f position) :
    Entity({ 196, 140, 16, 16 }, 1, 1)
{
    _texture.loadFromFile("assets/enemy.png");
    sprite.setTexture(_texture);
    sprite.setPosition(position);
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
    sprite.setPosition(rect.left, rect.top);
}

void Goomba::FixedUpdate(float dt) {
    _velocity.x = -_moveSpeed;

    if (!is_on_ground)
        _velocity.y += dt * 981.0f * _mass;

    rect.left += _velocity.x * dt * 10;
    rect.top += _velocity.y * dt;
}