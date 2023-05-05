#include "Collider.h"

std::vector<Collider*> Collider::colliders{};


Collider::Collider(const sf::FloatRect& rect)
	: rect(rect)
{
	Collider::colliders.push_back(this);
}

Collider::Collider(const Collider& other) : rect(other.rect)
{
	if (this == &other)
		return;
	Collider::colliders.push_back(this);
}


Collider::~Collider() {
	for (auto i = Collider::colliders.begin(); i != Collider::colliders.end(); ++i) {
		if (*i == this) {
			Collider::colliders.erase(i);
			break;
		}
	}
}

bool Collider::operator==(const Collider& other)
{
	return (rect == other.rect);
}


sf::Vector2f Collider::CheckCollision(const Collider& other) const
{
	sf::Vector2f other_position = other.rect.getPosition() + other.rect.getSize() / 2.0f;
	sf::Vector2f other_half_size = other.GetHalfSize();


	sf::Vector2f position = rect.getPosition() + rect.getSize() / 2.0f;
	sf::Vector2f half_size = GetHalfSize();

	float dx = other_position.x - position.x;
	float dy = other_position.y - position.y;

	float intersectX = abs(dx) - (other_half_size.x + half_size.x);
	float intersectY = abs(dy) - (other_half_size.y + half_size.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
		if (intersectX > intersectY) {
			if (dx > 0.0f) {
				return { intersectX, 0.0f };
			}
			else {
				return { -intersectX, 0.0f };
			}
		}
		else {
			if (dy > 0.0f) {
				return { 0.0f, intersectY };
			}
			else {
				return { 0.0f, -intersectY };
			}
		}

	}

	return { 0, 0 };
}

sf::Vector2f Collider::GetHalfSize() const
{
	return rect.getSize() / 2.0f;
}
