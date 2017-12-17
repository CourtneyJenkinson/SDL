#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"

namespace DungeonGame
{
	//Makes Background
	std::vector<Sprite*> g_spriteList;
	//Sprite backgroundSprite;  
	//Enemy enemySprite;
	//Hero heroSprite;

	void PlayerState::Initialize()
	{
		//TODO: Initialize PlayerState stuff here

		Reset();
	}

	void PlayerState::Reset()
	{
		//TODO: Reseet PlayerState stuff to default values

		m_bHasFinishedGame = false;
	}

	

	void WorldState::Initialize()
	{
		//TODO: Initialize WorldState stuff here

		Reset();
	}

	void WorldState::Reset()
	{
		//TODO: Reseet WorldState stuff to default values
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

		
		//Load enemy Sprite
		Sprite* enemySprite = new Enemy;
		enemySprite->Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		enemySprite->m_Size = Vector2d(64, 64);
		g_spriteList.push_back(enemySprite);


		//Load Hero Sprite
		Sprite* heroSprite = new Hero;
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