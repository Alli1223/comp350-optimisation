#pragma once
#include "Point.h"
#include "Texture.h"
#include "Inventory.h"
#include "Items.h"
#include "PathFinder.h"
#include "Animation.h"
class Character
{
public:
	Character();
	~Character();
	

	//Getter methods
	//! Gets the characters X value
	int getX() { return x; }
	//! Gets the characters Y value
	int getY() { return y; }
	//! Gets the characters X offsetvalue
	int getOffsetX() { return offsetX; }
	//! Gets the characters Y offsetvalue
	int getOffsetY() { return offsetY; }
	//! Gets the characters X value
	int getCellX() { return cellX; }
	//! Gets the characters Y value
	int getCellY() { return cellY; }
	//! Gets the characters size
	int getSize() { return size; }
	//! Gets rotations
	int getRotation() { return rotation; }
	int getTargetRotation() { return targetRotation; }
	int getRotationSpeed() { return rotationSpeed; }
	//! Gets the characters speed
	double getSpeed() { return speed; }
	//! Gets and the agents health
	double getHealth() { return health; }
	//Setter methods
	//! Sets the characters X value
	int setX(int newX) { return x = newX; }
	//! Sets the characters Y value
	int setY(int newY) { return y = newY; }
	//! Sets the size of the character
	int setSize(int newSize) { return size = newSize; }
	//! Sets the characters cellX offset value
	int setOffsetX(int newOffsetX) { return offsetX = newOffsetX; }
	//! Sets the characters Y offset value
	int setOffsetY(int newOffsetY) { return offsetY = newOffsetY; }
	//! Sets the characters cellX value
	int setCellX(int newCellX) { return cellX = newCellX; }
	//! Sets the characters cellY value
	int setCellY(int newCellY) { return cellY = newCellY; }
	//! Sets the position that takes 2 arguments, x and y
	int setPosition(int newX, int newY) { return x = newX, y = newY; }
	//! Sets the characters current speed
	double setSpeed(double newSpeed) { return speed = newSpeed; }
	//! Sets the characters health
	double setHealth(double newHealth) { return health = newHealth; }
	//! Sets rotations
	int setRotation(int newRotation) { return rotation = newRotation; }
	int setTargetRotation(int newTarget) { return targetRotation = newTarget; }
	int setRotationSpeed(int newSpeed) { return rotationSpeed = newSpeed; }
	//! Player movement boolean
	bool setPlayerMoving(bool yayornay) { return isMoving = yayornay; }
	bool isPlayerMoving() { return isMoving; }
	//! Agent ID
	std::string getID() { return ID; }
	std::string setID(std::string newID) { return ID = newID; }
	//! Gets and sets the agents point location
	Point getAgentPointLocation() { return agentPointLocation; }
	Point setAgentPointLocation(Point newPointLocation) { return agentPointLocation = newPointLocation; }
	//! Character Type
	std::string characterType = "NPC";

	//! Position in the world
	glm::vec2 chunkPos, cellPos;
	void Character::Update(Level& level);

	//! Enum for chacter customisation
	typedef struct
	{
		enum HeadWear 
		{
			noHeadWear,
			hat1,
			ha2
		}hat;

		enum BodyWear 
		{
			noTop,
			femaleTop1,
			femaleTop2

		}body;

		enum LegWear 
		{
			noBottoms,
			femaleBottom1,
			femaleBottom2

		}leg;

	} Clothing;

	typedef struct 
	{
		enum Gender
		{
			male,
			female
		} gender;

		enum EarType
		{
			aquatic,
			cat1,
			cat2,
			elf1,
			elf2,
			elf3,
			elf4,
			elf5,
			elf6,
			human
		} earType;

		enum EyeType
		{
			eye1,
			eye2,
			eye3,
			eye4,
			eye5,
			eye6,
			eye7,
			eye8,
			eye9,
			eye10,
			eye11,
			eye12,
			eye13
		} eyeType;

		enum HairType
		{
			hair1,
			hair2,
			hair3,
			hair4,
			hair5,
			hair6,
			hair7,
			hair8
		} hairType;

	} Body;
	//! Characters body options
	Body body;

	//! Character clothes
	Clothing PlayerClothes;

private:
	//! string stores agent ID/Name
	std::string ID = "";
	//! Rotation values
	int rotation = 0, targetRotation = 0, rotationSpeed = 5;
	//! Integers for the agent's X and Y position
	int offsetX = 0, offsetY = 0;
	int x = 0; int y = 0;
	//! Integers for the agent's cellX and cellY positions below agent
	int cellX = 0; int cellY = 0;
	//! Point for where the agent is located
	Point agentPointLocation;
	//! Integer for the agent's size when rendered
	int size = 50;
	//! Integer for the agent current speed
	double speed = 0.3;
	//! Double for swim speed
	float swimSpeed = 0.1;
	//! Default walk speed
	float walkSpeed = 0.3;
	//! Default walk speed
	float runSpeed = 1.0;
	//! A double for the agents's health
	double health = 100.0;
	//! A double for agents hunger decrease speed
	double hunger = 0.0;
	//! If the Character can rotate
	bool incrementalRotating = false;
	//! if the Character is moving
	bool isMoving = false;


};

