#include "stdafx.h"
#include "Menu.h"


Menu::Menu() : menuBackground(menuTextures + "Background.png"), cursor(otherTextures + "menuCursor.png")
{
	
}


Menu::~Menu()
{
}
Uint32 get_pixel_at(Uint32 * pixels, int x, int y, int w)
{
	return pixels[y * w + x];
}

std::shared_ptr<Button> get_instance(Button& n)
{
	return std::make_shared<Button>(n);
}


void Menu::MainMenu(GameSettings& gameSettings,Level& level, Camera& camera, Player& player, SDL_Renderer* renderer)
{
	// Create buttons
	Button characterScreen("Character Customisation");
	Button exit("Exit");
	Button useNetworking("Multiplayer");
	Button Fullscreen("FullScreen");
	Button loadFromSave("Load Save Game");
	Button play("New Game");
	auto& justPlay = get_instance(play);
	
	// Scale mouse correctly depending on resolution
	menuCursorSize = gameSettings.WINDOW_WIDTH / 25;
	bodyColourSlider.setColour(player.getBodyColour());
	gameSettings.gotoMainMenu = false;
	gameSettings.inGameMenu = false;
	// Display the menu screen
	while (displayMainMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{

		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayMainMenu = false;
			}
		}
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		menuBackground.alterTransparency(100);
		menuBackground.alterTextureColour(50, 50 ,50);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);
		
		
		int menuY = gameSettings.WINDOW_HEIGHT / 2;
		int menuX = gameSettings.WINDOW_WIDTH / 2;
		int menuSeperationDistance = 75;
		int buttonHeight = 50;
		int buttonWidth = 200;
		// Render buttons
		exit.render(renderer, 50, 25, 100, 50);

		// New Game
		justPlay->render(renderer, menuX, menuY - menuSeperationDistance * 2, buttonWidth, buttonHeight);
		if (justPlay->isPressed())
		{
			displayCharacterMenu = true;
			CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
			//displayMainMenu = false;
		}

		loadFromSave.render(renderer, menuX, menuY - menuSeperationDistance, buttonWidth, buttonHeight);

		// Load from save
		if (loadFromSave.isPressed())
		{
			gameSettings.loadGameFromSave(level);
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}
		
		// Dont save data when exit is pressed
		if (exit.isPressed())
		{
			gameSettings.running = false;
			gameSettings.saveLevelOnExit = false;
			gameSettings.savePlayerOnExit = false;
			displayMainMenu = false;
		}

		// Toggle fullscreen
		Fullscreen.render(renderer, menuX, menuY + menuSeperationDistance, buttonWidth, buttonHeight);
		if (Fullscreen.isPressed())
		{

			// TODO: restart the game in full screen
		}
		// Character Screen
		characterScreen.render(renderer, menuX, menuY + menuSeperationDistance * 2, buttonWidth * 3, buttonHeight * 1.5);
		if (characterScreen.isPressed())
		{
			CharacterCustomisationMenu(gameSettings, camera, player, renderer, level);
			displayCharacterMenu = true;
		}
		//Render the mouse cursor last
		cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}	
}

