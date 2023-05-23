#ifndef GOOMBA_H
#define GOOMBA_H

#include "Entity.h"
#include "AudioManager.h"
#include <iostream>

class Goomba : public Entity {
public:
	explicit Goomba(sf::Vector2f position);

	explicit Goomba(const Goomba& other);

	Goomba& operator=(const Goomba& other);

	void Update(float dt) override;
	void OnCollision(sf::Vector2f direction) override;

	sf::Sound goomba_sound;
	sf::SoundBuffer goomba_death_buf;

	virtual void Die() override;
private:


};

#endif