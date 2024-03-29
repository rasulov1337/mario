#include "Game.h"
#include <sstream>
#include <iomanip>

Game::Game() :
	_windowResolution(1300, 600),
	_aspectRatio(_windowResolution.x / _windowResolution.y),
	_gameResolution(_aspectRatio * 208, 208),
	_window(sf::VideoMode(_windowResolution.x, _windowResolution.y), GAME_TITLE),
	mario(100.0f),
	_view(sf::FloatRect(0.0f, 0.0f, _gameResolution.x, _gameResolution.y)),
	_gameOver(false),
	_score(0),
	_timeLeft(300)
{
	LoadLevel(0);

	cameraCenterPos = _gameResolution.x / 2;
	_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

	if (!_gameMusic.openFromFile(GAME_MUSIC_PATH))
		std::cerr << "ERROR: MAIN THEME MUSIC FILE IS NOT LOADED!";
	_gameMusic.setVolume(50);
	_gameMusic.play();
	_gameMusic.setLoop(true);

	if (!_font.loadFromFile(FONT_PATH))
	{
		std::cerr << "ERROR: MARIO FONT FILE WASN'T LOADED!";
	}
	const_cast<sf::Texture&>(_font.getTexture(12)).setSmooth(false);
	_text.setFont(_font);

	std::string s = GAME_TITLE + "\tScore\tTime\nBETA\t\t\t\t 00000\t 000";
	_text.setString(s);
	_text.setCharacterSize(12);

	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);


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
	_timeLeft -= dt;

	if (_timeLeft <= 0)
		OnDie();

	if (dt > (1.0f / 60.0f)) {
		dt = 1.0f / 60.0f;
	}


	for (auto& i : GameComponent::components_array) {
		if (!i->__delete)
			i->Update(dt);
	}

	for (auto& i : _coins) {
		i.Update(dt);
	}
}

void Game::ProcessPhysics()
{
	auto& c = Collider::colliders;  // Just an alias
	auto& e = Entity::entities;

	for (auto k = _goombas.begin(); k != _goombas.end(); ++k) {
		if (k->__delete) {
			continue;
		}
		sf::Vector2f direction;
		k->collider().CheckCollision(mario.collider(), direction, 1.0f);
		if (!direction.x && !direction.y)
			continue;
		if (direction.y < 0) {
			_score += 50;
			k->Die();
			break;
		}
		else if (direction.x != 0 && direction.y == 0) {
			OnDie();
			break;
		}
	}

	for (int i = 0; i < c.size(); ++i) {
		for (int j = 0; j < e.size(); ++j) {
			if (c[i]->disabled || c[i] == &e[j]->collider())
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
						AudioManager::Play(BRICK_HITSOUND_NAME);
						_score += 50;
						j->OnPlayerHit();
					}
				}

				for (auto j = _coins.begin(); j != _coins.end(); ++j) {
					if (&j->collider == c[i] && !j->_wasHit) {
						AudioManager::Play(COIN_HITSOUND_NAME);
						_score += 200;
						j->OnPlayerHit();
					}
				}
			}
		}
	}

	
	

	mario.rect.left = std::clamp(mario.rect.left, cameraCenterPos - _gameResolution.x / 2, static_cast<float>(_lvl.GetMapWidth()) - mario.rect.width);

	if (mario.rect.top >= _lvl.GetMapHeight() && !_gameOver) {
		OnDie();
		_gameOver = true;
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

	if (_gameOver)
	{
		sf::FloatRect textRect = _text.getLocalBounds();
		_window.clear(sf::Color(0, 0, 0));
		_text.setString("GAME OVER");
		_text.setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);
		_text.setPosition(sf::Vector2f(cameraCenterPos, _gameResolution.y / 2));
		_text.setCharacterSize(12);
		_window.draw(_text);
		_window.display();
		return;
	}

	_lvl.Draw(_window);

	for (auto& i : _bricks) {
		_window.draw(i.sprite);
	}

	// Entities
	for (auto& i : Entity::entities) {
		_window.draw(i->sprite);
	}

	for (auto& i : _coins) {
		_window.draw(i.sprite);
	}

#ifdef _DEBUG
	DrawColliders();
#endif

	std::stringstream ss;
	ss << std::setfill('0') << std::setw(4) << _score;
	std::string s = GAME_TITLE + "\tScore\tTime\nBETA\t\t\t\t " + ss.str() + "\t " + std::to_string(int(_timeLeft));
	_text.setString(s);
	_text.setCharacterSize(12);

	sf::FloatRect textRect = _text.getLocalBounds();

	_text.setPosition(sf::Vector2f(cameraCenterPos, textRect.height / 2 + 1));
	_window.draw(_text);

	_window.display();
}

void Game::LoadLevel(int level)
{
	_lvl.LoadFromFile(MAP_PATH + std::to_string(level) + ".tmx");

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
	for (auto& i : coinObjects) {
		_coins.push_back(Coin(i.rect));
	}


	// Entities...
	auto goombasObjects = _lvl.GetObjects("Goombas");
	for (auto& i : goombasObjects) {
		_goombas.push_back(Goomba(i.rect.getPosition()));
	}
}

void Game::OnDie()
{
	if (_gameOver)
		return;
	_gameOver = true;
	_gameMusic.stop();
	AudioManager::Play(MARIO_DEATH_SOUND_NAME);
}
