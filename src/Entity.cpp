#include "Entity.h"

std::vector<Entity*> Entity::entities{};

Entity::Entity(sf::FloatRect rect_, float mass, float moveSpeed)
	: rect(rect_), is_on_ground(false), _collider(rect), _mass(mass), _moveSpeed(moveSpeed), dead(false)
{
	Entity::entities.push_back(this);
}

Entity::Entity(const Entity& other) :
	rect(other.rect),
	_mass(other._mass),
	_moveSpeed(other._moveSpeed), 
	is_on_ground(false),
	_collider(rect),
	dead(other.dead)
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

Collider& Entity::collider()
{
	return _collider;
}

void Entity::OnCollision(sf::Vector2f direction)
{
}
