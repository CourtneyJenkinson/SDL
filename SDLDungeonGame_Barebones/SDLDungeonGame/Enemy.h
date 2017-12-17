#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Enemy : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer);
	};
}