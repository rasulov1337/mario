#include <SFML/Graphics/Rect.hpp>
#include <vector>


/// <summary>
/// Класс коллайдера. Используется для поиска пересечений объектов (физика игры).
/// </summary>
class Collider {
public:
	Collider(const sf::FloatRect* rect);
	~Collider();

	sf::Vector2f CheckCollision(const Collider& other) const;
	sf::Vector2f GetHalfSize() const;
	
	const sf::FloatRect* rect;
	
	static std::vector<Collider*> colliders;
};