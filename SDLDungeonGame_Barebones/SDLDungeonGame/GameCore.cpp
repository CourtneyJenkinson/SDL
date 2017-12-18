#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"
#include "RoomRender.h"

namespace DungeonGame
{
	//Makes Background
	std::vector<Sprite*> g_spriteList;

	void PlayerState::Initialize()
	{
		//TODO: Initialize PlayerState stuff here

		Reset();
	}

	void PlayerState::Reset()
	{
		//TODO: Reseet PlayerState stuff to default values
		m_CurrentPosition = Vector2d(2.0f * 64.0f, 1.0f * 64.0f);

		m_bHasFinishedGame = false;
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


	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState)
	{
		worldState.Initialize();
		playerState.Initialize();

		
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
		enemySprite->Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		enemySprite->m_Size = Vector2d(64, 64);
		g_spriteList.push_back(enemySprite);


		//Load Hero Sprite
		Hero* heroSprite = new Hero;
		heroSprite->Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Wasp.bmp"));
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
		
	}

	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState)
	{
		SDL_RenderClear(pRenderer);

		for (unsigned int i = 0; i < g_spriteList.size(); i++)
		{
			g_spriteList[i]->Render(pRenderer, worldState, playerState);
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