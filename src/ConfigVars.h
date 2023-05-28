#ifndef CONFIG_H
#define CONFIG_H

#include <string>

const std::string ASSETS_PATH = "assets/";
const std::string SOUNDS_PATH = "assets/sounds/";
const std::string MAP_PATH = "assets/";
const std::string SPRITES_PATH = "assets/";

// Sprites path
const std::string GOOMBA_SPRITE_PATH = "assets/enemy.png";
const std::string COIN_SPRITE_PATH = "assets/coin.png";

// Sound paths should not have extension at the end
const std::string GOOMBA_DEATH_SOUND_NAME = "goomba_death";
const std::string BRICK_HITSOUND_NAME = "brick";
const std::string COIN_HITSOUND_NAME = "coin";
const std::string MARIO_DEATH_SOUND_NAME = "mario_death";

const std::string GAME_MUSIC_PATH = "assets/music/Main_Theme.wav";
const std::string FONT_PATH = "assets/Mario_font.ttf";

const std::string GAME_TITLE = "Vodoprovodchik";

#undef _DEBUG


#endif // !CONFIG_H