void Menu::CharacterCustomisationMenu(GameSettings& gameSettings, Camera& camera, Player& player, SDL_Renderer* renderer, Level& level)
{
	Button back("Back");
	Button singlePlayer("Start");
	Button loadSave("Load Save");
	Button rotatePlayer("Rotate");
	// LEFT SIDE (ORGANIC)
	// Gender
	// Skin colour
	// Eye Type
	// Eye Colour

	// Gender
	Button femaleGender("", "FemaleButton");
	Button maleGender("", "MaleButton");
	//Skin Colour
	Button ChangeSkinColourL("", "LButton");
	Button ChangeSkinColourR("", "RButton");
	//Hair
	Button ChangeHairTypeL("", "L_Button");
	Button ChangeHairTypeR("", "R_Button");
	//Eye
	Button ChangeEyeTypeL("", "L_Button");
	Button ChangeEyeTypeR("", "R_Button");
	//Ear
	Button ChangeEarTypeL("", "L_Button");
	Button ChangeEarTypeR("", "R_Button");

	Button ChangeBodyColour("Body Colour");
	Button ChangeEyeColour("Eye Colour");
	Button ChangeHairColour("Hair Colour");

	// Right Side ( CLOTHES)
	// Hair / Hat
	// Tshit/ jacket
	// Trousers
	// Shoes

	Button changeHead("Change Hair");
	Button changeBody("Change Body");
	Button changeLegs("Change Trousers");


	

	Button randomiseAll("Random");
	
	Player playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
	playerCreation.PlayerClothes.body = Player::Clothing::jacket;
	playerCreation.PlayerClothes.head = Player::Clothing::longHair;

	// Load player from file
	playerCreation = gameSettings.getPlayerFromSave();
	playerCreation.setSize(gameSettings.WINDOW_WIDTH / 5);
	playerCreation.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2);
	
	while (displayCharacterMenu)
	{
		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			//getColourWheelvalue(renderer, mouseX, mouseY);
		}
		SDL_Event ev;
		if (SDL_PollEvent(&ev) != 0) {
			if (ev.type == SDL_QUIT) {
				displayCharacterMenu = false;
			}
		}
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		menuBackground.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 2, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);

		/////// Organic customisation buttons //////
		int buttonsX = playerCreation.getX() - playerCreation.getSize();
		int buttonsY = playerCreation.getY() - 200;
		int buttonSize = 100;

		femaleGender.getButtonBackgroundTexture().alterTextureColour(200, 150, 20);
		maleGender.render(renderer, buttonsX, buttonsY, buttonSize, buttonSize);
		femaleGender.render(renderer, buttonsX - 100, buttonsY, buttonSize, buttonSize);

		ChangeHairTypeL.render(renderer, buttonsX - 100, buttonsY + 100, buttonSize, buttonSize);
		ChangeHairTypeR.render(renderer, buttonsX, buttonsY + 100, buttonSize, buttonSize);

		ChangeEyeTypeL.render(renderer, buttonsX - 100, buttonsY +200, buttonSize, buttonSize);
		ChangeEyeTypeR.render(renderer, buttonsX, buttonsY + 200, buttonSize, buttonSize);

		ChangeEarTypeL.render(renderer, buttonsX - 100, buttonsY + 300, buttonSize, buttonSize);
		ChangeEarTypeR.render(renderer, buttonsX, buttonsY + 300, buttonSize, buttonSize);

		ChangeBodyColour.render(renderer, buttonsX - 50, buttonsY + 400, 200, 50);
		ChangeEyeColour.render(renderer, buttonsX - 50, buttonsY + 460, 200, 50);
		ChangeHairColour.render(renderer, buttonsX - 50, buttonsY + 510, 200, 50);
		// Clothes Customisation buttons
		changeHead.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() - 100, 100, 50);
		changeBody.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY(), 100, 50);
		changeLegs.render(renderer, playerCreation.getX() + playerCreation.getSize(), playerCreation.getY() + 100, 100, 50);
		randomiseAll.render(renderer, playerCreation.getX() + playerCreation.getSize() + 150, playerCreation.getY() - 150, 150, 50);

		

		// BUTTON FUNCTIONALITY
		if (maleGender.isPressed())
			playerCreation.body.gender = Player::Body::Gender::male;
		if (femaleGender.isPressed())
			playerCreation.body.gender = Player::Body::Gender::female;

		// Change Ear buttons
		if (ChangeEarTypeL.isPressed())
		{
			changeEarType(playerCreation, false);
		}
		else if (ChangeEarTypeR.isPressed())
		{
			changeEarType(playerCreation, true);
		}

		// Change Eye buttons
		if (ChangeEyeTypeL.isPressed())
		{
			changeEyeType(playerCreation, false);
		}
		else if (ChangeEyeTypeR.isPressed())
		{
			changeEyeType(playerCreation, true);
		}

		// Change Hair buttons
		if (ChangeHairTypeL.isPressed())
		{
			changeHairType(playerCreation, false);
		}
		else if (ChangeHairTypeR.isPressed())
		{
			changeHairType(playerCreation, true);
		}




		// Button functionality
		//Legs
		if (changeLegs.isPressed())
		{
			if (playerCreation.PlayerClothes.leg == Player::Clothing::noLeg)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
			else if (playerCreation.PlayerClothes.leg == Player::Clothing::chinos)
				playerCreation.PlayerClothes.leg = Player::Clothing::jeans;
			else if (playerCreation.PlayerClothes.leg == Player::Clothing::jeans)
				playerCreation.PlayerClothes.leg = Player::Clothing::chinos;
		}
		// Body
		if (changeBody.isPressed())
		{
			if (playerCreation.PlayerClothes.body == Player::Clothing::noShirt)
				playerCreation.PlayerClothes.body = Player::Clothing::jacket;
			else if (playerCreation.PlayerClothes.body == Player::Clothing::jacket)
				playerCreation.PlayerClothes.body = Player::Clothing::dress;
			else if (playerCreation.PlayerClothes.body == Player::Clothing::dress)
				playerCreation.PlayerClothes.body = Player::Clothing::jacket;
		}
		// Head
		if (changeHead.isPressed())
		{
			if (playerCreation.PlayerClothes.head == Player::Clothing::shortHair)
				playerCreation.PlayerClothes.head = Player::Clothing::longHair;
			else if (playerCreation.PlayerClothes.head == Player::Clothing::longHair)
				playerCreation.PlayerClothes.head = Player::Clothing::shortHair;
			else if (playerCreation.PlayerClothes.head == Player::Clothing::noHeadWear)
				playerCreation.PlayerClothes.head = Player::Clothing::shortHair;
		}


		// Body Colour
		if (ChangeBodyColour.isPressed())
		{
			hairColourSlider.Disable();
			eyeColourSlider.Disable();
			if (bodyColourSlider.isEnabled())
				bodyColourSlider.Disable();
			else
				bodyColourSlider.Enable();

		}
		// Hair colour
		if (ChangeHairColour.isPressed())
		{
			bodyColourSlider.Disable();
			eyeColourSlider.Disable();
			if (hairColourSlider.isEnabled())
				hairColourSlider.Disable();
			else
				hairColourSlider.Enable();
		}
		// Eye colour
		if (ChangeEyeColour.isPressed())
		{
			hairColourSlider.Disable();
			bodyColourSlider.Disable();
			if (eyeColourSlider.isEnabled())
				eyeColourSlider.Disable();
			else
				eyeColourSlider.Enable();
		}
		if (randomiseAll.isPressed())
		{
			playerCreation.setHairColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setEyeColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJacketColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setJeansColour(rand() % 255, rand() % 255, rand() % 255);
			playerCreation.setBodyColour(rand() % 255, rand() % 255, rand() % 255);
		}
		


		// Colour slider object positions and functionality
		// body slider
		if (bodyColourSlider.isEnabled())
		{
			ChangeBodyColour.getButtonBackgroundTexture().alterTextureColour(bodyColourSlider.getColour());
			bodyColourSlider.setPosition(gameSettings.WINDOW_WIDTH /2,  gameSettings.WINDOW_HEIGHT / 6);
			bodyColourSlider.setWidth(360);
			bodyColourSlider.setHeight(50);
			bodyColourSlider.Render(renderer);
			playerCreation.setBodyColour(bodyColourSlider.getColour());
		}
		// hair slider
		if (hairColourSlider.isEnabled())
		{
			ChangeHairColour.getButtonBackgroundTexture().alterTextureColour(hairColourSlider.getColour());
			hairColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			hairColourSlider.setWidth(360);
			hairColourSlider.setHeight(50);
			hairColourSlider.Render(renderer);
			playerCreation.setHairColour(hairColourSlider.getColour());
		}
		// eye slider
		if (eyeColourSlider.isEnabled())
		{
			ChangeEyeColour.getButtonBackgroundTexture().alterTextureColour(eyeColourSlider.getColour());
			eyeColourSlider.setPosition(gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT / 6);
			eyeColourSlider.setWidth(360);
			eyeColourSlider.setHeight(50);
			eyeColourSlider.Render(renderer);
			playerCreation.setEyeColour(eyeColourSlider.getColour());
		}
		
		// Render player
		playerCreation.RenderPlayer(renderer, camera);

		
		// Back button
		back.render(renderer, 50, 150, 100, 50);
		if (back.isPressed())
		{
			displayCharacterMenu = false;
			return;
		}

		// Start
		singlePlayer.render(renderer, gameSettings.WINDOW_WIDTH / 2 + 200, gameSettings.WINDOW_HEIGHT - 100, 100, 50);
		if (singlePlayer.isPressed())
		{
			gameSettings.running = true;
			gameSettings.useNetworking = false;
			displayCharacterMenu = false;
			displayMainMenu = false;
		}
		loadSave.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT - 100, 100, 50);
		if (loadSave.isPressed())
		{
			displayCharacterMenu = false;
			gameSettings.loadGameFromSave(level);
			player = gameSettings.getPlayerFromSave();
			displayMainMenu = false;
		}
		rotatePlayer.render(renderer, gameSettings.WINDOW_WIDTH / 2, gameSettings.WINDOW_HEIGHT - 150, 100, 50);
		if (rotatePlayer.isPressed())
		{
			int rotation = playerCreation.getTargetRotation() + 90;
			if (rotation > 360)
				rotation = 0;
			playerCreation.setTargetRotation(rotation);
		}


		//Render the mouse cursor last
		if (renderCursor)
			cursor.render(renderer, mouseX + (menuCursorSize / 2), mouseY + (menuCursorSize / 2), menuCursorSize, menuCursorSize);
		SDL_RenderPresent(renderer);
	}
	

	 //Only copy over the customsiation stuff
	//playerCreation.setSize(100);
	player.PlayerClothes = playerCreation.PlayerClothes;
	player.setHairColour(playerCreation.gethairColour().r, playerCreation.gethairColour().g, playerCreation.gethairColour().b);
	player.setEyeColour(playerCreation.getEyeColour().r, playerCreation.getEyeColour().g, playerCreation.getEyeColour().b);
	player.setJacketColour(playerCreation.getJacketColour().r, playerCreation.getJacketColour().g, playerCreation.getJacketColour().b);
	player.setJeansColour(playerCreation.getJeansColour().r, playerCreation.getJeansColour().g, playerCreation.getJeansColour().b);
	player.body = playerCreation.body;
	player.setBodyColour(playerCreation.getBodyColour().r, playerCreation.getBodyColour().g, playerCreation.getBodyColour().b);
	
}


