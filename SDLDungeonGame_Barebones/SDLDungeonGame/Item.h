#pragma once
#include "Sprite.h"

namespace DungeonGame
{
	class Item : public Sprite
	{
	public:
		void InitItem(SDL_Renderer* pRenderer, ItemData* pItemData);
		virtual void Update(float deltaSeconds, WorldState& worldState, PlayerState& playerState);

	private:
		ItemData* m_pItemData;
	};
}