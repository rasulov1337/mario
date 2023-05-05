#include "Player.h"

Player::Player(float jumpHeight) :
    Entity({ 196, 140, 16, 16 }, 1, 40),
    currentFrame(0),
    move_speed(10),
    _jumpHeight(jumpHeight)
{
    _texture.loadFromFile("assets/mario.png");
    sprite.setTexture(_texture);
    sprite.scale(0.5, 0.5);
}

void Player::Update(float dt) {
    dt /= 100;

    // ѕотом с анимацией надо будет повозитьс€...
    currentFrame += dt * 0.01;
    if (currentFrame > 5)
        currentFrame -= 4;

    processAnimation();

    sprite.setPosition(rect.left, rect.top);
}

void Player::FixedUpdate(float dt)
{
    _velocity.x *= 0.4f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        _velocity.x = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        _velocity.x = 1;

    if (is_on_ground && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
        _velocity.y = -sqrtf(2.0f * 981.0f * _jumpHeight);
        is_on_ground = false;
    }

    if (!is_on_ground)
        _velocity.y += dt * 981.0f * _mass;

    rect.left += _velocity.x * dt * 100;
    rect.top += _velocity.y * dt;
}


void Player::processAnimation() {
    //auto& xVelocity = body->GetLinearVelocity().x;
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        return;
    
    //int sign = xVelocity < 0 ? -1 : 1;
    //sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, sign * 32, 32));
}