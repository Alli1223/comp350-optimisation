#pragma once
#include "Level.h"
#include "Camera.h"
#include "Character.h"
#include "Player.h"
#include "GameSettings.h"

class CellRendering
{
public:
	CellRendering();
	~CellRendering();
	//! Render all game objects
	void RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, GameSettings& gameSettings, std::vector<std::shared_ptr<Player>>& allPlayers);
	static int CellRendering::RenderObjects2(void *data);
	//! Render a chunk of the level
	void CellRendering::RenderChunk(Level& level, Camera& camera, GameSettings& gameSettings, Player& player, std::shared_ptr<Chunk>& chunk);
	void CellRendering::threadededChunkrenderer(Level& level, Camera& camera, GameSettings& gameSettings, Player& player);
	//! Alter textures, i.e. transparency
	void CellRendering::AlterTextures(Level& level);
	//! Render player
	void CellRendering::RenderPlayer(SDL_Renderer* renderer, Player& player, Level& level, Camera& camera);
	//! Add texture to batch renderer
	void CellRendering::AddToBatchRendering(int ID, int x, int y, int& size, char layer);
	//! render cells around objects
	void CellRendering::renderCellsAroundObject(SDL_Renderer* renderer, Level& level, std::shared_ptr<Chunk>& chunk, int& x, int& y, int& xPos, int& yPos);
	//! Render player stats
	bool renderStats = false;
	//! If the game has darkness
	bool isThereDarkness = true;

	bool mFirstRun;
	
private:
	//Target Darkness
	float Tdarkness;
	float darkness = 255;
	float time = 0;

	

	const std::string SpriteSheets = "Resources\\Sprites\\SpriteSheets\\";
	const std::string RoomSpriteTextureLocation = "Resources\\Sprites\\roomSprites\\texturePack\\";
	const std::string ItemsSpriteTextureLocation = "Resources\\Sprites\\SpawnItems\\";
	const std::string TerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\";
	const std::string TreeTerrainSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Trees\\";
	const std::string WallSpriteTextureLocation = "Resources\\Sprites\\Terrain\\Walls\\";
	const std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	const std::string playerStatsTextureLocation = "Resources\\Sprites\\GUI\\PlayerStats\\";

	// Textures for game objects

	//! Are the textures for the statusbars
	Texture healthBarTexture;
	Texture hungerBarTexture;
	Texture tiredBarTexture;
	Texture oxygenBarTexture;
	Texture light;
	Texture lightsBackground;

	//TODO: load json file containing the array of different texture IDs //56 cells long
	int grassID = 5;
	int dirtID = 6;
	int sandID = 8;
	int waterID = 0;
	int water2ID = 1;
	int rockID = 614;
	int stoneID = 177;
	int redFlower = 542;
	int whiteFlower = 573;
	int blueFlower = 541;
	int bushID = 527;
	int redBerryBush = 528;
	int longGrass1 = 638;
	int longWood = 179;
	int stoneWall = 18;

	int woodFence = 1358;
	int woodHalfFence = 1415;

	int treeTop = 583;
	int treeBottom = 640;

	int waterTopLeft = 2;
	int waterTopMiddle = 3;
	int waterTopRight = 4;

	int waterMiddleLeft = 59;
	int waterMiddle = 60;
	int waterMiddleRight = 61;


	int waterBottomLeft = 114;
	int waterBottomMiddle = 115;
	int waterBottomRight = 116;

	//! Atlas textures
	Texture terrainAtlas;
	Texture roguelikeAtlas;
	Texture cropsAtlas;


	enum layers
	{
		seaLevel,
		ground,
		onGround,
		isCrops,
		abovePlayer
	};
	//! A vector of all textures
	std::vector<Chunk::textureID> allTextures;
	
};

