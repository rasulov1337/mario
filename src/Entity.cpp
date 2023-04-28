#include "Entity.h"


Entity::Entity(sf::FloatRect rect_, float mass, float moveSpeed)
	: rect(rect_), is_on_ground(false), _collider(&rect), _mass(mass), _moveSpeed(moveSpeed)
{
}
