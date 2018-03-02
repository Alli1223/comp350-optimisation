#include "stdafx.h"
#include "CellRendering.h"

//! Constructor that initalises all the texture file locations
CellRendering::CellRendering() : 
healthBarTexture(playerStatsTextureLocation + "PlayerHealth.png"), oxygenBarTexture(playerStatsTextureLocation + "PlayerOxygen.png"), hungerBarTexture(playerStatsTextureLocation + "PlayerHunger.png"), tiredBarTexture(playerStatsTextureLocation + "PlayerTiredness.png"),
terrainAtlas(TerrainSpriteTextureLocation + "SpriteSheets\\mapPack_tilesheet.png"), roguelikeAtlas(TerrainSpriteTextureLocation + "SpriteSheets\\roguelikeSheet_transparent.png")
{
	// Set other atlas stats
	terrainAtlas.setTileSize(128);
	terrainAtlas.setTileSize(16);

	// Set rogue atlas stats
	roguelikeAtlas.setTileSize(16);
	roguelikeAtlas.setAtlasType(1);
	roguelikeAtlas.setTileWidth(56);
}

//! Destructor
CellRendering::~CellRendering()
{
}

void CellRendering::AddToBatchRendering(int ID, int& x, int& y, int& size, char layer)
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
	
	//TreePixelTexture.alterTransparency(200);

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

void CellRendering::RenderChunk(Level& level, Camera& camera, Player& player, std::shared_ptr<Chunk>& chunk, SDL_Renderer* renderer)
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

			}
			else
			{
				// Base Ground Textures rendered in decending order (Top layered textures at bottom of list)
				if (chunk->tiles[x][y]->isGrass)
					AddToBatchRendering(899, xPos, yPos, cellSize, onGround);
				if (chunk->tiles[x][y]->isSand)
					AddToBatchRendering(8, xPos, yPos, cellSize, onGround);

				if (chunk->tiles[x][y]->isFlower1)
					AddToBatchRendering(409, xPos, yPos, cellSize, onGround);;
				if (chunk->tiles[x][y]->isDirt)
					AddToBatchRendering(6, xPos, yPos, cellSize, onGround);



				if (chunk->tiles[x][y]->isStoneWall)
					AddToBatchRendering(18, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isFlower1)
					AddToBatchRendering(395, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isFlower2)
					AddToBatchRendering(395, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isBerryPlant)
					AddToBatchRendering(820, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isBush)
					AddToBatchRendering(815, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isLongGrass)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isLongGrass2)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isSnow)
					AddToBatchRendering(sandID, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isRock)
					AddToBatchRendering(525, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isWood)
					AddToBatchRendering(78, xPos, yPos, cellSize, onGround);
				else if (chunk->tiles[x][y]->isStone)
					AddToBatchRendering(58, xPos, yPos, cellSize, onGround);


				if (chunk->tiles[x][y]->isWheat)
				{
					switch (chunk->tiles[x][y]->seedsStage)
					{
					case Cell::seedsGrowthStage::PlantStageOne:
						//WheatStageOne.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageTwo:
						//WheatStageTwo.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageThree:
						//WheatStageThree.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					case Cell::seedsGrowthStage::PlantStageFour:
						//WheatStageFour.render(renderer, xPos, yPos, cellSize, cellSize);
						break;
					}
				}

				if (chunk->tiles[x][y]->isTree)
				{
					AddToBatchRendering(631, xPos, yPos, cellSize, abovePlayer);
					AddToBatchRendering(575, xPos, yPos, cellSize, abovePlayer);
				}
				//BUSH 815 - 830
				//TREE - 575 - 631



				if (chunk->tiles[x][y]->isWoodFence)
				{
					//WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
					// Uncomment for fences to be combined
					if (level.isCellInChunk(x, y - 1) && level.isCellInChunk(x, y + 1) && level.isCellInChunk(x - 1, y) && level.isCellInChunk(x + 1, y))
					{
						/*
						if (chunk->tiles[x][y]->isWoodFence && chunk->tiles[x][y + 1]->isWoodFence && chunk->tiles[x][y - 1]->isWoodFence && !chunk->tiles[x + 1][y]->isWoodFence && !chunk->tiles[x - 1][y]->isWoodFence)
							//WoodFenceUP.render(renderer, xPos, yPos, cellSize, cellSize);
						else if (chunk->tiles[x][y]->isWoodFence && chunk->tiles[x][y + 1]->isWoodFence && chunk->tiles[x][y - 1]->isWoodFence && chunk->tiles[x + 1][y]->isWoodFence && chunk->tiles[x - 1][y]->isWoodFence)
							//WoodFenceCenter.render(renderer, xPos, yPos, cellSize, cellSize);
						else
							//WoodFenceSide.render(renderer, xPos, yPos, cellSize, cellSize);
							*/
					}
				}
			}
		}
}


//! Renders the chunks of cells
void CellRendering::RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, std::vector<std::shared_ptr<Player>>& allPlayers)
{	
	// Alter the textures
	AlterTextures(level);

	// Render all the cells in the chunks
	for (int i = (camera.getX() / level.getCellSize()) / level.getChunkSize() - 1; i < ((camera.getX() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.x - 1; i++)
		for (int j = (camera.getY() / level.getCellSize()) / level.getChunkSize() - 1; j < ((camera.getY() / level.getCellSize()) / level.getChunkSize()) + camera.ChunksOnScreen.y - 1; j++)
				RenderChunk(level,camera,player, level.World[i][j], renderer);

	// Batch render all the textures
	for each(auto &texture in allTextures)
	{
		roguelikeAtlas.renderAtlas(renderer, texture.index, texture.x, texture.y, texture.width, texture.height );
	}
	allTextures.erase(allTextures.begin(), allTextures.end());



	// Render the player
	player.RenderPlayer(renderer, camera);
	//Update and render multi players
	for each (auto &player in allPlayers)
	{
		player->Update(level);
		player->RenderPlayer(renderer, camera);
	}


	hungerBarTexture.alterTransparency(100);
	hungerBarTexture.render(renderer, player.placeItemPos.x * level.getCellSize() + (level.getCellSize() / 2) - camera.getX() , player.placeItemPos.y * level.getCellSize() + (level.getCellSize() / 2) - camera.getY(), level.getCellSize(), level.getCellSize());
	

	
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