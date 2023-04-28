#include "Entity.h"

using namespace sf;

/// <summary>
/// Класс игрока
/// </summary>
class Player : public Entity {
public:
    explicit Player(float jumpHeight);

    void Update(float dt);
    void FixedUpdate(float dt);

    sf::Sprite sprite;

    float move_speed;
private:
    sf::Texture texture;

    double currentFrame;
    float _jumpHeight;


    void processAnimation();
};