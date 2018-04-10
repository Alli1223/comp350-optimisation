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

	int getX() { return x; }
	int getY() { return y; }
	UINT32 plantGrowSpeed;
	Timer activeTime;

	bool setActive(bool isactive) { return Active = isactive; }
	bool isActive() { return Active; }

	int setNewPosition(int X, int Y) { return x = X, y = Y; }
	
private:
	int x = 0;
	int y = 0;
	int chunkSize = 8;
	bool Active = false;
	
	std::string chunkID;
};

