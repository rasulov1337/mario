#include <SFML/Graphics/Rect.hpp>
#include <vector>


/// <summary>
/// Класс коллайдера. Используется для поиска пересечений объектов (физика игры).
/// </summary>
class Collider {
public:
	Collider(const sf::FloatRect* rect);
	~Collider();

	static std::vector<Collider*> colliders;
	
	const sf::FloatRect* rect;
};