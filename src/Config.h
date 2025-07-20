#pragma once

constexpr unsigned short WINDOW_WIDTH = 576;
constexpr unsigned short WINDOW_HEIGHT = 768;

constexpr float WINDOW_CENTER_X = WINDOW_WIDTH / 2.0f;
constexpr float WINDOW_CENTER_Y = WINDOW_HEIGHT / 2.0f;

constexpr unsigned int FPS = 120;
constexpr unsigned int DELAY_MS = (FPS == 0) ? 0 : 1000 / FPS;

constexpr float GRAVITY = 3400.0f;

constexpr float GROUND_Y = WINDOW_HEIGHT - WINDOW_HEIGHT / 10.0f;
constexpr float GROUND_MOVE_SPEED = 300.0f;
constexpr float BACKGROUND_MOVE_SPEED = 30.0f;

constexpr float PIPE_MOVE_SPEED = 300.0f;
constexpr float PIPE_PAIR_GAP = 200.0f;
constexpr float PIPE_PAIRS_DISTANCE = 250.0f;
constexpr float PIPE_PAIRS_START_X = WINDOW_WIDTH + 200.0f;
constexpr float PIPE_MIN_Y = 100.0f;
constexpr float PIPE_MAX_Y = GROUND_Y - PIPE_PAIR_GAP - PIPE_MIN_Y;
constexpr unsigned short PIPE_PAIRS_COUNT = 3;

constexpr float BIRD_FLAP_FORCE = 780.0f;
constexpr float BIRD_MIN_ANGLE = -20.0f;
constexpr float BIRD_MAX_ANGLE = 90.0f;
constexpr float BIRD_ROTATING_SPEED = 300.0f;
constexpr float BIRD_COUNTER = 6.0f;

constexpr int SCORE_MEDAL_BRONZE = 10;
constexpr int SCORE_MEDAL_SILVER = 15;
constexpr int SCORE_MEDAL_PLATINUM = 20;
constexpr int SCORE_MEDAL_GOLD = 25;

constexpr const char* iconFile = "assets/icon.png";

constexpr const char* gameOverBannerFile = "assets/gameOverBanner.png";
constexpr const char* getReadyBannerFile = "assets/getReadyBanner.png";
constexpr const char* startBannerFile = "assets/startBanner.png";
constexpr const char* statsBannerFile = "assets/statsBanner.png";

constexpr const char* backgroundDayFile = "assets/backgroundDay.png";
constexpr const char* backgroundNightFile = "assets/backgroundNight.png";

constexpr const char* pipeGreenFile = "assets/pipeGreen.png";
constexpr const char* pipeBrownFile = "assets/pipeBrown.png";

constexpr const char* groundFile = "assets/ground.png";

constexpr const char* scoreFontFile = "assets/FlappyBirdRegular-9Pq0.ttf";

constexpr const char* birdYellowFiles[] =
{
	"assets/birdYellow001.png",
	"assets/birdYellow002.png",
	"assets/birdYellow003.png"
};

constexpr const char* birdRedFiles[] =
{
	"assets/birdRed001.png",
	"assets/birdRed002.png",
	"assets/birdRed003.png"
};

constexpr const char* birdBlueFiles[] =
{
	"assets/birdBlue001.png",
	"assets/birdBlue002.png",
	"assets/birdBlue003.png"
};

constexpr const char* medalFiles[] =
{
	"assets/medalBronze.png",
	"assets/medalSilver.png",
	"assets/medalPlatinum.png",
	"assets/medalGold.png"
};