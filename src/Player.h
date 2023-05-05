#include "Entity.h"

using namespace sf;

/// <summary>
/// ����� ������
/// </summary>
class Player : public Entity {
public:
    sf::Texture _animation_textures[7];
    explicit Player(float jumpHeight);

    void Update(float dt) override;
    void FixedUpdate(float dt) override;

    float move_speed;
private:
    sf::Texture texture;
    double currentFrame;
    float _jumpHeight;


    void processAnimation();
};