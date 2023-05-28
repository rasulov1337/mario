#include "AudioManager.h"

#include "ConfigVars.h"

void AudioManager::Play(std::string filename)
{
	if (_sounds.count(filename)) {
		_sounds[filename].play();
		return;
	}


	sf::SoundBuffer buff;


	if (!buff.loadFromFile(SOUNDS_PATH + filename + ".wav")) {
		std::cerr << "ERROR: " + filename + " FILE CAN'T LOADED!";
		return;
	}

	_buffers[filename] = buff;

	_sounds[filename] = sf::Sound();
	_sounds[filename].setBuffer(_buffers[filename]);

	_sounds[filename].play();
}


std::map<std::string, sf::SoundBuffer> AudioManager::_buffers;
std::map<std::string, sf::Sound> AudioManager::_sounds;