#include <iostream>
#include <unordered_set>

#include "Player.h"
#include "LevelData.h"
#include "Brick.h"
#include "Coin.h"
#include "StaticCollider.h"
#include "Goomba.h"

class Game {
	sf::Vector2f _windowResolution;
	float _aspectRatio;
	sf::Vector2f _gameResolution;
	sf::RenderWindow _window;
	sf::View _view;
	LevelData _lvl;

	float cameraCenterPos;
	
	void ProcessEvents();
	void Update();
	void ProcessPhysics();
	void Render();

	void LoadLevel(int level);
	void OnDie();

	// Debug
	void InitDebug();
	void DrawColliders();
	std::vector<RectangleShape> _rect_shapes;

	// Game Objects
	std::vector<Brick> _bricks;
	std::vector<Coin> _coins;
	std::vector<StaticCollider> _staticColliders;

	// Entities
	std::vector<Goomba> _goombas;
	
	sf::Music _gameMusic;

public:
	explicit Game();
	int Run();

	Player mario;


};