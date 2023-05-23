#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio.hpp>
#include <map>
#include <iostream>


class AudioManager {
public:
	AudioManager() = delete;

	static void Play(std::string filename);
private:
	static std::map<std::string, sf::SoundBuffer> _buffers;
	static std::map<std::string, sf::Sound> _sounds;

};

#endif