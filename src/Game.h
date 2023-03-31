#include "Player.h"
#include "Level.h"
#include <iostream>

#define FIXED_UPDATE_DELTA_TIME 1.0f/60

class Game {
	sf::Vector2f _screen_size;
	sf::RenderWindow _window;
	sf::View _view;
	Level _lvl;
	
	void ProcessEvents();
	void Update();
	void ProcessPhysics();
	void Render();
public:
	explicit Game();
	int Run();

	Player mario;
};