#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

#include "StaticCollider.h"


class Coin {
	friend class Game;
public:
	sf::Sprite sprite;
	StaticCollider collider;

	explicit Coin(sf::Sprite sprite_, sf::FloatRect rect) : sprite(sprite_), collider(rect), _wasHit(false) {

	}

	void OnPlayerHit() {
		if (_wasHit)
			return;

		std::cout << "Coin hit!\n";
		_wasHit = true;
		collider.disabled = true;
	}

private:
	bool _wasHit;
};

#endif // !COIN_H
