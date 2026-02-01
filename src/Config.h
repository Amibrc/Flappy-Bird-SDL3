#pragma once

constexpr unsigned short WINDOW_WIDTH = 576;
constexpr unsigned short WINDOW_HEIGHT = 768;

constexpr float WINDOW_CENTER_X = WINDOW_WIDTH / 2.0f;
constexpr float WINDOW_CENTER_Y = WINDOW_HEIGHT / 2.0f;

constexpr unsigned int FPS = 0;
constexpr unsigned int DELAY_MS = (FPS == 0) ? 0 : 1000 / FPS;

constexpr float GRAVITY = 3400.0f;

constexpr float TOP_GROUND_Y = 0.0f;
constexpr float BOTTOM_GROUND_Y = WINDOW_HEIGHT - WINDOW_HEIGHT / 10.0f;

constexpr float GROUND_MOVE_SPEED = 300.0f;
constexpr float BACKGROUND_MOVE_SPEED = 30.0f;

constexpr float PIPE_MOVE_SPEED = 300.0f;
constexpr float PIPE_PAIR_GAP = 200.0f;
constexpr float PIPE_PAIRS_DISTANCE = 250.0f;
constexpr float PIPE_PAIRS_START_X = WINDOW_WIDTH + 200.0f;
constexpr float PIPE_MIN_Y = TOP_GROUND_Y + 100.0f;
constexpr float PIPE_MAX_Y = BOTTOM_GROUND_Y - PIPE_PAIR_GAP - PIPE_MIN_Y;
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

constexpr const char* ICON_FILE = "assets/icon.png";

constexpr const char* GAME_OVER_BANNER_FILE = "assets/game-over-banner.png";
constexpr const char* GET_READY_BANNER_FILE = "assets/get-ready-banner.png";
constexpr const char* START_BANNER_FILE = "assets/start-banner.png";
constexpr const char* STATS_BANNER_FILE = "assets/stats-banner.png";
constexpr const char* NEW_BANNER_FILE = "assets/new-banner.png";
constexpr const char* FLAPPY_BIRD_BANNER_FILE = "assets/flappy-bird-banner.png";

constexpr const char* OK_BUTTON_FILE = "assets/ok-button.png";
constexpr const char* START_BUTTON_FILE = "assets/start-button.png";
constexpr const char* MENU_BUTTON_FILE = "assets/menu-button.png";

constexpr const char* BACKGROUND_DAY_FILE = "assets/background-day.png";
constexpr const char* BACKGROUND_NIGHT_FILE = "assets/background-night.png";

constexpr const char* PIPE_GREEN_FILE = "assets/pipe-green.png";
constexpr const char* PIPE_BROWN_FILE = "assets/pipe-brown.png";

constexpr const char* GROUND_FILE = "assets/ground.png";

constexpr const char* PAUSE_BUTTON_FILES[] =
{
	"assets/pause-button.png",
	"assets/resume-button.png"
};

constexpr const char* BIRD_YELLOW_FILES[] =
{
	"assets/bird-yellow-001.png",
	"assets/bird-yellow-002.png",
	"assets/bird-yellow-003.png",
};

constexpr const char* BIRD_RED_FILES[] =
{
	"assets/bird-red-001.png",
	"assets/bird-red-002.png",
	"assets/bird-red-003.png"
};

constexpr const char* BIRD_BLUE_FILES[] =
{
	"assets/bird-blue-001.png",
	"assets/bird-blue-002.png",
	"assets/bird-blue-003.png",
};

constexpr const char* MEDAL_FILES[] =
{
	"assets/medal-bronze.png",
	"assets/medal-silver.png",
	"assets/medal-platinum.png",
	"assets/medal-gold.png"
};

constexpr const char* PARTICLE_FILES[] =
{
	"assets/particle-001.png",
	"assets/particle-002.png",
	"assets/particle-003.png"
};