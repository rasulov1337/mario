#include "Collider.h"

std::vector<Collider*> Collider::colliders{};

Collider::Collider(const sf::FloatRect* rect)
	: rect(rect)
{
	Collider::colliders.push_back(this);
}


Collider::~Collider() {
	//for (auto &i = Collider::colliders.begin(); i != Collider::colliders.end(); ++i)
	//	if (*i == this)
	//		Collider::colliders.erase(i);

}