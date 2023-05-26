#include "Collider.h"

std::vector<Collider*> Collider::colliders{};


Collider::Collider(sf::FloatRect& rect)
	: rect(rect), disabled(false)
{
	Collider::colliders.push_back(this);
}

Collider::Collider(const Collider& other) : rect(other.rect), disabled(other.disabled)
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


bool Collider::CheckCollision(Collider& other, sf::Vector2f& direction, float push)
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
				Move(intersectX * (1.0 - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else {
				Move(-intersectX * (1.0 - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {
			if (dy > 0.0f) {
				Move(0.0f, intersectY * (1.0 - push));
				other.Move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}

	return false;
}

sf::Vector2f Collider::GetHalfSize() const
{
	return rect.getSize() / 2.0f;
}
