#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include <vector>

/// <summary>
/// ���� �� ������� ������� ����. ������ ��������� ����� ��������� ����. ������������ ��� ��������� ������ ������� Update() � FixedUpdate().
/// </summary>
class GameComponent {
public:
	friend class Game;

	GameComponent();
	~GameComponent();

	virtual void Update(float) {}

	static std::vector<GameComponent*> components_array;

protected:
	bool __delete;

};

#endif