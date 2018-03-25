#include "stdafx.h"
#include "Items.h"


Item::Item()
{
}

Item::Item(Item::ItemType type)
{
	this->type.Resource = type.Resource;
}


Item::~Item()
{
}