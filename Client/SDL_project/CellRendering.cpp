#include "stdafx.h"
#include "CellRendering.h"

//! Constructor that initalises all the texture file locations
CellRendering::CellRendering() :
	healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"),
	hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png"),
	light(playerStatsTextureLocation + "light.png"), lightsBackground(playerStatsTextureLocation + "black.png"),
	terrainAtlas(SpriteSheets + "mapPack_tilesheet.png"), roguelikeAtlas(SpriteSheets + "roguelikeSheet_transparent.png"), cropsAtlas(SpriteSheets + "crops.png")
{
	// Set other atlas stats
	terrainAtlas.setTileSize(128);
	terrainAtlas.setTileSize(16);

	// Set rogue atlas stats
	roguelikeAtlas.setTileSize(16);
	roguelikeAtlas.setAtlasType(1);
	roguelikeAtlas.setTileWidth(56);

	cropsAtlas.setTileSize(32);
	cropsAtlas.setTileWidth(8);
	cropsAtlas.setAtlasType(0);


}

//! Destructor
CellRendering::~CellRendering()
{
}

void CellRendering::AddToBatchRendering(int ID, int x, int y, int& size, char layer)
{
	textureID texture;
	texture.index = ID;
	texture.x = x;
	texture.y = y;
	texture.width = size;
	texture.height = size;
	texture.layer = layer;
	allTextures.push_back(texture);
}


void CellRendering::AlterTextures(Level& level)
{
	SDL_SetTextureBlendMode(light.getTexture(), SDL_BLENDMODE_MOD);
		time = level.getTimeOfDay();

		if (time > 9.0 && time < 21.0)
		{
			Tdarkness = 255;
		}
		else if (time < 9.0 || time > 21.0)
		{
			Tdarkness = 50;
		}


		if (Tdarkness > darkness)
			darkness++;
		else if (Tdarkness < darkness)
			darkness--;
		
		roguelikeAtlas.alterTextureColour(darkness, darkness, darkness);
		
}

