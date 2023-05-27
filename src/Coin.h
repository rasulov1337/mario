#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

#include "StaticCollider.h"


class Coin {
	friend class Game;
public:
	sf::Sprite sprite;
	StaticCollider collider;
	explicit Coin() = delete;

	explicit Coin(sf::FloatRect rect) :
		collider(rect),
		_wasHit(false),
		timeElapsed(0)
	{
		_texture = new Texture;
		if (!_texture->loadFromFile("assets/coin.png")) {
			std::cout << "E: Couldn't load coin sprite\n";
		}
		sprite.setTexture(*_texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		sprite.setPosition(rect.getPosition());
	}

	~Coin() {
	}

	void Update(float dt) {
		const float oneFrameLength = 0.4;
		const int numberOfFrames = 3;

		timeElapsed += dt;
		if (timeElapsed >= oneFrameLength * numberOfFrames) {
			timeElapsed = 0;
		}

		int frameIndex = timeElapsed / oneFrameLength;
		
		sprite.setTextureRect(sf::IntRect(frameIndex * 14, 0, 14, 14));
		sprite.setScale(1.142857142857143, 1.142857142857143);

		timeElapsed += dt;
		if (timeElapsed >= 2) {
			timeElapsed = 0;
		}

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
	float timeElapsed;
	sf::Texture* _texture;
};

#endif // !COIN_H
