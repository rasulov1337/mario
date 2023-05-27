#include "Entity.h"

using namespace sf;


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

    bool _faceRight;

    void ProcessAnimation();
};