void CellRendering::RenderChunk(Level& level, Camera& camera, GameSettings& gameSettings, Player& player, std::shared_ptr<Chunk>& chunk, SDL_Renderer* renderer)
{
	int newX = 0, newY = 0;
	int xPos = 0, yPos = 0;
	int cellSize = level.getCellSize();

	for (int x = 0; x < level.getChunkSize(); x++)
		for (int y = 0; y < level.getChunkSize(); y++)
		{
			newX = chunk->tiles[x][y]->getX();
			newY = chunk->tiles[x][y]->getY();

			xPos = newX * cellSize + cellSize / 2;
			yPos = newY * cellSize + cellSize / 2;

			xPos -= camera.getX();
			yPos -= camera.getY();


			if (chunk->tiles[x][y]->isWater)
			{
				// Code for ripples
				//sin(sqrt(pow(chunk->tiles[x][y]->getX(),2) + pow(chunk->tiles[x][y]->getY(),2)) + SDL_GetTicks() / 500) > 0)
				if (sin(chunk->tiles[x][y]->getX() + SDL_GetTicks() / 500) > 0)
					AddToBatchRendering(waterID, xPos, yPos, cellSize, seaLevel);
				else
					AddToBatchRendering(water2ID, xPos, yPos, cellSize, seaLevel);

				switch (chunk->tiles[x][y]->orientation)
				{
				case Cell::orientation::topLeft:
					AddToBatchRendering(waterTopLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::topMiddle:
					AddToBatchRendering(waterTopMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::topRight:
					AddToBatchRendering(waterTopRight, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middleLeft:
					AddToBatchRendering(waterMiddleLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middle:
					AddToBatchRendering(waterMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::middleRight:
					AddToBatchRendering(waterMiddleRight, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomLeft:
					AddToBatchRendering(waterBottomLeft, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomMiddle:
					AddToBatchRendering(waterBottomMiddle, xPos, yPos, cellSize, ground);
					break;
				case Cell::orientation::bottomRight:
					AddToBatchRendering(waterBottomRight, xPos, yPos, cellSize, ground);
					break;
				}
			}
			

			// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
			if (chunk->tiles[x][y]->isGrass)
				AddToBatchRendering(grassID, xPos, yPos, cellSize, ground);
			if (chunk->tiles[x][y]->isSand)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, ground);

			if (chunk->tiles[x][y]->isDirt)
				AddToBatchRendering(dirtID, xPos, yPos, cellSize, ground);



			if (chunk->tiles[x][y]->isStoneWall)
				AddToBatchRendering(18, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isFlower1)
				AddToBatchRendering(blueFlower, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isFlower2)
				AddToBatchRendering(redFlower, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isBerryPlant)
				AddToBatchRendering(redBerryBush, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isBush)
				AddToBatchRendering(525, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isLongGrass)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isLongGrass2)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isSnow)
				AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isRock)
				AddToBatchRendering(rockID, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isWood)
				AddToBatchRendering(longWood, xPos, yPos, cellSize, onGround);
			else if (chunk->tiles[x][y]->isStone)
				AddToBatchRendering(stoneID, xPos, yPos, cellSize, onGround);



			if (chunk->tiles[x][y]->isWheat)
			{
				// Update seeds
				if (chunk->tiles[x][y]->plantTimer.getTicks() > gameSettings.plantGrowSpeed)
				{
					switch (chunk->tiles[x][y]->seedsStage)
					{
					case Cell::seedsGrowthStage::PlantStageOne:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageTwo;
						break;
					case Cell::seedsGrowthStage::PlantStageTwo:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageThree;
						break;
					case Cell::seedsGrowthStage::PlantStageThree:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageFour;
						break;
					case Cell::seedsGrowthStage::PlantStageFour:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageFive;
						break;
					case Cell::seedsGrowthStage::PlantStageFive:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageSix;
						break;
					case Cell::seedsGrowthStage::PlantStageSix:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageSeven;
						break;
					case Cell::seedsGrowthStage::PlantStageSeven:
						chunk->tiles[x][y]->seedsStage = Cell::seedsGrowthStage::PlantStageSeven;
						break;
					}
					chunk->tiles[x][y]->plantTimer.restart();
				}

				switch (chunk->tiles[x][y]->seedsStage)
				{
				case Cell::seedsGrowthStage::PlantStageOne:
					AddToBatchRendering(1, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageTwo:
					AddToBatchRendering(2, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageThree:
					AddToBatchRendering(3, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageFour:
					AddToBatchRendering(4, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageFive:
					AddToBatchRendering(5, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageSix:
					AddToBatchRendering(6, xPos, yPos, cellSize, isCrops);
					break;
				case Cell::seedsGrowthStage::PlantStageSeven:
					AddToBatchRendering(7, xPos, yPos, cellSize, isCrops);
					break;
				}
			}

			if (chunk->tiles[x][y]->isTree)
			{
				AddToBatchRendering(treeBottom, xPos, yPos, cellSize, onGround);
				AddToBatchRendering(treeTop, xPos, yPos - cellSize, cellSize, abovePlayer);
			}



			// Fences
			if (chunk->tiles[x][y]->isWoodFence)
			{
				AddToBatchRendering(woodHalfFence, xPos, yPos, cellSize, onGround);
				//renderCellsAroundObject(renderer, level, chunk, x, y, xPos, yPos);
			}
			

		}

}

void CellRendering::renderCellsAroundObject(SDL_Renderer* renderer, Level& level, std::shared_ptr<Chunk>& chunk, int& x, int& y, int& xPos, int& yPos)
{
	// Render Pools
	int cellSize = level.getCellSize();
	for(int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
		{
			if (level.isCellInChunk(x, y) && level.isCellInChunk(x, y + 1) && level.isCellInChunk(x - 1, y) && level.isCellInChunk(x + 1, y))
			{
			}
		}

		// Right
		if (level.getCell(xPos + 1, yPos)->isWoodFence && level.getCell(xPos, yPos + 1)->isWoodFence && level.getCell(xPos, yPos - 1)->isWoodFence && !level.getCell(xPos + 1, yPos)->isWoodFence && !level.getCell(xPos - 1, yPos)->isWoodFence)
		{
			AddToBatchRendering(woodFence, xPos, yPos - cellSize, cellSize, abovePlayer);
		}
		else if (level.getCell(xPos, yPos)->isWoodFence && level.getCell(xPos, yPos + 1)->isWoodFence && level.getCell(xPos, yPos - 1)->isWoodFence && !level.getCell(xPos + 1, yPos)->isWoodFence && !level.getCell(xPos - 1, yPos)->isWoodFence)
		{
			AddToBatchRendering(woodFence +1, xPos, yPos - cellSize, cellSize, abovePlayer);
		}
		//WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
		else
		{
			AddToBatchRendering(woodFence + 2, xPos, yPos - cellSize, cellSize, abovePlayer);
		}
		//WoodFenceSide.render(renderer, xPos, yPos, cellSize, cellSize);
		
	
}

//! Renders the chunks of cells
void CellRendering::RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, GameSettings& gameSettings, std::vector<std::shared_ptr<Player>>& allPlayers)
{	
	// Alter the textures
	AlterTextures(level);
	int x, y;
	// Render all the cells in the chunks
	for (int i = (camera.getX() / level.getCellSize()) / level.getChunkSize() - 1; i < ((camera.getX() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.x; i++)
		for (int j = (camera.getY() / level.getCellSize()) / level.getChunkSize() - 1; j < ((camera.getY() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.y; j++)
				RenderChunk(level,camera, gameSettings, player, level.World[i][j], renderer);


	// Batch render all the textures
	for each(auto &texture in allTextures)
	{
		switch (texture.layer)
		{
		case seaLevel:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case ground:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case onGround:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		case isCrops:
			cropsAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		}
	}
	



	// Render the player
	player.RenderPlayer(renderer, camera);
	//Update and render multi players
	for each (auto &player in allPlayers)
	{
		player->Update(level);
		player->RenderPlayer(renderer, camera);
	}

	// Batch render all the textures
	for each(auto &texture in allTextures)
	{
		switch (texture.layer)
		{
		case abovePlayer:
			roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height);
			break;
		}
	}


	//SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1000, 1000);
	//hungerBarTexture.alterTransparency(100);
	//SDL_SetRenderTarget(renderer, lightsBackground.getTexture());
	//light.alterTransparency(100);
	hungerBarTexture.render(renderer, player.placeItemPos.x * level.getCellSize() + (level.getCellSize() / 2) - camera.getX() , player.placeItemPos.y * level.getCellSize() + (level.getCellSize() / 2) - camera.getY(), level.getCellSize(), level.getCellSize());
	//light.renderLight(renderer, 0,0, player.getX() - camera.getX(), player.getY() - camera.getY(), level.getCellSize() * 10, level.getCellSize() * 10);
	//SDL_SetRenderTarget(renderer, NULL);
	//lightsBackground.render(renderer, 0, 0, gameSettings.WINDOW_WIDTH, gameSettings.WINDOW_HEIGHT);
	
	
	allTextures.erase(allTextures.begin(), allTextures.end());
	
}

void CellRendering::RenderPlayer(SDL_Renderer* renderer, Player& player,  Level& level, Camera& camera)
{
	//int x = player.getX() - camera.getX();
	//int y = player.getY() - camera.getY();
	//player.setPosition(x, y);
	//if (player.characterType == "Player")
		//characterTex.renderRotation(renderer, x, y, player.getSize(), player.getSize(), player.getRotation());
		//player.RenderPlayer(renderer);

}