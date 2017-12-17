#include "Enemy.h"

using namespace DungeonGame;

	void Enemy::Initialize(SDL_Renderer* pRenderer)
	{
		Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		m_Size = Vector2d(64, 64);
	}
