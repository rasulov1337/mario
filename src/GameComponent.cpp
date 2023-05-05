#include "GameComponent.h"

std::vector<GameComponent*> GameComponent::components_array{};

GameComponent::GameComponent() {
	GameComponent::components_array.push_back(this);
}

GameComponent::~GameComponent() {
	for (auto i = GameComponent::components_array.begin(); i != GameComponent::components_array.end(); ++i) {
		if (*i == this) {
			GameComponent::components_array.erase(i);
			break;
		}
	}
}