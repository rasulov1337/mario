#include "Game.h"


Game::Game() :
	_windowResolution(1300, 600),
	_aspectRatio(_windowResolution.x / _windowResolution.y),
	_gameResolution(_aspectRatio * 208, 208),
	_window(sf::VideoMode(_windowResolution.x, _windowResolution.y), "Mario Lite"),
	mario(100.0f),
	_view(sf::FloatRect(0.0f, 0.0f, _gameResolution.x, _gameResolution.y))
{
	LoadLevel(0);

	cameraCenterPos = _gameResolution.x / 2;
	_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

	if (!_gameMusic.openFromFile("assets/music/Main_Theme.wav"))
		std::cout << "ERROR: MAIN THEME MUSIC FILE IS NOT LOADED!";
	_gameMusic.setVolume(50);
	_gameMusic.play();
	_gameMusic.setLoop(true);

	if (!_brick_sound_buf.loadFromFile("assets/sounds/brick.wav"))
		std::cout << "ERROR: BRICK SOUND FILE IS NOT LOADED!";
	_brick_sound.setBuffer(_brick_sound_buf);

	if (!_coin_sound_buf.loadFromFile("assets/sounds/coin.wav"))
		std::cout << "ERROR: COIN SOUND FILE IS NOT LOADED!";
	_coin_sound.setBuffer(_coin_sound_buf);

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
	static sf::Event e;

	while (_window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			_window.close();
			break;
		case sf::Event::Resized:
			_windowResolution.x = e.size.width;
			_windowResolution.y = e.size.height;
			_aspectRatio = _windowResolution.x / _windowResolution.y;
			_gameResolution = { _aspectRatio * 208, 208 };
			_view.setSize(sf::Vector2f(_gameResolution.x, _gameResolution.y));
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
		if (!i->__delete)
			i->Update(dt);
	}


}

void Game::ProcessPhysics()
{
	auto& c = Collider::colliders;  // Just an alias
	auto& e = Entity::entities;
	
	for (int i = 0; i < c.size(); ++i) {
		for (int j = 0; j < e.size(); ++j) {
			if (c[i] == &e[j]->collider())
				continue;
			sf::Vector2f direction;
			if (c[i]->CheckCollision(e[j]->collider(), direction, 1.0f)) {
				e[j]->OnCollision(direction);
			}

			if (!direction.x && !direction.y) {
				continue;
			}

			// From Top
			if (direction.y > 0 && direction.x == 0) {
				for (auto j = _bricks.begin(); j != _bricks.end(); ++j) {
					if (&j->collider == c[i]) {
						_brick_sound.play();
						j->OnPlayerHit();
					}
				}

				for (auto j = _coins.begin(); j != _coins.end(); ++j) {
					if (&j->collider == c[i]) {
						_coin_sound.play();
						j->OnPlayerHit();
					}
				}

			}
		}
	}

	mario.rect.left = std::clamp(mario.rect.left, cameraCenterPos - _gameResolution.x / 2, static_cast<float>(_lvl.GetMapWidth()) - mario.rect.width);

	if (mario.rect.top >= _lvl.GetMapHeight()) {
		OnDie();
	}
}

void Game::Render() {
	if (mario.rect.left > cameraCenterPos)
		cameraCenterPos = mario.rect.left;
	if (cameraCenterPos + _gameResolution.x / 2 > _lvl.GetMapWidth())
		cameraCenterPos = _lvl.GetMapWidth() - _gameResolution.x / 2;
	
		
	_view.setCenter(cameraCenterPos, _gameResolution.y / 2);
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
	auto goombasObjects = _lvl.GetObjects("Goombas");
	for (auto& i : goombasObjects) {
		_goombas.push_back(Goomba(i.rect.getPosition()));
	}
}

void Game::OnDie()
{
	// Show die screen
	// Reload
}
