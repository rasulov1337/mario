#include "../Headers/Player.h"

Player::Player(): xDirection(0), yDirection(0), currentFrame(0), _speed(2) {
    texture.loadFromFile("../assets/mario.png");
    sprite.setTexture(texture);
    rect = sf::FloatRect(100, 180, 16, 16);
}


void Player::update(double deltaTime) {
    rect.left += deltaTime * xDirection * double(_speed) / 10;

    currentFrame += deltaTime * 0.01;
    if (currentFrame > 5)
        currentFrame -= 4;

    processAnimation();
	sprite.setPosition(rect.left, 0);
	  
    xDirection = 0;
}

void Player::processAnimation() {
    if (xDirection == 0) {
        sprite.setTextureRect(IntRect(0, 0, 32, 32));
        return;
    }
    
    sprite.setTextureRect(IntRect(32 * int(currentFrame), 0, 32, 32));
    
    if (xDirection < 0 && sprite.getScale().x > 0)
        sprite.setScale(-1, 1);
    else if (xDirection > 0 && sprite.getScale().x < 0)
        sprite.setScale(1, 1);
}