#include <iostream>
#include <unordered_set>

#include "Player.h"
#include "LevelData.h"
#include "Brick.h"
#include "Coin.h"
#include "StaticCollider.h"
#include "Goomba.h"

#define FIXED_UPDATE_DELTA_TIME 1.0f/60

class Game {
	sf::Vector2f _screen_size;
	sf::RenderWindow _window;
	sf::View _view;
	LevelData _lvl;
	
	void ProcessEvents();
	void Update();
	void ProcessPhysics();
	void Render();

	void LoadLevel(int level);

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
	

public:
	explicit Game();
	int Run();

	Player mario;


};