#pragma once
#include "Player.h"
#include "Timer.h"
class GameSettings
{
public:
	GameSettings();
	~GameSettings();


	//! initial window settings
	int WINDOW_WIDTH = 800;
	int WINDOW_HEIGHT = 600;

	//! Save the players settings
	void savePlayerSettings(Player& player);
	Player getPlayerFromSave();
	//! Save the level
	void saveLevelData(Level& level);
	Level loadGameFromSave();
	

	//! Whether the game will save the game when it closes
	bool saveLevelOnExit = true;
	bool savePlayerOnExit = true;

	bool restartGame = false;
	bool saveGame = false;
	//! Get screen resolution
	void getScreenResolution();
	//! Calculate FPS
	void CalculateFramesPerSecond();

	//Timer used to update the caption
	Timer fpsTimer;
	float getAverageFPS() { return avgFPS; }
	static const bool displayFPS = false;


	Uint32 elapsedTime = 0;
	Uint32 lastFrameTimeElapsed = 0;
	float deltaTime = 0;

	//! amount of items in items
	const int amountOfWoodInTrees = 3;
	const int amountOfStoneInRocks = 3;

	//! Time it takes for plants to grow in ms
	UINT32 plantGrowSpeed = 10000;

	//! Whether the game is fullscreen
	bool fullscreen = false;
	bool displayMouse = false;
	int mousePointerSize = 25;


	//! Main Menu toggle
	bool mainMenu = true;
	bool inGameMenu = false;

	bool gotoMainMenu = false;
	//! The cell the mouse is hovering over
	glm::vec2 mouseCellPos;

	//TODO: implement UI scaling
	float UIScale = 1.0;

	//! Whether the game uses networking and false if singleplayer
	bool useNetworking = false;


	//! Whether the game is running or not
	bool running = true;
	//! stores screen resolution
	SDL_DisplayMode currentDisplay;
	
	
private:

	std::ofstream playerSave;
	std::ofstream levelSave;

	std::string levelSavePath = "Resources\\Data\\levelData.txt";
	std::string playerSavePath = "Resources\\Data\\playerData.txt";

	//The frames per second timer
	//Timer used to calculate the frames per second
	int frame = 0;
	//Start counting frames per second
	int countedFrames = 0;
	float avgFPS = 0;

};

