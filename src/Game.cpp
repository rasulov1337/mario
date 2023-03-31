#include "Game.h"
#include "tinyxml2.h"

using namespace tinyxml2;


Game::Game() :
	_screen_size(1200, 600),
	_window(sf::VideoMode(_screen_size.x, _screen_size.y), "Mario Lite"),
	mario(),
	_view(sf::FloatRect(0.0f, 0.0f, _screen_size.x, _screen_size.y)),
	_lvl("assets/map.tmx")
{
	// Далее создаются физические объекты типа Ground, но это надо сделать получше! TODO!
	std::vector<Object> block = _lvl.GetObjects("Ground");
	for (int i = 0; i < block.size(); i++)
	{
		new Collider(new Rect(block[i].rect));
	}


	auto pipes = _lvl.GetObjects("Pipes");
	for (int i = 0; i < pipes.size(); ++i) {
		new Collider(new Rect(pipes[i].rect));
	}
	

	_view.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f, 2.0f));
}


int Game::Run() {
	while (_window.isOpen())
	{
		ProcessEvents();
		Update();
		ProcessPhysics();
		Render();
	}

	return 0;
}

void Game::ProcessEvents()
{
	sf::Event evt;

	while (_window.pollEvent(evt))
	{
		switch (evt.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		}
	}
}

void Game::Update() {
	// Firstly, Update()
	static sf::Clock clock;
	float dt = clock.restart().asMilliseconds();
	for (auto& i : GameComponent::components_array) {
		i->Update(dt);
	}

	// Secondly, FixedUpdate()
	for (auto& i : GameComponent::components_array) {
		i->FixedUpdate(FIXED_UPDATE_DELTA_TIME);
	}
}

void Game::ProcessPhysics()
{
	auto& c = Collider::colliders;  // Just an alias

	for (int i = 0; i < c.size(); ++i)
		for (int j = i + 1; j < c.size(); ++j) {
			
			// If something is ontop of something
			if (((c[i]->rect->top + c[i]->rect->height) >= c[j]->rect->top)
				&& ((c[i]->rect->top + c[i]->rect->height) <= c[j]->rect->top + c[j]->rect->height)
				&& (c[i]->rect->left >= c[j]->rect->left)
				&& ((c[i]->rect->left + c[i]->rect->width) <= (c[j]->rect->left + c[j]->rect->width))) {
				if (c[i]->rect == &mario.rb.rect) {
					mario.rb.is_on_ground = true;
				}
			}

			// If something hits something
			if (((c[i]->rect->left + c[i]->rect->width) >= c[j]->rect->left)
				&& ((c[i]->rect->left + c[i]->rect->width) <= c[j]->rect->left + c[j]->rect->width)
				&& (c[i]->rect->top >= c[j]->rect->top)
				&& ((c[i]->rect->top + c[i]->rect->height) <= (c[j]->rect->top + c[j]->rect->height))) {
				if (c[i]->rect == &mario.rb.rect) {
					mario.rb.rect = sf::FloatRect(c[j]->rect->left - mario.rb.rect.width, mario.rb.rect.top, mario.rb.rect.width, mario.rb.rect.height);
				}
			}
		}
}

void Game::Render() {
	float view_left_border = mario.rb.rect.left + _screen_size.x / 4;
	if (mario.rb.rect.left < _screen_size.x / 4)
		view_left_border = _screen_size.x / 2;
	float view_top_border = mario.rb.rect.top + _screen_size.y / 4;
	if (mario.rb.rect.top < _screen_size.y / 4)
		view_top_border = _screen_size.y / 2;
	_view.setCenter(view_left_border, view_top_border);
	_window.setView(_view);

	_window.clear();

	_lvl.Draw(_window);
	_window.draw(mario.sprite);
	_window.display();
}