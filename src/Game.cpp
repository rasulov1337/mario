#include "Game.h"


Game::Game() :
	_screen_size(1200, 600),
	_window(sf::VideoMode(_screen_size.x, _screen_size.y), "Mario Lite"),
	mario(100.0f),
	_view(sf::FloatRect(0.0f, 0.0f, _screen_size.x, _screen_size.y))
{
	LoadLevel(0);

	_view.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

#ifdef _DEBUG
	std::cin.tie(0);
	std::cout.tie(0);
	std::cout.sync_with_stdio(false);
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
		rs.setPosition(i->rect.getPosition());
		rs.setSize(i->rect.getSize());
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
		rs->setPosition((*col)->rect.getPosition());
		rs->setSize((*col)->rect.getSize());
		_window.draw(*rs);
	}
}

void Game::ProcessEvents()
{
	static sf::Event evt;

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
	float dt = clock.restart().asSeconds();
	if (dt > (1.0f / 60.0f)) {
		dt = 1.0f / 60.0f;
	}
	for (auto& i : GameComponent::components_array) {
		i->Update(dt);
	}
}

void Game::ProcessPhysics()
{
	auto& c = Collider::colliders;  // Just an alias
	auto& e = Entity::entities;
	
	for (int i = 0; i < c.size(); ++i) {
			if (c[i] == &mario.collider())
				continue;

			sf::Vector2f direction;
			if (c[i]->CheckCollision(mario.collider(), direction, 1.0f)) {
				mario.OnCollision(direction);
			}
			//sf::Vector2f collisionInfo = c[i]->CheckCollision(mario.collider());
			//sf::Vector2f collisionInfo = mario.collider().CheckCollision(*c[i]);

			if (!direction.x && !direction.y) {
				continue;
			}


			// From Top
			if (direction.y > 0 && direction.x == 0) {
				for (auto j = _bricks.begin(); j != _bricks.end(); ++j) {
					if (&j->collider == c[i]) {
						j->OnPlayerHit();
					}
				}

				for (auto j = _coins.begin(); j != _coins.end(); ++j) {
					if (&j->collider == c[i]) {
						j->OnPlayerHit();
					}
				}

			}

			//std::cout << collisionInfo.x << ' ' << collisionInfo.y << '\n';
		
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

	for (auto& i : _bricks) {
		_window.draw(i.sprite);
	}

	// Entities
	for (auto& i : Entity::entities) {
		_window.draw(i->sprite);
	}

#ifdef _DEBUG
	DrawColliders();
#endif

	_window.display();
}

void Game::LoadLevel(int level)
{
	_lvl.LoadFromFile("assets/map.tmx");
	// HACK: FOR CORRECT PHYSICS FIRST INIT CREATURES THAN GROUND AND OTHERS

	// Далее создаются физические объекты типа Ground, но это надо сделать получше! TODO!
	std::vector<Object> block = _lvl.GetObjects("Ground");
	for (int i = 0; i < block.size(); ++i) {
		_staticColliders.push_back(StaticCollider(block[i].rect));
	}

	auto pipes = _lvl.GetObjects("Pipes");
	for (int i = 0; i < pipes.size(); ++i) {
		_staticColliders.push_back(StaticCollider(pipes[i].rect));
	}

	auto brickObjects = _lvl.GetObjects("Bricks");
	auto brickSprite = _lvl.GetTile(1);
	for (auto& i : brickObjects) {
		brickSprite.setPosition(i.sprite.getPosition());
		_bricks.push_back({ brickSprite });
	}

	auto coinObjects = _lvl.GetObjects("Coins");
	auto coinSprite = sf::Sprite();
	for (auto& i : coinObjects) {
		_coins.push_back(Coin(coinSprite, i.rect));
	}


	// Entities...
	/*auto goombasObjects = _lvl.GetObjects("Goombas");
	for (auto& i : goombasObjects) {
		_goombas.push_back(Goomba(i.rect.getPosition()));
	}*/
}
