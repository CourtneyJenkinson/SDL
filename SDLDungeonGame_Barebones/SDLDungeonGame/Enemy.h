#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	enum EnemyState
	{
		EnemyState_None,
		EnemyState_Idle,
		EnemyState_Agro,
		EnemyState_Return
	};

	class Enemy : public Sprite
	{
	public:
		void InitEnemy(SDL_Renderer* pRenderer, EnemyData* m_pEnemyDat);
		~Enemy();
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		void SetEnemyState(EnemyState newEnemyState);
		Vector2d m_SpawnPoint;
		EnemyData* m_pEnemyData;
		EnemyState m_pEnemyState;
	};
}