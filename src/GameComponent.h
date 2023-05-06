#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include <vector>

/// <summary>
/// Один из базовых классов игры. Просто описывает любой компонент игры. Используется для упрощения вызова методов Update() и FixedUpdate().
/// </summary>
class GameComponent {
public:
	GameComponent();
	~GameComponent();

	virtual void Update(float) {}

	static std::vector<GameComponent*> components_array;
};

#endif