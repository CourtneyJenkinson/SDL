#include "GameCore.h"
#include "Sprite.h"
#include "Enemy.h"
#include "Hero.h"

namespace DungeonGame
{
	//Makes Background
	Sprite backgroundSprite;  
	Enemy enemySprite;
	Hero heroSprite;

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
		backgroundSprite.Initialize(Sprite::LoadTexture(pRenderer, "Assets/background.bmp"));
		backgroundSprite.m_Size = Vector2d(WINDOW_WIDTH, WINDOW_HEIGHT);

		enemySprite.Initialize(pRenderer);
		//heroSprite.Initialize(Sprite::LoadTexture(pRenderer, "Assets/Tex_Ant.bmp"));
		//heroSprite.m_Size = Vector2d(64, 64);

		heroSprite.Initialize(pRenderer);
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
		backgroundSprite.Update(deltaSeconds, worldState, playerState);
		enemySprite.Update(deltaSeconds, worldState, playerState);
		heroSprite.Update(deltaSeconds, worldState, playerState);
	}

	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState)
	{
		SDL_RenderClear(pRenderer);

		backgroundSprite.Render(pRenderer, worldState, playerState);

		enemySprite.Render(pRenderer, worldState, playerState);

		heroSprite.Render(pRenderer, worldState, playerState);

		SDL_RenderPresent(pRenderer);
	}

	void CleanupGame()
	{
		backgroundSprite.Cleanup();
		enemySprite.Cleanup();
		heroSprite.Cleanup();
		Sprite::ClearTextures();
	}
}