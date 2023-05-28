#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>

#include "StaticCollider.h"

#include "ConfigVars.h"

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
		if (!_texture.loadFromFile(COIN_SPRITE_PATH)) {
			std::cerr << "E: Couldn't load coin sprite\n";
		}
		sprite.setTexture(_texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		sprite.setPosition(rect.getPosition());
	}

	explicit Coin(const Coin& other):
		collider(other.collider),
		_texture(other._texture),
		sprite(other.sprite),
		timeElapsed(other.timeElapsed),
		_wasHit(other._wasHit)
	{
		sprite.setTexture(_texture);
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

		if (!_wasHit) {
			int frameIndex = timeElapsed / oneFrameLength;

			sprite.setTextureRect(sf::IntRect(frameIndex * 14, 0, 14, 14));
			sprite.setScale(1.142857142857143, 1.142857142857143);

			timeElapsed += dt;
			if (timeElapsed >= 2) {
				timeElapsed = 0;
			}
		}

	}

	void OnPlayerHit() {
		if (_wasHit)
			return;
#ifdef _DEBUG
		std::cout << "Coin hit!\n";
#endif
		_wasHit = true;
		sprite.setTextureRect(sf::IntRect(3 * 14, 0, 14, 14));
	}

private:
	bool _wasHit;
	float timeElapsed;
	sf::Texture _texture;
};

#endif // !COIN_H
