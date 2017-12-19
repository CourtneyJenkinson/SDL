#pragma once
#include "SDL.h"
#include <vector>

namespace DungeonGame
{
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;

	const float TILE_SIZE_W = 64.0f;
	const float TILE_SIZE_H = 64.0f;

	struct BulletData;


	struct Vector2d
	{
		float X;
		float Y;

		Vector2d() :
			X(0.0f),
			Y(0.0f)
		{
		}

		Vector2d(float inX, float inY) :
			X(inX),
			Y(inY)
		{
		}

		bool operator==(const Vector2d& otherPosition) const
		{
			return X == otherPosition.X && Y == otherPosition.Y;
		}

		bool operator!=(const Vector2d& otherPosition) const
		{
			return !(*this == otherPosition);
		}

		Vector2d& operator+=(const Vector2d &rhs)
		{
			this->X += rhs.X;
			this->Y += rhs.Y;
			return *this;
		}

		const Vector2d operator+(const Vector2d &other) const
		{
			return Vector2d(*this) += other;
		}

		Vector2d& operator-=(const Vector2d &rhs)
		{
			this->X -= rhs.X;
			this->Y -= rhs.Y;
			return *this;
		}

		const Vector2d operator-(const Vector2d &other) const
		{
			return Vector2d(*this) -= other;
		}

		Vector2d& operator*=(float scalar)
		{
			this->X *= scalar;
			this->Y *= scalar;
			return *this;
		}

		const Vector2d operator*(float scalar) const
		{
			return Vector2d(*this) *= scalar;
		}

		float GetLength()
		{
			return sqrtf(X * X + Y * Y);
		}

		void Normalize()
		{
			float length = GetLength();
			if (length > 0.0f)
			{
				X = X / length;
				Y = Y / length;
			}
			else
			{
				X = 0.0f;
				Y = 0.0f;
			}
		}
	};

	enum ItemType
	{
		ITEM_Egg
	};

	struct ItemData
	{
		ItemType type;
		Vector2d position;
		bool bAlive;
	};

	struct EnemyData
	{
		Vector2d m_CurrentPosition;
		int EnemyHp;
		bool bAlive;

		//void hit by bullet
		void OnHitByBullet(BulletData* pBullet);
	};

	struct BulletData
	{
		Vector2d position;
		Vector2d direction;
		float bulletLifeTime;
		bool bAlive;
	};

	class PlayerState
	{
	public:
		void Initialize();
		void Reset();
		
		bool EnemyToPlayerCollision(EnemyData* enemySprite);

		bool ItemToPlayerCollision(ItemData* itemSprite);

		bool m_bHasFinishedGame;
		bool m_bWantsToShot;

		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;

		bool m_bAlive;
		int m_HP;

		std::vector<ItemType> m_Inventory;

		std::vector<BulletData> m_Bullet;

		float m_ShotCooldownSec;

	};

	class WorldState
	{
	public:
		void Initialize();
		void Reset();

		unsigned int GetTileTypeAtPosition(const Vector2d& inPosition);

		
		
		bool BulletCollWithItem(BulletData* pBullet);

		bool BulletCollWithEnemy(BulletData* pBullet);

		//tile setup
		unsigned int m_TilesPerRow;
		std::vector<unsigned int> m_Tiles;

		std::vector<ItemData> m_Item;
		std::vector<EnemyData> m_Enemy;
	};

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState);
	void GetInput(const WorldState& worldState, PlayerState& playerState);
	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState);
	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState);
	void CleanupGame();
}