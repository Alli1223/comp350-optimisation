#include "stdafx.h"
#include "GameUI.h"


GameUI::GameUI()
{
	
}


GameUI::~GameUI()
{
}


void GameUI::Render(SDL_Renderer* renderer, Player& player, GameSettings& gameSettings)
{
	// Renders inventory
	player.InventoryPanel.RenderInventory(renderer, player.inventory);

	// Render toolbar
	toolbar.UpdateAndRenderToolbar(renderer, player, gameSettings);

	// Render Crafting
	player.craftingUI.renderCraftingMenu(renderer, player.inventory);

	// Render game menu
	if (gameSettings.inGameMenu)
	{
		gameMenu.render(renderer, gameSettings);
	}
}