void Menu::changeEarType(Player& player, bool increment)
{
	if (increment)
	{
		switch (player.body.earType)
		{
		case Player::Body::EarType::aquatic:
			player.body.earType = Player::Body::EarType::cat1;
			break;
		case Player::Body::EarType::cat1:
			player.body.earType = Player::Body::EarType::cat2;
			break;
		case Player::Body::EarType::cat2:
			player.body.earType = Player::Body::EarType::elf1;
			break;
		case Player::Body::EarType::elf1:
			player.body.earType = Player::Body::EarType::elf2;
			break;
		case Player::Body::EarType::elf2:
			player.body.earType = Player::Body::EarType::elf3;
			break;
		case Player::Body::EarType::elf3:
			player.body.earType = Player::Body::EarType::elf4;
			break;
		case Player::Body::EarType::elf4:
			player.body.earType = Player::Body::EarType::elf5;
			break;
		case Player::Body::EarType::elf5:
			player.body.earType = Player::Body::EarType::elf6;
			break;
		case Player::Body::EarType::elf6:
			player.body.earType = Player::Body::EarType::human;
			break;
		case Player::Body::EarType::human:
			player.body.earType = Player::Body::EarType::aquatic;
			break;
		}
	}
	else
		switch (player.body.earType)
		{
		case Player::Body::EarType::aquatic:
			player.body.earType = Player::Body::EarType::human;
			break;
		case Player::Body::EarType::human:
			player.body.earType = Player::Body::EarType::elf6;
			break;
		case Player::Body::EarType::elf6:
			player.body.earType = Player::Body::EarType::elf5;
			break;
		case Player::Body::EarType::elf5:
			player.body.earType = Player::Body::EarType::elf4;
			break;
		case Player::Body::EarType::elf4:
			player.body.earType = Player::Body::EarType::elf3;
			break;
		case Player::Body::EarType::elf3:
			player.body.earType = Player::Body::EarType::elf2;
			break;
		case Player::Body::EarType::elf2:
			player.body.earType = Player::Body::EarType::elf1;
			break;
		case Player::Body::EarType::elf1:
			player.body.earType = Player::Body::EarType::cat2;
			break;
		case Player::Body::EarType::cat2:
			player.body.earType = Player::Body::EarType::cat1;
			break;
		case Player::Body::EarType::cat1:
			player.body.earType = Player::Body::EarType::aquatic;
			break;
		}

}

