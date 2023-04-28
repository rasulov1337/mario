#include <vector>

/// <summary>
/// Один из базовых классов игры. Просто описывает любой компонент игры. Используется для упрощения вызова методов Update() и FixedUpdate().
/// </summary>
class GameComponent {
public:
	GameComponent();
	virtual void Update(float) {}
	virtual void FixedUpdate(float) {}

	static std::vector<GameComponent*> components_array;
};

