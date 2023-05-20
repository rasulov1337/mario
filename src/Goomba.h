#ifndef GOOMBA_H
#define GOOMBA_H

#include "Entity.h"

class Goomba : public Entity {
public:
	explicit Goomba(sf::Vector2f position);

	explicit Goomba(const Goomba& other);

	Goomba& operator=(const Goomba& other);

	void Update(float dt) override;
	void OnCollision(sf::Vector2f direction) override;

	virtual void Die() override;
private:


};

#endif