void Menu::changeEyeType(Player& player, bool increment)
{
	if (increment)
	{
		switch (player.body.eyeType)
		{
		case Player::Body::EyeType::eye1:
			player.body.eyeType = Player::Body::EyeType::eye2;
			break;
		case Player::Body::EyeType::eye2:
			player.body.eyeType = Player::Body::EyeType::eye3;
			break;
		case Player::Body::EyeType::eye3:
			player.body.eyeType = Player::Body::EyeType::eye4;
			break;
		case Player::Body::EyeType::eye4:
			player.body.eyeType = Player::Body::EyeType::eye5;
			break;
		case Player::Body::EyeType::eye5:
			player.body.eyeType = Player::Body::EyeType::eye6;
			break;
		case Player::Body::EyeType::eye6:
			player.body.eyeType = Player::Body::EyeType::eye7;
			break;
		case Player::Body::EyeType::eye7:
			player.body.eyeType = Player::Body::EyeType::eye8;
			break;
		case Player::Body::EyeType::eye8:
			player.body.eyeType = Player::Body::EyeType::eye9;
			break;
		case Player::Body::EyeType::eye9:
			player.body.eyeType = Player::Body::EyeType::eye10;
			break;
		case Player::Body::EyeType::eye10:
			player.body.eyeType = Player::Body::EyeType::eye11;
			break;
		case Player::Body::EyeType::eye11:
			player.body.eyeType = Player::Body::EyeType::eye12;
			break;
		case Player::Body::EyeType::eye12:
			player.body.eyeType = Player::Body::EyeType::eye13;
			break;
		case Player::Body::EyeType::eye13:
			player.body.eyeType = Player::Body::EyeType::eye1;
			break;
		}
	}
	else
		switch (player.body.eyeType)
		{
		case Player::Body::EyeType::eye13:
			player.body.eyeType = Player::Body::EyeType::eye12;
			break;
		case Player::Body::EyeType::eye12:
			player.body.eyeType = Player::Body::EyeType::eye11;
			break;
		case Player::Body::EyeType::eye11:
			player.body.eyeType = Player::Body::EyeType::eye10;
			break;
		case Player::Body::EyeType::eye10:
			player.body.eyeType = Player::Body::EyeType::eye9;
			break;
		case Player::Body::EyeType::eye9:
			player.body.eyeType = Player::Body::EyeType::eye8;
			break;
		case Player::Body::EyeType::eye8:
			player.body.eyeType = Player::Body::EyeType::eye7;
			break;
		case Player::Body::EyeType::eye7:
			player.body.eyeType = Player::Body::EyeType::eye6;
			break;
		case Player::Body::EyeType::eye6:
			player.body.eyeType = Player::Body::EyeType::eye5;
			break;
		case Player::Body::EyeType::eye5:
			player.body.eyeType = Player::Body::EyeType::eye4;
			break;
		case Player::Body::EyeType::eye4:
			player.body.eyeType = Player::Body::EyeType::eye3;
			break;
		case Player::Body::EyeType::eye3:
			player.body.eyeType = Player::Body::EyeType::eye2;
			break;
		case Player::Body::EyeType::eye2:
			player.body.eyeType = Player::Body::EyeType::eye1;
			break;
		case Player::Body::EyeType::eye1:
			player.body.eyeType = Player::Body::EyeType::eye13;
			break;
		}

}

