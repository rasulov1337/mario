#include <SFML/Graphics.hpp>
#include "RigidBody.h"

using namespace sf;

/// <summary>
/// Класс игрока
/// </summary>
class Player : public GameComponent {
public:
    explicit Player();

    void Update(float dt);
    void FixedUpdate(float fixed_dt);
    void HandleMovement(float dt);

    sf::Sprite sprite;
    RigidBody rb;

    float move_speed;
private:
    sf::Texture texture;

    double currentFrame;

    void processAnimation();
};