#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <vector>


/// <summary>
/// Класс коллайдера. Используется для поиска пересечений объектов (физика игры).
/// </summary>
class Collider {
public:
	Collider(sf::FloatRect& rect);
	Collider(const Collider& other);
	~Collider();

	void Move(float dx, float dy) {
		rect.left += dx;
		rect.top += dy;
	}

	bool operator==(const Collider& other);


	//sf::Vector2f CheckCollision(const Collider& other) const;
	sf::Vector2f GetHalfSize() const;
	bool CheckCollision(Collider& other, sf::Vector2f& direction, float push);
	
	sf::FloatRect& rect;
	
	static std::vector<Collider*> colliders;

	bool disabled;
};

#endif