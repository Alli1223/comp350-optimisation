#include "stdafx.h"
#include "InGameMenu.h"


InGameMenu::InGameMenu() : background("Resources\\UI\\Background.png"), Exit("Exit"), Save("Save"), Fullscreen("FullScreen"), Windowed("Windowed"), MainMenu("Main Menu")
{
	timeout.start();
}


InGameMenu::~InGameMenu()
{
}



void InGameMenu::render(SDL_Renderer* renderer, GameSettings& gameSettings)
{
	
	background.alterTransparency(200);
	background.alterTextureColour(200, 100, 50);
	background.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);
	Exit.render(renderer, gameSettings.WINDOW_WIDTH / 2 - buttonSize, gameSettings.WINDOW_HEIGHT / 2, buttonSize, buttonSize);
	Save.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, buttonSize, buttonSize);
	Fullscreen.render(renderer, gameSettings.WINDOW_WIDTH / 2 + buttonSize * 2, gameSettings.WINDOW_HEIGHT / 2 - (buttonSize / 2), buttonSize * 2, buttonSize);
	//Windowed.render(renderer, gameSettings.WINDOW_WIDTH / 2 + buttonSize * 2, gameSettings.WINDOW_HEIGHT / 2 + (buttonSize / 2), buttonSize * 2, buttonSize);
	MainMenu.render(renderer, gameSettings.WINDOW_WIDTH / 2 + buttonSize * 2, gameSettings.WINDOW_HEIGHT / 2 + (buttonSize / 2), buttonSize * 2, buttonSize);
	if (Exit.isPressed())
	{
		gameSettings.saveLevelOnExit = false;
		gameSettings.running = false;
	}
	if (Save.isPressed())
	{
		gameSettings.saveLevelOnExit = true;
		gameSettings.running = false;
	}

	if (Fullscreen.isPressed())
		gameSettings.fullscreen = true;
	if (MainMenu.isPressed())
	{
		gameSettings.gotoMainMenu = true;
		gameSettings.running = false;
	}
		
		
	

}