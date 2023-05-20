#include "Player.h"
#include <iostream>

Player::Player(float jumpHeight) :
    Entity({ 300, 140, 16, 16 }, 1, 100.0f),
    currentFrame(0),
    _jumpHeight(jumpHeight)
{
    sf::Texture textures[7];
   textures[0].loadFromFile("assets/marioo0.png");
        textures[1].loadFromFile("assets/marioo1.png");
        textures[2].loadFromFile("assets/marioo2.png");
        textures[3].loadFromFile("assets/marioo3.png");
        textures[4].loadFromFile("assets/marioo4.png");
        textures[5].loadFromFile("assets/marioo5.png");
        textures[6].loadFromFile("assets/marioo6.png");

    std::copy(std::begin(textures), std::end(textures), std::begin(_animation_textures));
    
    sprite.setTexture(_animation_textures[0]);
    sprite.scale(0.5, 0.5);
    
    if (!big_jump_buf.loadFromFile("assets/sounds/big_jump.wav"))
        std::cout << "ERROR: BIG JUMP SOUND FILE IS NOT LOADED!";
}

void Player::Update(float dt) {
    ProcessAnimation();

    sprite.setPosition(rect.left, rect.top);


    _velocity.x *= 0.9f;
    bool is_moving = false; // флаг для отслеживания движения

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        _velocity.x = -_moveSpeed;
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        _velocity.x = _moveSpeed;
        is_moving = true;
    }
    if (!is_moving) { // если клавиша движения была отпущена, остановить марио
        _velocity.x = 0;
    }
    if (is_on_ground && (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))) {
        
        player_sound.setBuffer(big_jump_buf);
        player_sound.play();
        _velocity.y = -sqrtf(2.0f * 981.0f * _jumpHeight);
        is_on_ground = false;
    }

    _velocity.y += 981.0f * dt;

    rect.left += _velocity.x * dt;
    rect.top += _velocity.y * dt;
}

void Player::OnCollision(sf::Vector2f direction)
{
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

void Player::Die()
{

}


void Player::ProcessAnimation() {
    if (!is_on_ground) { // Если Марио в воздухе
        if (_velocity.y > 0) { // Если Марио падает вниз
            sprite.setTexture(_animation_textures[5]); // Используйте текстуру анимации падения
        }
        else { // Иначе, Марио прыгает вверх
            sprite.setTexture(_animation_textures[4]); // Используйте текстуру анимации прыжка вверх
        }
        sprite.setScale((_velocity.x > 0) ? 0.5f : -0.5f, 0.5f); // Определите направление
        sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f); // Установите центр спрайта
    }
    else { // Иначе, Марио на земле
        int direction = (_velocity.x > 0) ? 1 : ((_velocity.x < 0) ? -1 : 0);
        if (direction == 0) {
            sprite.setTexture(_animation_textures[0]);
            sprite.setScale(0.5f, 0.5f);
        }
        else {
            sprite.setTexture(_animation_textures[(int)currentFrame % 3 + 1]);
            sprite.setScale(direction * 0.5f, 0.5f);
            sprite.setOrigin((direction == 1) ? 0.f : sprite.getGlobalBounds().width, 0.f);
        }
        currentFrame += 0.1; // увеличение текущего кадра анимации
        if (currentFrame > 6) { // если проигралась последняя текстура, начинаем сначала
            currentFrame = 0;
        }
    }
}