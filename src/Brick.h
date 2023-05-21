#pragma once
#include <SFML/Graphics.hpp>
#include "Collider.h"



class Brick {
public:
	sf::Sprite sprite;
	sf::FloatRect rect;
	Collider collider;

	Brick(sf::Sprite sprite_) : 
		sprite(sprite_),
		rect(0, 0, 0, 0),
		collider(rect) {
		auto spritePosition = sprite.getPosition();
		auto textureRect = sprite.getTextureRect();
		rect = sf::FloatRect(spritePosition.x, spritePosition.y, textureRect.width, textureRect.height);
	}

	Brick(const Brick& other) : 
		sprite(other.sprite),
		rect(0, 0, 0, 0),
		collider(rect) {
		if (this == &other)
			return;
		auto spritePosition = sprite.getPosition();
		auto textureRect = sprite.getTextureRect();
		rect = sf::FloatRect(spritePosition.x, spritePosition.y, textureRect.width, textureRect.height);
	}

	

	void OnPlayerHit() {
		sprite = sf::Sprite();
		rect = {0, 0, 0, 0};
		std::cout << "Brick hit!\n";
	}


	

};