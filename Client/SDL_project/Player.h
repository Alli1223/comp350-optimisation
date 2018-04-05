#pragma once
#include "Character.h"
#include "Animation.h"
#include "Items.h"
#include "GUI.h"
#include "InventoryUI.h"
#include "CraftingUI.h"
class Player : public Character
{
public:
	Player();
	~Player();
	
	//! Render the player
	void RenderPlayer(SDL_Renderer* renderer, Camera& camera);
	void RenderPlayerNew(SDL_Renderer* renderer, Camera& camera);
	//! Renders the characters clothes
	void renderCharacterClothes(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize, bool flipSprite);
	void renderCharacterBody(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize, bool flipSprite);
	//! Move the player to the position
	void Player::Move();


	json getPlayerJson();
	
	glm::vec2 renderOffset;
	glm::vec2 screenCenter;
	glm::vec2 placeItemPos;
	int xOffset, yOffset;

	//! Player clothes
	Clothing PlayerClothes;
	InventoryUI InventoryPanel;
	CraftingUI craftingUI;
	

	Animation getWalkAnimation() { return walkHorizontalAnimation; }
	SDL_Color gethairColour() { return hairColour; }
	SDL_Color getEyeColour() { return eyeColour; }
	SDL_Color getJacketColour() { return topColour; }
	SDL_Color getJeansColour() { return bottomColour; }
	SDL_Color getBodyColour() { return bodyColour; }
	int setHairColour(int r, int g, int b) { return hairColour.r = r, hairColour.g = g, hairColour.b = b; }
	int setEyeColour(int r, int g, int b) { return eyeColour.r = r, eyeColour.g = g, eyeColour.b = b; }
	int setJacketColour(int r, int g, int b) { return topColour.r = r, topColour.g = g, topColour.b = b; }
	int setJeansColour(int r, int g, int b) { return bottomColour.r = r, bottomColour.g = g, bottomColour.b = b; }
	int setBodyColour(int r, int g, int b) { return bodyColour.r = r, bodyColour.g = g, bodyColour.b = b; }
	SDL_Color setBodyColour(SDL_Color colour) { return bodyColour = colour; }
	SDL_Color setEyeColour(SDL_Color colour) { return eyeColour = colour; }
	SDL_Color setHairColour(SDL_Color colour) { return hairColour = colour; }
	SDL_Color setTopColour(SDL_Color colour) { return topColour = colour; }
	SDL_Color setBottomColour(SDL_Color colour) { return bottomColour = colour; }
	Inventory inventory;
	Pathfinder pathFinder;
	
private:
	//! Json data to store player stats
	json playerJsondata;
	//! Whether the player is able to move
	bool playerCanMove = true;
	//! Pixel size of the player sprite in the spritesheet
	int pixelSize = 64;
	//! Default colours
	SDL_Color hairColour = { 255,255,255 };
	SDL_Color eyeColour = { 255,255,255 };
	SDL_Color topColour = { 255,255,255 };
	SDL_Color bottomColour = { 255,255,255 };

	SDL_Color bodyColour = { 255,224,189 };
	//! Texture locations
	std::string characterTextureLocation = "Resources\\Sprites\\Character\\";
	std::string clothesTextureLocation = "Resources\\Characters\\Accessories\\Clothing\\";

	std::string CharacterTextureLocation = "Resources\\Characters\\";
	std::string CharacterEarsTextureLocation = "Resources\\Characters\\Accessories\\Ears\\";
	std::string CharacterEyesTextureLocation = "Resources\\Characters\\Accessories\\Eyes\\";
	std::string CharacterHairTextureLocation = "Resources\\Characters\\Accessories\\Hair\\";

	//! Gender Textures
	Texture male;
	Texture female;

	//! Ear Textures
	Texture aquaticEar;
	Texture catEar1;
	Texture catEar2;
	Texture elfEar1;
	Texture elfEar2;
	Texture elfEar3;
	Texture elfEar4;
	Texture elfEar5;
	Texture elfEar6;
	Texture human;

	Texture eye1;
	Texture eye2;
	Texture eye3;
	Texture eye4;
	Texture eye5;
	Texture eye6;
	Texture eye7;
	Texture eye8;
	Texture eye9;
	Texture eye10;
	Texture eye11;
	Texture eye12;
	Texture eye13;

	Texture hair1;
	Texture hair2;
	Texture hair3;
	Texture hair4;
	Texture hair5;
	Texture hair6;
	Texture hair7;
	Texture hair8;


	//!Shadow
	Texture playerShadow;

	//! Texture for the Character
	Texture characterIdleTexture;
	Texture walkTexture;
	Texture sideBlinkTexture;
	Texture shortHairTexture;
	Texture longHairTexture;
	Texture eyesTexture;
	
	//! Texture for the clothes
	Texture femaleTop1;
	Texture femaleTop2;
	Texture femaleBottom1;
	Texture femaleBottom2;
	//! Animations
	Animation walkHorizontalAnimation;
	Animation walkVerticalAnimation;
	Animation idleAnimation;
	Animation blinkAnimation;

	

};

