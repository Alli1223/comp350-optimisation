#include "stdafx.h"
#include "Player.h"


Player::Player() : characterIdleTexture(characterTextureLocation + "idle.png"), 
shortHairTexture(clothesTextureLocation + "hair1.png"), longHairTexture(clothesTextureLocation + "hair2.png"),
eyesTexture(characterTextureLocation + "eyesAnim.png"), walkTexture(characterTextureLocation + "walk.png"), sideBlinkTexture(characterTextureLocation + "sideBlink.png"),
male(CharacterTextureLocation + "\\Male\\MaleBasic.png"), female(CharacterTextureLocation + "\\Female\\FemaleBasic.png"), playerShadow(CharacterTextureLocation + "\\Shared\\BasicShadows.png"),
aquaticEar(CharacterEarsTextureLocation + "Aquatic_Ears.png"),catEar1(CharacterEarsTextureLocation + "Cat_Ears_1.png"), catEar2(CharacterEarsTextureLocation + "Cat_Ears_2.png"),elfEar1(CharacterEarsTextureLocation + "Elf_Ears_1.png"),elfEar2(CharacterEarsTextureLocation + "Elf_Ears_2.png"),elfEar3(CharacterEarsTextureLocation + "Elf_Ears_3.png"), elfEar4(CharacterEarsTextureLocation + "Elf_Ears_4.png"),elfEar5(CharacterEarsTextureLocation + "Elf_Ears_5.png"),elfEar6(CharacterEarsTextureLocation + "Elf_Ears_6.png"),human(CharacterEarsTextureLocation + "Human_Ears.png"),
eye1(CharacterEyesTextureLocation + "Eye_type_1.png"), eye2(CharacterEyesTextureLocation + "Eye_type_2.png"), eye3(CharacterEyesTextureLocation + "Eye_type_3.png"), eye4(CharacterEyesTextureLocation + "Eye_type_4.png"), eye5(CharacterEyesTextureLocation + "Eye_type_5.png"), eye6(CharacterEyesTextureLocation + "Eye_type_6.png"), eye7(CharacterEyesTextureLocation + "Eye_type_7.png"), eye8(CharacterEyesTextureLocation + "Eye_type_8.png"), eye9(CharacterEyesTextureLocation + "Eye_type_9.png"), eye10(CharacterEyesTextureLocation + "Eye_type_10.png"), eye11(CharacterEyesTextureLocation + "Eye_type_11.png"), eye12(CharacterEyesTextureLocation + "Eye_type_12.png"), eye13(CharacterEyesTextureLocation + "Eye_type_13.png"),
hair1(CharacterHairTextureLocation + "Hair_1.png"), hair2(CharacterHairTextureLocation + "Hair_2.png"), hair3(CharacterHairTextureLocation + "Hair_3.png"), hair4(CharacterHairTextureLocation + "Hair_4.png"), hair5(CharacterHairTextureLocation + "Hair_5.png"), hair6(CharacterHairTextureLocation + "Hair_6.png"), hair7(CharacterHairTextureLocation + "Hair_7.png"), hair8(CharacterHairTextureLocation + "Hair_8.png"),
femaleTop1(clothesTextureLocation + "\\Female\\Tops\\Female_top_1.png"), femaleTop2(clothesTextureLocation + "\\Female\\Tops\\Female_top_2.png"), femaleBottom1(clothesTextureLocation + "\\Female\\Bottoms\\Female_Bottoms_1.png"), femaleBottom2(clothesTextureLocation + "\\Female\\Bottoms\\Female_Bottoms_2.png")
{
	walkHorizontalAnimation.maxFrames = 4;
	walkVerticalAnimation.maxFrames = 6;
	idleAnimation.maxFrames = 3;
	idleAnimation.setFrameRate(500);
	walkVerticalAnimation.setFrameRate(200);
	walkHorizontalAnimation.setFrameRate(200);
	blinkAnimation.maxFrames = 4;
	blinkAnimation.setFrameRate(200);
	blinkAnimation.oscillate = true;
}


