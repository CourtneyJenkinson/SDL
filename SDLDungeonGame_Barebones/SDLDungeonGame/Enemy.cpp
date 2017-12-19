#include "Enemy.h"

using namespace DungeonGame;

	void Enemy::InitEnemy(SDL_Renderer* pRenderer, EnemyData* pEnemyData)
	{
		m_pEnemyState = EnemyState_None;
		m_pEnemyData = pEnemyData;
		Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		m_Size = Vector2d(64, 64);

		m_SpawnPoint = m_pEnemyData->m_CurrentPosition;
		SetEnemyState(EnemyState_Idle);
	
	}


	Enemy::~Enemy()
	{

	}
	void Enemy::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
	{
		m_Position = m_pEnemyData->m_CurrentPosition
			+ Vector2d(m_Size.X * -0.5f, m_Size.Y * -0.5f);
		m_bVisible = m_pEnemyData->EnemyHp > 0;
		
		{
			m_Position = m_pEnemyData->m_CurrentPosition - m_Size * 0.5f;
			m_bVisible = m_pEnemyData->bAlive;

			//collider
			if (m_pEnemyData->bAlive && playerState.EnemyToPlayerCollision(m_pEnemyData))
			{
				m_pEnemyData->bAlive = false;
				playerState.m_HP--;
				if (playerState.m_HP <= 0)
				{
					playerState.m_bAlive = false;
				}
			}
		}

		switch (m_pEnemyState)
		{
		case EnemyState_Idle:
		{
			Vector2d vectorToPlayer =
				m_pEnemyData->m_CurrentPosition - playerState.m_CurrentPosition;
			if (vectorToPlayer.GetLength() > 300.0f)
			{
				SetEnemyState(EnemyState_Agro);
			}
			vectorToPlayer.Normalize();
			m_pEnemyData->m_CurrentPosition += vectorToPlayer * deltaSeconds * 120.0f;
		}
		break;

		case EnemyState_Agro:
		{
			Vector2d vectorToPlayer =
				m_pEnemyData->m_CurrentPosition - playerState.m_CurrentPosition;
			if (vectorToPlayer.GetLength() > 150.0f)
			{
				SetEnemyState(EnemyState_Return);
			}
			vectorToPlayer.Normalize();
			m_pEnemyData->m_CurrentPosition += vectorToPlayer * deltaSeconds * 120.0f;
		}
		break;

		case EnemyState_Return:
		{
			Vector2d vectorToHome =
				m_SpawnPoint - m_pEnemyData->m_CurrentPosition;
			if (vectorToHome.GetLength() < 10.0f)
			{
				SetEnemyState(EnemyState_Idle);
			}
			vectorToHome.Normalize();
			m_pEnemyData->m_CurrentPosition += vectorToHome * deltaSeconds * 60.0f;

		}
		break;



		//collider
		//if (m_pEnemyData->bAlive && playerState.ItemToPlayerCollision(m_pEnemyData))
		//{
			//m_pEnemyData->bAlive = false;
		//}
		}
	}

	void Enemy::SetEnemyState(EnemyState newEnemyState)
	{
		if (m_pEnemyState != newEnemyState)
		{
			//On Exit
			//switch (m_pEnemyState)
			//{
			//}
			m_pEnemyState = newEnemyState;
			//On Enter
			//switch (m_pEnemyState)
			//{
			//}
		}
	}

