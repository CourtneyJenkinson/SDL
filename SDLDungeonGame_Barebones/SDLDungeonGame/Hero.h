#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public:
		void Initialize(SDL_Renderer* pRenderer);
	};
}