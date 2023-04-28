#include "Player.h"

Player::Player() :
    currentFrame(0),
    rb({ 196, 140, 16, 16 }, 10),
    move_speed(10)
{
    texture.loadFromFile("assets/mario.png");
    sprite.setTexture(texture);
    sprite.scale(0.5, 0.5);
}


void Player::Update(float dt) {
    dt /= 100;

    // ѕотом с анимацией надо будет повозитьс€...
    currentFrame += dt * 0.01;
    if (currentFrame > 5)
        currentFrame -= 4;

    processAnimation();

    sprite.setPosition(rb.rect.left, rb.rect.top);
    HandleMovement(dt);

}

void Player::FixedUpdate(float fixed_dt)
{
}

void Player::HandleMovement(float dt) {
    int x = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        x = -1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        x = 1;
    if (/*rb.is_on_ground &&*/ sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        rb.rect.top -= 10;
        rb.is_on_ground = false;
    }

    rb.rect.left += x * dt * move_speed;
}

void Player::processAnimation() {
    //auto& xVelocity = body->GetLinearVelocity().x;
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        return;
    
    //int sign = xVelocity < 0 ? -1 : 1;
    //sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, sign * 32, 32));
}