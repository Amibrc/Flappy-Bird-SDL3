#pragma once

constexpr unsigned short WINDOW_WIDTH = 576;
constexpr unsigned short WINDOW_HEIGHT = 768;

constexpr float WINDOW_CENTER_X = WINDOW_WIDTH / 2.0f;
constexpr float WINDOW_CENTER_Y = WINDOW_HEIGHT / 2.0f;
constexpr float GROUND_Y = WINDOW_HEIGHT - WINDOW_HEIGHT / 10.0f;

constexpr unsigned int FPS = 60;
constexpr unsigned int DELAY_MS = 1000 / FPS;

constexpr float GRAVITY = 2.0f;

constexpr float PIPE_MOVE_SPEED = 5.0f;
constexpr float PIPE_PAIR_GAP = 200.0f;
constexpr float PIPE_PAIRS_DISTANCE = 250.0f;
constexpr float PIPE_PAIRS_START_X = WINDOW_WIDTH + 200.0f;
constexpr float PIPE_MIN_Y = 100.0f;
constexpr float PIPE_MAX_Y = GROUND_Y - PIPE_PAIR_GAP - PIPE_MIN_Y;
constexpr unsigned short PIPE_PAIRS_COUNT = 3;

constexpr float BIRD_FLAP_FORCE = 20.0f;
constexpr float GROUND_MOVE_SPEED = 5.0f;

constexpr const char* iconTextureFile = "assets/icon.png";

constexpr const char* gameOverBannerTextureFile = "assets/gameOverBanner.png";
constexpr const char* getReadyBannerTextureFile = "assets/getReadyBanner.png";

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