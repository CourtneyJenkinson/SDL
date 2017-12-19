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

	void EnemyData::OnHitByBullet(BulletData* pBullet)
	{
		EnemyHp--;
		if (EnemyHp <= 0)
		{
			bAlive = false;
		}
	}

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
		m_bAlive = true;
		m_HP = 5;

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

	bool PlayerState::EnemyToPlayerCollision(EnemyData* enemySprite)
	{
		//makes a vector from player to item
		Vector2d enemyToPlayer = enemySprite->m_CurrentPosition - m_CurrentPosition;
		//gets the distance of the vector
		float distance = enemyToPlayer.GetLength();
		//returns turn if player is less than 16 pixels of an item
		return distance < 64.0f;
	}

	

	void WorldState::Initialize()
	{
		//TODO: Initialize WorldState stuff here
		m_TilesPerRow = 48;
		m_Tiles =
		{
			0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			0,2,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,
			0,2,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,
			0,2,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,
			0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,2,1,1,1,2,
			0,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,2,1,1,1,2,
			0,2,1,1,1,2,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,2,1,1,1,2,
			0,2,1,1,1,2,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,2,0,0,0,0,2,1,1,1,2,
			0,2,1,1,1,2,0,0,0,0,0,0,0,0,2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,2,0,0,0,0,2,1,1,1,2,
			0,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,1,1,1,2,2,2,2,2,2,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,
			0,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,
			0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

		}; 

		//Adds Item to list
		{
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

			ItemData item3 = {};
			item3.type = ITEM_Egg;
			item3.bAlive = true;
			item3.position = Vector2d(16.0f *64.0f, 6.0f *64.0f);
			m_Item.push_back(item3);

			ItemData item4 = {};
			item4.type = ITEM_Egg;
			item4.bAlive = true;
			item4.position = Vector2d(16.0f *64.0f, 5.0f *64.0f);
			m_Item.push_back(item4);

			ItemData item5 = {};
			item5.type = ITEM_Egg;
			item5.bAlive = true;
			item5.position = Vector2d(17.0f *64.0f, 5.0f *64.0f);
			m_Item.push_back(item5);

			ItemData item6 = {};
			item6.type = ITEM_Egg;
			item6.bAlive = true;
			item6.position = Vector2d(34.0f *64.0f, 2.0f *64.0f);
			m_Item.push_back(item6);

			ItemData item7 = {};
			item7.type = ITEM_Egg;
			item7.bAlive = true;
			item7.position = Vector2d(44.0f *64.0f, 2.0f *64.0f);
			m_Item.push_back(item7);

			ItemData item8 = {};
			item8.type = ITEM_Egg;
			item8.bAlive = true;
			item8.position = Vector2d(45.0f *64.0f, 2.0f *64.0f);
			m_Item.push_back(item8);

			ItemData item9 = {};
			item9.type = ITEM_Egg;
			item9.bAlive = true;
			item9.position = Vector2d(46.0f *64.0f, 2.0f *64.0f);
			m_Item.push_back(item9);

			ItemData item10 = {};
			item10.type = ITEM_Egg;
			item10.bAlive = true;
			item10.position = Vector2d(46.0f *64.0f, 3.0f *64.0f);
			m_Item.push_back(item10);

			ItemData item11 = {};
			item11.type = ITEM_Egg;
			item11.bAlive = true;
			item11.position = Vector2d(45.0f *64.0f, 3.0f *64.0f);
			m_Item.push_back(item11);

			ItemData item12 = {};
			item12.type = ITEM_Egg;
			item12.bAlive = true;
			item12.position = Vector2d(29.0f *64.0f, 11.0f *64.0f);
			m_Item.push_back(item12);

			ItemData item13 = {};
			item13.type = ITEM_Egg;
			item13.bAlive = true;
			item13.position = Vector2d(28.0f *64.0f, 11.0f *64.0f);
			m_Item.push_back(item13);

			ItemData item14 = {};
			item14.type = ITEM_Egg;
			item14.bAlive = true;
			item14.position = Vector2d(28.0f *64.0f, 12.0f *64.0f);
			m_Item.push_back(item14);

			ItemData item15 = {};
			item15.type = ITEM_Egg;
			item15.bAlive = true;
			item15.position = Vector2d(17.0f *64.0f, 13.0f *64.0f);
			m_Item.push_back(item15);

			ItemData item16 = {};
			item16.type = ITEM_Egg;
			item16.bAlive = true;
			item16.position = Vector2d(16.0f *64.0f, 13.0f *64.0f);
			m_Item.push_back(item16);

			ItemData item17 = {};
			item17.type = ITEM_Egg;
			item17.bAlive = true;
			item17.position = Vector2d(16.0f *64.0f, 12.0f *64.0f);
			m_Item.push_back(item17);
		}

			//Adds Enemy to list
		{
			EnemyData enemy1 = {};
			enemy1.bAlive = true;
			enemy1.EnemyHp = 3;
			enemy1.m_CurrentPosition = Vector2d(10.0f *64.0f, 3.0f *64.0f);
			//enemy1.NavPoints.push_back(5.0f *64.0f, 1.0f *64.0f);
			m_Enemy.push_back(enemy1);

			EnemyData enemy2 = {};
			enemy2.bAlive = true;
			enemy2.EnemyHp = 3;
			enemy2.m_CurrentPosition = Vector2d(20.0f *64.0f, 12.0f *64.0f);
			m_Enemy.push_back(enemy2);

			EnemyData enemy3 = {};
			enemy3.bAlive = true;
			enemy3.EnemyHp = 3;
			enemy3.m_CurrentPosition = Vector2d(29.0f *64.0f, 11.0f *64.0f);
			m_Enemy.push_back(enemy3);

			EnemyData enemy4 = {};
			enemy4.bAlive = true;
			enemy4.EnemyHp = 3;
			enemy4.m_CurrentPosition = Vector2d(3.0f *64.0f, 15.0f *64.0f);
			m_Enemy.push_back(enemy4);

			EnemyData enemy5 = {};
			enemy5.bAlive = true;
			enemy5.EnemyHp = 3;
			enemy5.m_CurrentPosition = Vector2d(29.0f *64.0f, 16.0f *64.0f);
			m_Enemy.push_back(enemy5);


			EnemyData enemy6 = {};
			enemy6.bAlive = true;
			enemy6.EnemyHp = 3;
			enemy6.m_CurrentPosition = Vector2d(37.0f *64.0f, 16.0f *64.0f);
			m_Enemy.push_back(enemy6);
		}



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

	bool WorldState::BulletCollWithEnemy(BulletData* pBullet)
	{
		bool bHasCollided = false;
		for (unsigned int i = 0; i < m_Enemy.size(); i++)
		{
			EnemyData& currEnemy = m_Enemy[i];
			//makes a vector from bullet to enemy
			Vector2d enemyToBullet = pBullet->position - currEnemy.m_CurrentPosition;
			//gets the distance of the vector
			float distance = enemyToBullet.GetLength();
			//returns true if bullet is less than 16 pixels of an enemy
			bHasCollided = distance < 32.0f;
			if (bHasCollided)
			{
				//runs a destroy func
				currEnemy.OnHitByBullet(pBullet);
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
		for (unsigned int i = 0; i < worldState.m_Enemy.size(); i++)
		{
			Enemy* enemySprite = new Enemy;
			enemySprite->InitEnemy(pRenderer, &worldState.m_Enemy[i]);
			enemySprite->m_Size = Vector2d(64, 64);
			g_spriteList.push_back(enemySprite);
		}

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

		//WIN CONDITION
		if (playerState.m_Inventory.size() >= 17)
		{
			exit(15);
		}
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