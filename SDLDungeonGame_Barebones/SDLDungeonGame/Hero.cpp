#include "Hero.h"

using namespace DungeonGame;

void Hero::InitHero(SDL_Renderer* pRenderer)
{
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Wasp.bmp"));
	m_Size = Vector2d(256, 256);
}
