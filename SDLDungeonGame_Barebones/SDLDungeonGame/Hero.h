#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public:
		void InitHero(SDL_Renderer* pRenderer);
	};
}