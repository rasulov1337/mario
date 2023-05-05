#include <vector>

/// <summary>
/// ���� �� ������� ������� ����. ������ ��������� ����� ��������� ����. ������������ ��� ��������� ������ ������� Update() � FixedUpdate().
/// </summary>
class GameComponent {
public:
	GameComponent();
	virtual void Update(float) {}
	virtual void FixedUpdate(float) {}

	static std::vector<GameComponent*> components_array;
};

