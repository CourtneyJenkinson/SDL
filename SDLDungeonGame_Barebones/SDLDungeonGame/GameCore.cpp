#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "RoomRender.h"
#include "Item.h"
#include "Bullet.h"

namespace DungeonGame
{
	//Makes Background
	std::vector<Sprite*> g_spriteList;
	Vector2d cameraPosition;
	const unsigned int BULLET_COUNT = 3;


	void PlayerState::Initialize()
	{
		for (unsigned int i = 0; i < BULLET_COUNT; i++)
		{
			BulletData bullet = {};
			bullet.bAlive = false;
			m_Bullet.push_back(bullet);

		}

		Reset();
	}

	void PlayerState::Reset()
	{
		//Set spawn point
		m_CurrentPosition = Vector2d(2.0f * 64.0f, 1.0f * 64.0f);

		m_bWantsToShot = false;
		m_bHasFinishedGame = false;
		m_ShotCooldownSec - 0.0f;
	}

	bool PlayerState::ItemToPlayerCollision(ItemData* itemSprite)
	{
		//makes a vector from player to item
		Vector2d itemToPlayer = itemSprite->position - m_CurrentPosition;
		//gets the distance of the vector
		float distance = itemToPlayer.GetLength();
		//returns turn if player is less than 16 pixels of an item
		return distance < 64.0f;
	}

	

	void WorldState::Initialize()
	{
		//TODO: Initialize WorldState stuff here
		m_TilesPerRow = 8;
		m_Tiles =
		{
			0,2,2,2,2,2,2,0,
			0,2,1,1,1,1,2,0,
			0,2,1,1,1,1,2,0,
			0,2,1,1,1,1,2,0,
			0,2,1,1,1,1,2,0,
			0,2,1,1,1,1,2,0,
			0,2,2,2,2,2,2,0
		};

		//Adds Item to list
		ItemData item1 = {};
		item1.bAlive = true;
		item1.type = ITEM_Egg;
		item1.position = Vector2d(3.0f *64.0f, 3.0f *64.0f);
		m_Item.push_back(item1);

		ItemData item2 = {};
		item2.type = ITEM_Egg;
		item2.bAlive = true;
		item2.position = Vector2d(4.0f *64.0f, 3.0f *64.0f);
		m_Item.push_back(item2);

		Reset();
	}

	void WorldState::Reset()
	{
		//TODO: Reseet WorldState stuff to default values
	}

	unsigned int WorldState::GetTileTypeAtPosition(const Vector2d& inPosition)
	{
		int col = (int)(inPosition.X / 64.0f);
		int row = (int)(inPosition.Y / 64.0f);

		int index = row * m_TilesPerRow + col;
		if (index >= 0 && index < m_Tiles.size())
		{
			return m_Tiles[index];
		}

		return 1;
	}

	bool WorldState::BulletCollWithItem(BulletData* pBullet)
	{
		bool bHasCollided = false;
		for (unsigned int i = 0; i < m_Item.size(); i++)
		{
			ItemData& currItem = m_Item[i];
			//makes a vector from bullet to item
			Vector2d itemToBullet = pBullet->position - currItem.position;
			//gets the distance of the vector
			float distance = itemToBullet.GetLength();
			//returns true if bullet is less than 16 pixels of an item
			 bHasCollided = distance < 32.0f;
			if (bHasCollided)
			{
				bHasCollided = true;
				break;
			}
		}
		return bHasCollided;
	}

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState)
	{
		worldState.Initialize();
		playerState.Initialize();
		cameraPosition = Vector2d(); 

		
		//Load Background Sprite
		Sprite* backgroundSprite = new Sprite;
		backgroundSprite->Initialize(Sprite::LoadTexture(pRenderer, "Assets/background.bmp"));
		backgroundSprite->m_Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);
		g_spriteList.push_back(backgroundSprite);


		//Load Room
		RoomRender* roomSprite = new RoomRender;
		roomSprite->InitRoom(pRenderer);
		g_spriteList.push_back(roomSprite);
		
		//Load enemy Sprite
		Enemy* enemySprite = new Enemy;
		enemySprite->InitEnemy(pRenderer);
		enemySprite->m_Size = Vector2d(64, 64);
		g_spriteList.push_back(enemySprite);

		//Load Items
		for (unsigned int i = 0; i < worldState.m_Item.size(); i++)
		{
			Item* itemSprite = new Item;
			itemSprite->InitItem(pRenderer, &worldState.m_Item[i]);
			g_spriteList.push_back(itemSprite);
		}

		//Load Bullets
		for (unsigned int i = 0; i < playerState.m_Bullet.size(); i++)
		{
			Bullet* bulletSprite = new Bullet;
			bulletSprite->InitBullet(pRenderer, &playerState.m_Bullet[i]);
			g_spriteList.push_back(bulletSprite);
		}


		//Load Hero Sprite
		Hero* heroSprite = new Hero;
		heroSprite->InitHero(pRenderer);
		heroSprite->m_Size = Vector2d(128, 128);
		g_spriteList.push_back(heroSprite);
	
	}

	void GetInput(const WorldState& worldState, PlayerState& playerState)
	{
		

		SDL_Event e = {};
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				playerState.m_bHasFinishedGame = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_ESCAPE:
					playerState.m_bHasFinishedGame = true;
					break;
				case SDLK_UP:
					playerState.m_DesiredDirection.Y = -1.0f;
					break;
				case SDLK_DOWN:
					playerState.m_DesiredDirection.Y = 1.0f;
					break;
				case SDLK_RIGHT:
					playerState.m_DesiredDirection.X = 1.0f;
					break;
				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = -1.0f;
					break;
				case SDLK_SPACE:
					playerState.m_bWantsToShot = true;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				auto keyCode = e.key.keysym.sym;
				switch (keyCode)
				{
				case SDLK_UP:
				case SDLK_DOWN:
					playerState.m_DesiredDirection.Y = 0.0f;
					break;
				case SDLK_RIGHT:
				case SDLK_LEFT:
					playerState.m_DesiredDirection.X = 0.0f;
					break;
				case SDLK_SPACE:
					playerState.m_bWantsToShot = false;
					break;
				}
			}
		}
	}

	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState)
	{
		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Update(deltaSeconds, worldState, playerState);
		}
		cameraPosition = Vector2d(WINDOW_WIDTH * 0.5f, WINDOW_HEIGHT * 0.5f) - playerState.m_CurrentPosition;
	}

	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState)
	{
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Render(pRenderer, worldState, playerState, cameraPosition);
		}

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame()
	{
		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Cleanup();
			delete g_spriteList[i];
		}

		Sprite::ClearTextures();
	}
}