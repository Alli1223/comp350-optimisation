#pragma once
#include "InGameMenu.h"
#include "Player.h"
#include "GameSettings.h"
#include "ToolBar.h"
#include "CraftingUI.h"
class GameUI
{
public:
	//! Consyructor
	GameUI();
	//! Destructor
	~GameUI();
	//! Toolbar object
	ToolBar toolbar;
	InGameMenu gameMenu;

	//Function that renders all the UI elements
	void Render(SDL_Renderer* renderer, Player& player, GameSettings& gameSettings);

};

