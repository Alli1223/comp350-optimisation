#include "stdafx.h"
#include "Chunk.h"


Chunk::Chunk()
{
	tiles.reserve(chunkSize);
}
Chunk::Chunk(int initX, int initY)
{
	x = initX;
	y = initY;
	chunkID = "X:" + std::to_string(x) + ",Y:" + std::to_string(y);
}

void Chunk::AddToBatchRendering(int ID, int x, int y, int size, char layer)
{

}



Chunk::~Chunk()
{
	if(!tiles.empty())
		tiles.erase(tiles.begin() , tiles.end());

}
