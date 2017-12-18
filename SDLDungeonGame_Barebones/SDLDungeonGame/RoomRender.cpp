#include "RoomRender.h"

using namespace DungeonGame;

void RoomRender::InitRoom(SDL_Renderer* pRenderer)
{
	m_pFloorTexture = LoadTexture(pRenderer, "Assets/Tex_Floor.bmp");
	m_pWallTexture = LoadTexture(pRenderer, "Assets/Tex_Wall.bmp");
}

void RoomRender::Render(SDL_Renderer *pRenderer, const WorldState& worldState, const PlayerState& playerState, const Vector2d& baseTransformation)
{
	const std::vector<unsigned int>& tiles = worldState.m_Tiles;
	int columnsRendered = 0;
	int rowsRendered = 0;

	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		unsigned int tileType = tiles[i]; 

		SDL_Texture* pCurrTexture = nullptr;

		switch (tileType)
		{
		case 1:
			pCurrTexture = m_pFloorTexture;
			break;
		case 2:
			pCurrTexture = m_pWallTexture;
			break;
		}

		if (pCurrTexture)
		{
			SDL_Rect destRect =
			{
				columnsRendered * 64,	//x
				rowsRendered * 64,	//y
				64,	//w
				64, 	//h
			};

			SDL_RenderCopy(pRenderer, pCurrTexture, nullptr, &destRect);
			
		}
		columnsRendered++;
		if (columnsRendered % worldState.m_TilesPerRow == 0)
		{
		rowsRendered++;
		columnsRendered = 0;
		}
	}
}