void Menu::changeHairType(Player& player, bool increment)
{
	if (increment)
	{
		switch (player.body.hairType)
		{
		case Player::Body::HairType::hair1:
			player.body.hairType = Player::Body::HairType::hair2;
			break;
		case Player::Body::HairType::hair2:
			player.body.hairType = Player::Body::HairType::hair3;
			break;
		case Player::Body::HairType::hair3:
			player.body.hairType = Player::Body::HairType::hair4;
			break;
		case Player::Body::HairType::hair4:
			player.body.hairType = Player::Body::HairType::hair5;
			break;
		case Player::Body::HairType::hair5:
			player.body.hairType = Player::Body::HairType::hair6;
			break;
		case Player::Body::HairType::hair6:
			player.body.hairType = Player::Body::HairType::hair7;
			break;
		case Player::Body::HairType::hair7:
			player.body.hairType = Player::Body::HairType::hair8;
			break;
		case Player::Body::HairType::hair8:
			player.body.hairType = Player::Body::HairType::hair1;
		}
	}
	else
		switch (player.body.hairType)
		{
		case Player::Body::HairType::hair8:
			player.body.hairType = Player::Body::HairType::hair7;
			break;
		case Player::Body::HairType::hair7:
			player.body.hairType = Player::Body::HairType::hair6;
			break;
		case Player::Body::HairType::hair6:
			player.body.hairType = Player::Body::HairType::hair5;
			break;
		case Player::Body::HairType::hair5:
			player.body.hairType = Player::Body::HairType::hair4;
			break;
		case Player::Body::HairType::hair4:
			player.body.hairType = Player::Body::HairType::hair3;
			break;
		case Player::Body::HairType::hair3:
			player.body.hairType = Player::Body::HairType::hair2;
			break;
		case Player::Body::HairType::hair2:
			player.body.hairType = Player::Body::HairType::hair1;
			break;
		case Player::Body::HairType::hair1:
			player.body.hairType = Player::Body::HairType::hair8;
		
		}

}