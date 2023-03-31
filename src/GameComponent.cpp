#include "GameComponent.h"

std::vector<GameComponent*> GameComponent::components_array{};

GameComponent::GameComponent() {
	GameComponent::components_array.push_back(this);
}