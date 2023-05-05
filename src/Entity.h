#ifndef ENTITY_H
#define ENTITY_H

#include "Collider.h"
#include "GameComponent.h"
#include <SFML/Graphics.hpp>



class Entity : public GameComponent {
public:
	explicit Entity(sf::FloatRect rect_, float mass, float moveSpeed);
	explicit Entity(const Entity& other);
	~Entity();

	bool is_on_ground;
	sf::FloatRect rect;
	const Collider& collider();
	sf::Sprite sprite;

	static std::vector<Entity*> entities;

protected:
	Collider _collider;
	float _mass;
	float _moveSpeed;
	sf::Vector2f _velocity;

	sf::Texture _texture;
};

#endif