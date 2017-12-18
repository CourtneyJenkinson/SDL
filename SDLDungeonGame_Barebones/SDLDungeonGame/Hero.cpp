#include "Hero.h"

using namespace DungeonGame;

void Hero::InitHero(SDL_Renderer* pRenderer)
{
	Sprite::Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Wasp.bmp"));
	m_Size = Vector2d(256, 256);
}

 void Hero::Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
{
	
	//Moving Logic
	{
		const float HERO_PIXELS_PER_SECOND = 300.0f * deltaSeconds;
		Vector2d newPosition = playerState.m_CurrentPosition + playerState.m_DesiredDirection * HERO_PIXELS_PER_SECOND;
	if (worldState.GetTileTypeAtPosition(newPosition) == 1)
	{
		playerState.m_CurrentPosition = newPosition;
	}
	}

	 //Boundary
	 m_Position = playerState.m_CurrentPosition - Vector2d(m_Size.X * 0.5f, m_Size.Y * 0.85f);

	 //Shooting Logic
	 {
		 playerState.m_ShotCooldownSec -= deltaSeconds;
		 if (playerState.m_ShotCooldownSec < 0.0f)
		 {
			 playerState.m_ShotCooldownSec = 0.0f;
		 }

		 if (playerState.m_bWantsToShot)
		 {
			 TryToShot(playerState);
		 }
	 }
}

 void Hero::TryToShot(PlayerState& playerState)
 {
	 if (playerState.m_ShotCooldownSec == 0.0f)
	 {
		 for (unsigned int i = 0; i < playerState.m_Bullet.size(); i++)
		 {
			 BulletData& currBullet = playerState.m_Bullet[i];
			 if (!currBullet.bAlive)
			 {
				 playerState.m_ShotCooldownSec = 0.4f;
				 currBullet.bAlive = true;
				 currBullet.bulletLifeTime = 0.0f;
				 currBullet.position = playerState.m_CurrentPosition;
				 currBullet.direction = Vector2d(0.0f, -1.0f);
				 //sets bullet directon
					 if (playerState.m_DesiredDirection != Vector2d(0.0f, 0.0f))
					 {
						 currBullet.direction = playerState.m_DesiredDirection;
					 }
				 break;
			 }
		 }
	 }
 }