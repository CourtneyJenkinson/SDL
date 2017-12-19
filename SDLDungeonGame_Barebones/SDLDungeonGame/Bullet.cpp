#include "Bullet.h"

using namespace DungeonGame;

void Bullet::InitBullet(SDL_Renderer* pRenderer, BulletData* pBulletData)
{
	m_pBulletData = pBulletData;

	std::string textureFilename = "Assets/Tex_Spit.bmp";

	Sprite::Initialize(Sprite::LoadTexture(pRenderer, textureFilename.c_str()));

	m_Size = Vector2d(16, 16);
}
void Bullet::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	m_Position = m_pBulletData->position - m_Size * 0.5f;
	m_bVisible = m_pBulletData->bAlive;

	//Spawns bullets
	if (m_pBulletData->bAlive)
	{
		m_pBulletData->bulletLifeTime += deltaSeconds;
		if (m_pBulletData->bulletLifeTime >= 0.75f)
		{
			m_pBulletData->bAlive = false;
		}
		//Bullet Movement
		const float BULLET_SPEED = 300.0f * deltaSeconds;
		m_pBulletData->position = m_pBulletData->position + m_pBulletData->direction  * BULLET_SPEED;
	}

	//Bullet collide with item
	if (worldState.BulletCollWithItem(m_pBulletData))
	{
		m_pBulletData->bAlive = false;
	}

	if (worldState.BulletCollWithEnemy(m_pBulletData))
	{
		m_pBulletData->bAlive = false;
	}
}

