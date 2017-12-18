#pragma once
#include "SDL.h"
#include <vector>

namespace DungeonGame
{
	const float WINDOW_WIDTH = 1280.0f;
	const float WINDOW_HEIGHT = 720.0f;

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

	class PlayerState
	{
	public:
		void Initialize();
		void Reset();

		bool m_bHasFinishedGame;

		Vector2d m_CurrentPosition;
		Vector2d m_DesiredDirection;

	};

	class WorldState
	{
	public:
		void Initialize();
		void Reset();
	};

	void InitializeGame(SDL_Renderer* pRenderer, WorldState& worldState, PlayerState& playerState);
	void GetInput(const WorldState& worldState, PlayerState& playerState);
	void UpdateGame(float deltaSeconds, WorldState& worldState, PlayerState& playerState);
	void RenderGame(SDL_Renderer* pRenderer, const WorldState& worldState, const PlayerState& playerState);
	void CleanupGame();
}