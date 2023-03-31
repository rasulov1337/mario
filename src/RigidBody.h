#include "Collider.h"
#include "GameComponent.h"


/// <summary>
/// Класс тела, которое может двигаться и иметь коллизии.
/// </summary>
class RigidBody : public GameComponent {
public:
	explicit RigidBody(sf::FloatRect rect_, float mass);

	void FixedUpdate(float dt);

	float mass;

	bool is_on_ground;

	sf::FloatRect rect;
	
private:
	Collider _collider;
	
};