#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Hero : public Sprite
	{
	public:
		void InitHero(SDL_Renderer* pRenderer);
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

		int m_HP;
		int m_MP;
	};
}