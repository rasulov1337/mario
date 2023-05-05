#ifndef STATIC_COLLIDER_H
#define STATIC_COLLIDER_H

#include "Collider.h"

class StaticCollider : public Collider {
public:
	const sf::FloatRect rect;

	explicit StaticCollider(const sf::FloatRect rect_) : rect(rect_), Collider(rect)
	{

	}

	explicit StaticCollider(const StaticCollider& other) : rect(other.rect), Collider(rect) {

	}
};


#endif // !STATIC_COLLIDER_H
