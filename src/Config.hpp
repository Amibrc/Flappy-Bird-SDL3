#pragma once

constexpr unsigned short WINDOW_WIDTH = 576;
constexpr unsigned short WINDOW_HEIGHT = 768;

constexpr unsigned short WINDOW_CENTER_X = WINDOW_WIDTH / 2;
constexpr unsigned short WINDOW_CENTER_Y = WINDOW_HEIGHT / 2;

constexpr unsigned short GROUND_Y = WINDOW_HEIGHT - WINDOW_HEIGHT / 10;

constexpr float GRAVITY = 2;
constexpr float PIPE_MOVE_SPEED = 5;
constexpr float PIPE_PAIR_GAP = 200;
constexpr float PIPE_PAIRS_DISTANCE = 350;
constexpr float PIPE_PAIRS_START_X = WINDOW_WIDTH + 200;
constexpr float BIRD_FLAP_FORCE = 20;

constexpr float GROUND_MOVE_SPEED = 5;

constexpr const char* iconTextureFile = "assets/icon.png";
constexpr const char* gameOverBannerTextureFile = "assets/gameOverBanner.png";

constexpr const char* backgroundDayTextureFile = "assets/backgroundDay.png";
constexpr const char* backgroundNightTextureFile = "assets/backgroundNight.png";

constexpr const char* pipeGreenTextureFile = "assets/pipeGreen.png";
constexpr const char* pipeBrownTextureFile = "assets/pipeBrown.png";

constexpr const char* grassTextureFile = "assets/grass.png";

constexpr const char* birdYellowTextureFiles[] =
{
	"assets/birdYellow001.png",
	"assets/birdYellow002.png",
	"assets/birdYellow003.png"
};

constexpr const char* birdRedTextureFiles[] =
{
	"assets/birdRed001.png",
	"assets/birdRed002.png",
	"assets/birdRed003.png"
};

constexpr const char* birdBlueTextureFiles[] =
{
	"assets/birdBlue001.png",
	"assets/birdBlue002.png",
	"assets/birdBlue003.png"
};