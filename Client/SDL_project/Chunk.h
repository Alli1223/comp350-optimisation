#pragma once
#include "Cell.h"
class Chunk
{
public:
	Chunk();
	~Chunk();
	Chunk::Chunk(int initX, int initY);
	int getChunkSize() { return chunkSize; }
	std::vector<std::vector<std::shared_ptr<Cell>>> tiles;
	void AddToBatchRendering(int ID, int x, int y, int size, char layer);

	int getX() { return x; }
	int getY() { return y; }

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
	std::vector<textureID> allTextures;
	UINT32 plantGrowSpeed;
	
private:
	int x = 0;
	int y = 0;
	int chunkSize = 8;
	
	std::string chunkID;
};

