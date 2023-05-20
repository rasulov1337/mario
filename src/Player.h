#include "Entity.h"
#include <SFML/Audio.hpp>

using namespace sf;

/// <summary>
/// Класс игрока
/// </summary>
class Player : public Entity {
public:
    sf::Texture _animation_textures[7];
    explicit Player(float jumpHeight);

    void Update(float dt) override;
    void OnCollision(sf::Vector2f direction) override;

    void Die() override;
private:
    sf::Texture texture;
    double currentFrame;
    float _jumpHeight;

    sf::Sound player_sound;
    sf::SoundBuffer big_jump_buf;
    sf::SoundBuffer small_jump_buf;


    void ProcessAnimation();
};