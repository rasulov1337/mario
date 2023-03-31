#include "RigidBody.h"

RigidBody::RigidBody(sf::FloatRect rect_, float mass)
	: rect(rect_), is_on_ground(false), _collider(&rect), mass(mass)
{
}

void RigidBody::FixedUpdate(float dt)
{
	if (!is_on_ground) {
		rect.top += dt * mass * 9.8;
	}
}