Player::~Player()
{
}

void Player::Move()
{

}

void Player::RenderPlayerNew(SDL_Renderer* renderer, Camera& camera)
{
	
}

void Player::RenderPlayer(SDL_Renderer* renderer, Camera& camera)
{
	if (isPlayerMoving())
	{
		walkHorizontalAnimation.OnAnimate();
		walkVerticalAnimation.OnAnimate();
	}
	else
	{
		walkHorizontalAnimation.setCurrentFrame(0);
		walkVerticalAnimation.setCurrentFrame(0);
		idleAnimation.OnAnimate();
	}

	// Fixed a weird bug
	renderOffset.x = getX() - camera.getX();
	renderOffset.y = getY() - camera.getY();

	// Alter clothes colors
	shortHairTexture.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
	longHairTexture.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);

	eyesTexture.alterTextureColour(eyeColour, 100);
	sideBlinkTexture.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
	male.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
	female.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
	

	int idleX = 0;
	


	/// RENDER ROTATIONS ///
	//Walk Down (S)
	if (getTargetRotation() == 0 || getTargetRotation() == 360)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 2, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
		}

		else
		{
			renderCharacterBody(renderer, 0, pixelSize * 5, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, 0, pixelSize * 5, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
		}
	}


	// Walk Left (A)
	else if (getTargetRotation() == 90)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize(), true);
			renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, pixelSize, renderOffset.x, renderOffset.y, pixelSize, getSize(), true);
		}
		else
		{
			renderCharacterBody(renderer, 0, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize(), true);
			renderCharacterClothes(renderer, 0, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize(), true);
		}
			
	}
	// Walk Right (D)
	else if (getTargetRotation() == 270)
	{
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, walkHorizontalAnimation.getCurrentFrame() * pixelSize, 0, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);

		}

		else
		{

			renderCharacterBody(renderer, idleAnimation.getCurrentFrame() * pixelSize + 380, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, idleAnimation.getCurrentFrame() * pixelSize + 380, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
		}
	
	}
	// Walk Up (W)
	else if (getTargetRotation() == 180)
	{
		if (walkVerticalAnimation.getCurrentFrame() == 4)
			walkVerticalAnimation.setCurrentFrame(0);
		if (isPlayerMoving())
		{
			renderCharacterBody(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, walkVerticalAnimation.getCurrentFrame() * pixelSize, pixelSize * 3, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);

		}
		else
		{
			renderCharacterBody(renderer, 0, pixelSize * 4, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
			renderCharacterClothes(renderer, 0, pixelSize * 4, renderOffset.x, renderOffset.y, pixelSize, getSize(), false);
		}
	}
}

void Player::renderCharacterBody(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize, bool flipSprite)
{

	switch (body.gender)
	{
		// MALE BODY TYPE
	case Body::Gender::male:
		male.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
		// FEMALE BODY TYPE 
	case Body::Gender::female:
		female.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}


	switch (body.hairType)
	{
	case Body::HairType::hair1:
		hair1.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair2:
		hair2.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair3:
		hair3.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair3.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair4:
		hair4.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair4.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair5:
		hair5.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair5.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair6:
		hair6.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair6.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair7:
		hair7.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair7.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::HairType::hair8:
		hair8.alterTextureColour(hairColour.r, hairColour.g, hairColour.b);
		hair8.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}

	switch (body.eyeType)
	{
	case Body::EyeType::eye1:
		eye1.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye2:
		eye2.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye3:
		eye3.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye3.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye4:
		eye4.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye4.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye5:
		eye5.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye5.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye6:
		eye6.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye6.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye7:
		eye7.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye7.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye8:
		eye8.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye8.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye9:
		eye9.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye9.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye10:
		eye10.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye10.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye11:
		eye11.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye11.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye12:
		eye12.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye12.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EyeType::eye13:
		eye13.alterTextureColour(eyeColour.r, eyeColour.g, eyeColour.b);
		eye13.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}

	switch (body.earType)
	{
	case Body::aquatic:
		aquaticEar.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		aquaticEar.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::cat1:
		catEar1.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		catEar1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::cat2:
		catEar2.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		catEar2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf1:
		elfEar1.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf2:
		elfEar2.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf3:
		elfEar3.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar3.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf4:
		elfEar4.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar4.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf5:
		elfEar5.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar5.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::elf6:
		elfEar6.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		elfEar6.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	case Body::EarType::human:
		human.alterTextureColour(bodyColour.r, bodyColour.g, bodyColour.b);
		human.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}

	
	playerShadow.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
	
		
}

