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
	//! Render a chunk of the level
	void CellRendering::RenderChunk(Level& level, Camera& camera, GameSettings& gameSettings, Player& player, std::shared_ptr<Chunk>& chunk, SDL_Renderer* renderer);
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

	//TODO: load json file containing the array of different texture IDs
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
	int redBerryBush = 528;
	int longGrass1 = 638;
	int longWood = 179;

	int woodFence = 1356;


	int treeTop = 583;
	int treeBottom = 640;
	

	//! Atlas textures
	Texture terrainAtlas;
	Texture roguelikeAtlas;
	Texture cropsAtlas;

	//! Contains the data for texture positions and layers
	struct textureID
	{
		int index;
		int x, y;
		int width, height;
		//! texture transparency
		char transparency;
		//! Layer to be rendered on -- 0 = Ground -- 1 = Items on ground -- 2 = Player -- 3 = Above player
		char layer;
		//! Atlas to render texture from
		char atlasID;
	};

	enum layers
	{
		seaLevel,
		ground,
		onGround,
		isCrops,
		abovePlayer
	};
	//! A vector of all textures
	std::vector<textureID> allTextures;
	
};

