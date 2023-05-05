#ifndef COLLIDER_H
#define COLLIDER_H

#include <SFML/Graphics/Rect.hpp>
#include <vector>


/// <summary>
/// ����� ����������. ������������ ��� ������ ����������� �������� (������ ����).
/// </summary>
class Collider {
public:
	Collider(const sf::FloatRect& rect);
	Collider(const Collider& other);
	~Collider();

	bool operator==(const Collider& other);


	sf::Vector2f CheckCollision(const Collider& other) const;
	sf::Vector2f GetHalfSize() const;
	
	const sf::FloatRect& rect;
	
	static std::vector<Collider*> colliders;
};

#endif