void Player::renderCharacterClothes(SDL_Renderer* renderer, int frameX, int frameY, int x, int y, int pixelSize, int characterSize, bool flipSprite)
{


	//Render leg wear
	switch (PlayerClothes.leg)
	{
	case Clothing::noBottoms:

		break;

	case Clothing::femaleBottom1:
		femaleBottom1.alterTextureColour(bottomColour.r, bottomColour.g, bottomColour.b);
		femaleBottom1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;

	case Clothing::femaleBottom2:
		femaleBottom2.alterTextureColour(bottomColour.r, bottomColour.g, bottomColour.b);
		femaleBottom2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}

	//Render body
	switch (PlayerClothes.body)
	{
	case Clothing::noTop:
		
		break;
	case Clothing::femaleTop1:
		femaleTop1.alterTextureColour(topColour.r, topColour.g, topColour.b);
		femaleTop1.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;

	case Clothing::femaleTop2:
		femaleTop2.alterTextureColour(topColour.r, topColour.g, topColour.b);
		femaleTop2.renderAnim(renderer, frameX, frameY, x, y, pixelSize, characterSize, flipSprite);
		break;
	}

}

// Modify this data aswell as in gameSettings.getPlayerFromSave()
json Player::getPlayerJson()
{
	json playerData;
	playerData["PlayerData"]["name"] = getID();
	playerData["PlayerData"]["rotation"] = getTargetRotation();
	playerData["PlayerData"]["X"] = getX();
	playerData["PlayerData"]["Y"] = getY();
	playerData["PlayerData"]["isMoving"] = isPlayerMoving();
	playerData["PlayerData"]["headWear"] = PlayerClothes.hat;
	playerData["PlayerData"]["hairColour"]["r"] = gethairColour().r;
	playerData["PlayerData"]["hairColour"]["g"] = gethairColour().g;
	playerData["PlayerData"]["hairColour"]["b"] = gethairColour().b;
	playerData["PlayerData"]["eyeColour"]["r"] = getEyeColour().r;
	playerData["PlayerData"]["eyeColour"]["g"] = getEyeColour().g;
	playerData["PlayerData"]["eyeColour"]["b"] = getEyeColour().b;
	playerData["PlayerData"]["bodyWear"] = PlayerClothes.body;
	playerData["PlayerData"]["upperClothesColour"]["r"] = getJacketColour().r;
	playerData["PlayerData"]["upperClothesColour"]["g"] = getJacketColour().g;
	playerData["PlayerData"]["upperClothesColour"]["b"] = getJacketColour().b;
	playerData["PlayerData"]["legWear"] = PlayerClothes.leg;
	playerData["PlayerData"]["legColour"]["r"] = getJeansColour().r;
	playerData["PlayerData"]["legColour"]["g"] = getJeansColour().g;
	playerData["PlayerData"]["legColour"]["b"] = getJeansColour().b;

	playerData["PlayerData"]["gender"] = body.gender;
	playerData["PlayerData"]["earType"] = body.earType;
	playerData["PlayerData"]["eyeType"] = body.eyeType;
	playerData["PlayerData"]["bodyColour"]["r"] = getBodyColour().r;
	playerData["PlayerData"]["bodyColour"]["g"] = getBodyColour().g;
	playerData["PlayerData"]["bodyColour"]["b"] = getBodyColour().b;

	return playerData;
}

