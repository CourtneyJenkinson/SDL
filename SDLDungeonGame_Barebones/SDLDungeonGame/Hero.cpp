#include "Hero.h"

using namespace DungeonGame;

void Hero::InitHero(SDL_Renderer* pRenderer)
{
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Wasp.bmp"));
	m_Size = Vector2d(256, 256);
}

 void Hero::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	 const float HERO_PIXELS_PER_SECOND = 300.0f * deltaSeconds;
	 Vector2d newPosition = playerState.m_CurrentPosition + playerState.m_DesiredDirection * HERO_PIXELS_PER_SECOND;
	 if (worldState.GetTileTypeAtPosition(newPosition) == 1)
	 {
		playerState.m_CurrentPosition = newPosition;
	 }
	 
	 //m_Position = playerState.m_CurrentPosition;
	 //Boundary
	 m_Position = playerState.m_CurrentPosition + Vector2d(m_Size.X, m_Size.Y);
}