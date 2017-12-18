#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Enemy : public Sprite
	{
	public:
		void InitEnemy(SDL_Renderer* pRenderer, EnemyData* m_pEnemyDat);
		~Enemy();
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		EnemyData* m_pEnemyData;
	};
}