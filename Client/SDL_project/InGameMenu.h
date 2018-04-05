#pragma once
#include "GUI.h"
#include "Button.h"
#include "GameSettings.h"
class InGameMenu : public GUI
{
public:
	//! Constructor
	InGameMenu();
	//! Destructor
	~InGameMenu();

	Button Exit;
	Button Save;
	Button Fullscreen;
	Button Windowed;
	Button MainMenu;

	Texture background;

	int buttonSize = 100;
	Timer timeout;

	bool isOpen;

	const std::string backgroundTextureLocation = "Resources\\Sprites\\Menu\\";
	const std::string buttonsTextureLocation = "Resources\\UI\\";
	//! Render the overlay menu
	void render(SDL_Renderer* renderer, GameSettings& gameSettings);
};

