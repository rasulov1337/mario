#include "Collider.h"
#include "GameComponent.h"
#include <SFML/Graphics.hpp>



class Entity : public GameComponent {
public:
	explicit Entity(sf::FloatRect rect_, float mass, float moveSpeed);
	
	bool is_on_ground;
	sf::FloatRect rect;

protected:
	Collider _collider;
	float _mass;
	float _moveSpeed;
	sf::Vector2f _velocity;
};