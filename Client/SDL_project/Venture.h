#pragma once
#include "Texture.h"
#include "Level.h"
#include "Map.h"
#include "Point.h"
#include "Cell.h"
#include "PathFinder.h"
#include "GameSettings.h"
#include "GUI.h"
#include "ToolBar.h"
#include "Items.h"
#include "CellRendering.h"
#include "PerlinNoise.h"
#include "ProceduralTerrain.h"
#include "Camera.h"
#include "Inventory.h"
#include "UserInput.h"
#include "Player.h"
#include "TextUI.h"
#include "Menu.h"
#include "InventoryUI.h"
#include "CraftingUI.h"
#include "GameUI.h"


//! The main class
/*!
This is the main class where the game is laoded and run. 
*/
class Venture
{
public:
	//! A constructor
	Venture();
	//! A deconstructor
	~Venture();

	//! Main Run loop
	void run();

	//! Initalising all classes needed for game
	Level level;
	GameSettings gameSettings;
	Map mapLoader;
	Cell cell;
	CellRendering cellrenderer;
	ProceduralTerrain terrainGen;
	Camera camera;
	UserInput input;
	Player player;
	GameUI UI;
	
	
	bool needsRestart = false;
	

	//! Vector of all other players names in the game
	std::vector<std::string> otherPlayerNames;

	//! Coordinates of the mouse 
	int mouseX, mouseY;

	glm::vec2 mouseCellPosition;
private:

	//! start point and end point for pathfinding
	Point startPoint, endPoint;

	//! Pointer to the window that the game will be rendered in
	SDL_Window* window;
	//" Pointer to the renderer
	SDL_Renderer* renderer;

	SDL_GLContext glContext;

	Texture backgroundTexture;
	Texture mousePointer;

	std::vector<std::shared_ptr<Player>> allPlayers;
	

	//! Some colours for text output
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Black = { 0, 0, 0 };

	
};

