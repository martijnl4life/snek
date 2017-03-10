#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	enum class State
	{
		empty,
		obstacle,
		food,
		poison
	};
public:
	Board( Graphics& gfx );
	void Initboard(std::mt19937& rng, const class Snake& snake, int nFood, float percentagePoison);
	void DrawCell( const Location& loc,Color c );
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard( const Location& loc ) const;
	State GetLocState( const Location& loc ) const;
	void ClearLoc(const Location& loc);
	void SetLocState(const Location& loc, const State& state);
	void SpawnBlock( std::mt19937& rng,const class Snake& snake, const State& state);
	void DrawBorder();
	void DrawBoard();
private:
	static constexpr Color borderColor = Colors::Blue;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color foodColor = Colors::Green;
	static constexpr Color poisonColor = Colors::Magenta;
	static constexpr int dimension = 20;
	static constexpr int cellPadding = 1;
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 2;
	static constexpr int x = 70;
	static constexpr int y = 50;
	State LocStates[width * height] = {State::empty}; 
	Graphics& gfx;
};