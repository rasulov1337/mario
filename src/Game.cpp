#include "Game.h"


Game::Game() :
	_screen_size(1200, 600),
	_window(sf::VideoMode(_screen_size.x, _screen_size.y), "Mario Lite"),
	mario(40),
	_view(sf::FloatRect(0.0f, 0.0f, _screen_size.x, _screen_size.y))
{

	_lvl.LoadFromFile("assets/map.tmx");
	// HACK: FOR CORRECT PHYSICS FIRST INIT CREATURES THAN GROUND AND OTHERS

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

#ifdef _DEBUG
	InitDebug();
#endif
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

void Game::InitDebug() {
	for (auto& i : Collider::colliders) {
		sf::RectangleShape rs;
		rs.setPosition(i->rect->getPosition());
		rs.setSize(i->rect->getSize());
		rs.setFillColor(sf::Color(0, 0, 0, 0));
		rs.setOutlineColor(sf::Color(255, 255, 0));
		rs.setOutlineThickness(1);
		_rect_shapes.push_back(rs);
	}
}

void Game::DrawColliders()
{
	auto rs = _rect_shapes.begin();
	auto col = Collider::colliders.begin();
		
	for (; rs != _rect_shapes.end(); ++rs, ++col) {
		rs->setPosition((*col)->rect->getPosition());
		rs->setSize((*col)->rect->getSize());
		_window.draw(*rs);
	}
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

	for (int i = 0; i < c.size(); ++i) {
		for (int j = i + 1; j < c.size(); ++j) {
			bool is_mario = c[i]->rect == &mario.rect;

			if (!is_mario)
				break;

			sf::Vector2f collisionInfo = c[i]->CheckCollision(*c[j]);

			if (!collisionInfo.x && !collisionInfo.y) {
				continue;
			}

			mario.rect.left += collisionInfo.x;
			mario.rect.top += collisionInfo.y;

			if (collisionInfo.y < 0) {
				mario.is_on_ground = true;
			}
		}
	}
}

void Game::Render() {
	float view_left_border = mario.rect.left + _screen_size.x / 4;
	if (mario.rect.left < _screen_size.x / 4)
		view_left_border = _screen_size.x / 2;
	float view_top_border = mario.rect.top + _screen_size.y / 4;
	if (mario.rect.top < _screen_size.y / 4)
		view_top_border = _screen_size.y / 2;
	_view.setCenter(view_left_border, view_top_border);
	_window.setView(_view);

	_window.clear();

	_lvl.Draw(_window);
	_window.draw(mario.sprite);

#ifdef _DEBUG
	DrawColliders();
#endif

	_window.display();
}