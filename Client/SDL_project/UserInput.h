#pragma once
#include "Level.h"
#include "Camera.h"
#include "Player.h"
#include "ToolBar.h"
#include "InventoryUI.h"
#include "Timer.h"
#include "GameUI.h"
class UserInput
{
public:
	UserInput();
	~UserInput();

	Inventory craftingInventory;
	void UserInput::UseItemFromToolbar(int xPos, int yPos, ToolBar& toolbar, Player& player, Level& level, GameSettings& gameSettings, SDL_Renderer* renderer);

	void UserInput::HandleUserInput(SDL_Renderer* renderer, Level& level, Player& player, Camera& camera, GameSettings& gameSettings, ToolBar& toolbar, GameUI& UI);

	bool UserInput::CheckIfCellIsWalkable(Level& level, int x, int y);

	void ChangeCellsAroundPoint(Level& level, glm::vec2 point, int dist, std::string type);
private:
	Timer inventoryTimer;
	Timer craftingTimer;
	//! Timeout in milliseconds
	float inventoryTimeout = 500;
	float craftingTimeout = 500;
	glm::vec2 playerChunkPos;
	glm::vec2 playercellPos;
	glm::vec2 InterDir;

	SDL_Joystick *joystick;
};

