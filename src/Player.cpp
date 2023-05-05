#include "Player.h"

Player::Player(float jumpHeight) :
    Entity({ 196, 140, 16, 16 }, 1, 40),
    currentFrame(0),
    move_speed(10),
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
}

void Player::Update(float dt) {
    dt /= 100;

    processAnimation();

    sprite.setPosition(rect.left, rect.top);
}

void Player::FixedUpdate(float dt)
{
    _velocity.x *= 0.4f;
    bool is_moving = false; // ���� ��� ������������ ��������

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        _velocity.x = -1;
        is_moving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        _velocity.x = 1;
        is_moving = true;
    }
    if (!is_moving) { // ���� ������� �������� ���� ��������, ���������� �����
        _velocity.x = 0;
    }
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
    if (!is_on_ground) { // ���� ����� � �������
        if (_velocity.y > 0) { // ���� ����� ������ ����
            sprite.setTexture(_animation_textures[5]); // ����������� �������� �������� �������
        }
        else { // �����, ����� ������� �����
            sprite.setTexture(_animation_textures[4]); // ����������� �������� �������� ������ �����
        }
        sprite.setScale((_velocity.x > 0) ? 0.5f : -0.5f, 0.5f); // ���������� �����������
        sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f); // ���������� ����� �������
    }
    else { // �����, ����� �� �����
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
        currentFrame += 0.1; // ���������� �������� ����� ��������
        if (currentFrame > 6) { // ���� ����������� ��������� ��������, �������� �������
            currentFrame = 0;
        }
    }
}