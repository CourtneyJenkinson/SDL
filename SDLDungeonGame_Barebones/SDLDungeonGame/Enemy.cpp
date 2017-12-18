#include "Enemy.h"

using namespace DungeonGame;

	void Enemy::InitEnemy(SDL_Renderer* pRenderer, EnemyData* pEnemyData)
	{
		m_pEnemyData = pEnemyData;
		Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		m_Size = Vector2d(64, 64);
	}


	Enemy::~Enemy()
	{

	}
	void Enemy::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
	{
		m_Position = m_pEnemyData->m_CurrentPosition
			+ Vector2d(m_Size.X * -0.5f, m_Size.Y * -0.5f);
		m_bVisible = m_pEnemyData->m_Hp > 0;


		Vector2d vectorToPlayer =
			playerState.m_CurrentPosition - m_pEnemyData->m_CurrentPosition;

		vectorToPlayer.Normalize();
		m_pEnemyData->m_CurrentPosition += vectorToPlayer * deltaSeconds * 120.0f;

		//collider
		//if (m_pEnemyData->bAlive && playerState.ItemToPlayerCollision(m_pEnemyData))
		//{
			//m_pEnemyData->bAlive = false;
		//}
	}

