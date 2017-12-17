#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Enemy : public Sprite
	{
	public:
		void InitEnemy(SDL_Renderer* pRenderer);
	};
}