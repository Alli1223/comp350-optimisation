#pragma once
#include "Level.h"
#include "Camera.h"
#include "Character.h"
#include "Player.h"

class CellRendering
{
public:
	CellRendering();
	~CellRendering();

	void RenderObjects(Level& level, SDL_Renderer* renderer, Camera& camera, Player& player, std::vector<std::shared_ptr<Player>>& allPlayers);

	void CellRendering::RenderChunk(Level& level, Camera& camera, Player& player, std::shared_ptr<Chunk>& chunk, SDL_Renderer* renderer);

	void CellRendering::AlterTextures(Level& level);

	void CellRendering::RenderPlayer(SDL_Renderer* renderer, Player& player, Level& level, Camera& camera);

	void CellRendering::AddToBatchRendering(int ID, int x, int y, int size);

	bool renderStats = false;
	
	struct tree
	{
		glm::vec2 pos;
		bool isFern = false;
		bool isOak = false;
		bool isPine = false;
		glm::vec2 treeSize;
	};
	

	std::vector<tree> treesBelow;
	std::vector<tree> treesAbove;

	bool isThereDarkness = true;

	

private:

	std::vector<Texture> texturesToRender;

	//Target Darkness
	float Tdarkness;
	float darkness = 255;
	float time = 0;
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
	int sandID = 8;
	int waterID = 0;
	int water2ID = 1;

	Texture terrainAtlas;
	Texture atlasTwoTest;


	struct textureID
	{
		int index;
		int x, y;
		int width, height;
	};

	std::vector<textureID> allTextures;

	
};

