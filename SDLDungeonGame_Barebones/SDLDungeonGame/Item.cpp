#include "Item.h"

using namespace DungeonGame;

void Item::InitItem(SDL_Renderer* pRenderer, ItemData* pItemData)
{
	m_pItemData = pItemData;

	std::string textureFilename = "Assets/Tex_Egg.bmp";

	switch (m_pItemData->type)
	{
	case ITEM_Egg:
		textureFilename = "Assets/Tex_Egg.bmp";
		break;
	}

		Sprite::Initialize(Sprite::LoadTexture(pRenderer, textureFilename.c_str()));

	m_Size = Vector2d(32, 32);
}
void Item::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState) 
{
	m_Position = m_pItemData->position - m_Size * 0.5f;
	m_bVisible = m_pItemData->bAlive;

	//collider
	if (m_pItemData->bAlive && playerState.ItemToPlayerCollision(m_pItemData))
	{
		m_pItemData->bAlive = false;
		//adds to player inventor
		playerState.m_Inventory.push_back(m_pItemData->type);
	}
}