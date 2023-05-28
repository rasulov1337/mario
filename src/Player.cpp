#include "Player.h"
#include <iostream>
#include "AudioManager.h"

#include "ConfigVars.h"

Player::Player(float jumpHeight) :
    Entity({ 300, 140, 16, 16 }, 1, 100.0f),
    currentFrame(0),
    _jumpHeight(jumpHeight),
    _faceRight(false)
{
    if (!texture.loadFromFile(ASSETS_PATH + "/mario.png"))
        std::cout << "ERROR: FAILED TO LOAD MARIO TEXTURE!";

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); 
    sprite.scale(0.5, 0.5);

}

void Player::Update(float dt) {
    ProcessAnimation();

    sprite.setPosition(rect.left, rect.top);

    _velocity.x *= 0.9f;
    bool is_moving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _velocity.x = -_moveSpeed;
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _velocity.x = _moveSpeed;
        is_moving = true;
    }
    if (!is_moving) {
        _velocity.x = 0;
    }
    if (is_on_ground && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {

        AudioManager::Play("big_jump");
        _velocity.y = -sqrtf(2.0f * 981.0f * _jumpHeight);
        is_on_ground = false;
    }

    _velocity.y += 981.0f * dt;

    rect.left += _velocity.x * dt;
    rect.top += _velocity.y * dt;
}

void Player::OnCollision(sf::Vector2f direction) {
    if (direction.x < 0.0f)
        _velocity.x = 0;
    else if (direction.x > 0.0f)
        _velocity.x = 0;

    if (direction.y < 0) {
        _velocity.y = 0;
        is_on_ground = true;
    }
    else if (direction.y > 0) {
        _velocity.y = 0;
    }
}

void Player::Die() {

}

void Player::ProcessAnimation() {
    if (!is_on_ground) {
        if (_velocity.y > 0) {
            sprite.setTextureRect(sf::IntRect(5 * 32, 0, 32, 32));
        }
        else {
            sprite.setTextureRect(sf::IntRect(4 * 32, 0, 32, 32));
        }
    }
    else {
        int direction = (_velocity.x > 0) ? 1 : ((_velocity.x < 0) ? -1 : 0);
        if (direction > 0)
            _faceRight = true;
        else if (direction < 0)
            _faceRight = false;

        if (direction == 0) {
            sprite.setTextureRect(sf::IntRect(!_faceRight * 32, 0, _faceRight ? 32 : -32, 32));
        }
        else {
            int frameIndex = static_cast<int>(currentFrame) % 3 + 1;
            if (direction < 0) {
                frameIndex++;
            }
            sprite.setTextureRect(sf::IntRect(frameIndex * 32, 0, direction * 32, 32));
        }
        currentFrame += 0.1;
        if (currentFrame > 6) {
            currentFrame = 0;
        }
    }
}
