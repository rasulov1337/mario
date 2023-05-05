#include "Entity.h"

using namespace sf;

/// <summary>
/// Класс игрока
/// </summary>
class Player : public Entity {
public:
    explicit Player(float jumpHeight);

    void Update(float dt) override;
    void FixedUpdate(float dt) override;

    float move_speed;
private:
    double currentFrame;
    float _jumpHeight;


    void processAnimation();
};