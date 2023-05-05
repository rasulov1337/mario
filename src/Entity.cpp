#include "Entity.h"

std::vector<Entity*> Entity::entities{};

Entity::Entity(sf::FloatRect rect_, float mass, float moveSpeed)
	: rect(rect_), is_on_ground(false), _collider(rect), _mass(mass), _moveSpeed(moveSpeed)
{
	Entity::entities.push_back(this);
}

Entity::Entity(const Entity& other) :
	rect(other.rect),
	_mass(other._mass),
	_moveSpeed(other._moveSpeed), 
	is_on_ground(false),
	_collider(rect)
{
	Entity::entities.push_back(this);
}

Entity::~Entity() {
	for (auto i = Entity::entities.begin(); i != Entity::entities.end(); ++i) {
		if (*i == this) {
			Entity::entities.erase(i);
			break;
		}
	}
}

const Collider& Entity::collider()
{
	return _collider;
}
