#include "stdafx.h"
#include "Venture.h"
#include "InitialisationError.h"
void showErrorMessage(const char* message, const char* title)
{
	// Note: this is specific to Windows, and would need redefining to work on Mac or Linux
	MessageBoxA(nullptr, message, title, MB_OK | MB_ICONERROR);
}



Venture::Venture() : backgroundTexture("Resources\\background5.jpg"), mousePointer("Resources\\Sprites\\Cursor\\cursor.png")
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0 || SDL_Init(SDL_INIT_TIMER | SDL_INIT_JOYSTICK) < 0)
	{
		std::cout << (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError()) << std::endl;
		throw InitialisationError("SDL_Init failed");
	}
	
	SDL_ShowCursor(SDL_DISABLE);

	// Set Window Size
	gameSettings.getScreenResolution();

	gameSettings.WINDOW_HEIGHT;
	gameSettings.WINDOW_WIDTH;
	if (!gameSettings.fullscreen)
	{
		gameSettings.WINDOW_HEIGHT /=2;
		gameSettings.WINDOW_WIDTH /= 2;
	}
	gameSettings.deltaTime = SDL_GetTicks();
	

	camera.WindowHeight = gameSettings.WINDOW_HEIGHT;
	camera.WindowWidth = gameSettings.WINDOW_WIDTH;
	camera.SetPos(0, 0);
	


	// Create the window
	if (gameSettings.fullscreen)
		window = SDL_CreateWindow("VentureGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
	else
		window = SDL_CreateWindow("VentureGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	glContext = SDL_GL_CreateContext(window);
	if (window == nullptr)
		throw InitialisationError("SDL_CreateWindow failed");

	// Create Renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_TEXTUREACCESS_TARGET | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
		throw InitialisationError("SDL_CreateRenderer failed");

	// IF TTF Init error
	if (!TTF_WasInit() && TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(1);
	}
}

Venture::~Venture()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Venture::run()
{
	terrainGen.setSeed(321);

	level.GenerateWorld(camera);

	// Run the main menu
Menu:
	if (gameSettings.mainMenu)
	{
		Menu menu;
		menu.MainMenu(gameSettings, level, camera, player, renderer);
		menu.~menu();
	}

	// Generates the world around the camera position


	int cellSize = level.getCellSize();
	

	// Create a unique playername
	std::string playerName = std::to_string(SDL_GetTicks());

	player.characterType = "Player";
	player.setSpeed(0.5);
	player.setID(playerName);
	player.setX(0);
	player.setY(0); 
	

	UI.toolbar.createToolbar(player, gameSettings);

	player.inventory.setCapacity(56);
	// Add starting items
	Item hoe;
	hoe.type.Resource = Item::ItemType::isHOE;
	Item WoodAxe;
	WoodAxe.type.Resource = Item::ItemType::isWOODAXE;
	Item PickAxe;
	PickAxe.type.Resource = Item::ItemType::isPICKAXE;
	Item Scythe;
	Scythe.type.Resource = Item::ItemType::isSCYTHE;
	Item seeds;
	seeds.type.Resource = Item::ItemType::isSEEDS;
	Item waterCan;
	waterCan.type.Resource = Item::ItemType::isWATERINGCAN;
	Item fishingPole;
	fishingPole.type.Resource = Item::ItemType::isFISHINGROD;
	Item wood;
	wood.type.Resource = Item::ItemType::isWOOD;
	Item stone;
	stone.type.Resource = Item::ItemType::isSTONE;


	player.inventory.add(WoodAxe);
	player.inventory.add(PickAxe);
	player.inventory.add(hoe);
	player.inventory.add(waterCan);
	//player.inventory.add(fishingPole);
	player.inventory.add(Scythe);
	player.inventory.add(seeds);
	player.inventory.add(wood);

	player.InventoryPanel.setX(gameSettings.WINDOW_WIDTH / 2 + gameSettings.WINDOW_WIDTH / 4);
	player.InventoryPanel.setY(gameSettings.WINDOW_HEIGHT / 2);
	player.InventoryPanel.setHeight(gameSettings.WINDOW_HEIGHT - gameSettings.WINDOW_HEIGHT / 4);
	player.InventoryPanel.setWidth(gameSettings.WINDOW_WIDTH / 3);
	player.InventoryPanel.setIconSize(gameSettings.WINDOW_WIDTH / 50);
	player.InventoryPanel.CreateInventory(renderer, player.inventory);
	player.InventoryPanel.setDisplayInventory(false);

	player.craftingUI.setX(gameSettings.WINDOW_WIDTH / 4);
	player.craftingUI.setY(gameSettings.WINDOW_HEIGHT / 2);
	player.craftingUI.setHeight(gameSettings.WINDOW_HEIGHT - gameSettings.WINDOW_HEIGHT / 4);
	player.craftingUI.setWidth(gameSettings.WINDOW_WIDTH / 3);
	player.craftingUI.setIconSize(gameSettings.WINDOW_WIDTH / 25);
	gameSettings.fpsTimer.start();

	/////////////////////////////////////////////// MAIN LOOP ///////////////////////////////////////
	while (gameSettings.running)
	{
		// Get mouse Position
		SDL_GetMouseState(&mouseX, &mouseY);
		//gameSettings.getScreenResolution();

		if (gameSettings.displayFPS)
			gameSettings.CalculateFramesPerSecond();
		gameSettings.elapsedTime = SDL_GetTicks();

		
		gameSettings.mouseCellPos.x = mouseX / level.getCellSize() + camera.getX() / level.getCellSize();
		gameSettings.mouseCellPos.y = mouseY / level.getCellSize() + camera.getY() / level.getCellSize();



		// Handle the input
		input.HandleUserInput(renderer, level, player, camera, gameSettings, UI.toolbar, UI);
		player.setSize(level.getCellSize() * 2);
		
		//Player pos for camera lerp
		glm::vec2 playerPos;
		playerPos.x = player.getX() - camera.WindowWidth / 2;
		playerPos.y = player.getY() - camera.WindowHeight / 2;


		camera.Lerp_To(playerPos, camera.getCameraSpeed());
		level.GenerateWorld(camera);

		// Clear Rendering process:
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Update the position of the player
		player.Update(level);


		// Renders all the cells and players
		//std::thread renderThread(&CellRendering::RenderObjects, level, renderer, camera, player, gameSettings, allPlayers);
		
		struct data
		{

		};

		cellrenderer.RenderObjects(level, renderer, camera, player, gameSettings, allPlayers);

		// Render all the UI
		UI.Render(renderer, player, gameSettings);


		if(player.pathFinder.Path.size() > 0)
			player.pathFinder.drawPath(player.pathFinder.Path, renderer, camera, level);

		
		if (gameSettings.displayMouse)
			mousePointer.render(renderer, mouseX + (gameSettings.mousePointerSize / 2), mouseY + (gameSettings.mousePointerSize / 2), gameSettings.mousePointerSize, gameSettings.mousePointerSize * 1.5);
		SDL_RenderPresent(renderer);

		// If the level needs to be saved
		if (gameSettings.saveGame)
		{
			gameSettings.saveLevelData(level);
			gameSettings.saveGame = false;
		}

		gameSettings.deltaTime = gameSettings.elapsedTime - gameSettings.lastFrameTimeElapsed;
		gameSettings.lastFrameTimeElapsed = gameSettings.elapsedTime;
		// End while running
	}

	if (gameSettings.gotoMainMenu)
		goto Menu;
	///// END GAME LOOP //////


	// Save player settings when the game ends the game loop
	if (gameSettings.saveLevelOnExit && !gameSettings.useNetworking)
		gameSettings.saveLevelData(level);
	if (gameSettings.savePlayerOnExit)
		gameSettings.savePlayerSettings(player);
	if (gameSettings.restartGame)
		needsRestart = true;
}