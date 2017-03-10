#include "Board.h"
#include "Snake.h"
#include <assert.h>

Board::Board( Graphics& gfx )
	:
	gfx( gfx )
{}

void Board::Initboard(std::mt19937& rng, const class Snake& snake, int nFood, float percentagePoison)
{
	assert(nFood >= 0);
	for (int i = 0; i < nFood; i++)
	{
		SpawnBlock(rng, snake, State::food);
	}
	assert(percentagePoison >= 0);
	for (int i = 0; i < int(width * height * percentagePoison); i++)
	{
		SpawnBlock(rng, snake, State::poison);
	}
}

void Board::DrawCell( const Location & loc,Color c )
{
	assert( loc.x >= 0 );
	assert( loc.x < width );
	assert( loc.y >= 0 );
	assert( loc.y < height );

	const int off_x = x + borderWidth + borderPadding;
	const int off_y = y + borderWidth + borderPadding;

	gfx.DrawRectDim( loc.x * dimension + off_x + cellPadding,loc.y * dimension + off_y + cellPadding,dimension - cellPadding * 2,dimension - cellPadding * 2,c );
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard( const Location & loc ) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

Board::State Board::GetLocState( const Location & loc ) const
{
	return LocStates[loc.y * width + loc.x];
}

void Board::ClearLoc(const Location & loc)
{
	LocStates[loc.y * width + loc.x] = State::empty;
}

void Board::SetLocState(const Location& loc,const State& state)
{
	LocStates[loc.y * width + loc.x] = state;
}

void Board::SpawnBlock( std::mt19937 & rng,const Snake& snake, const State& state)
{
	std::uniform_int_distribution<int> xDist( 0,GetGridWidth() - 1 );
	std::uniform_int_distribution<int> yDist( 0,GetGridHeight() - 1 );

	Location newLoc;
	do
	{
		newLoc.x = xDist( rng );
		newLoc.y = yDist( rng );
	}
	while( snake.IsInTile( newLoc ) || GetLocState(newLoc) == State::obstacle || GetLocState(newLoc) == State::food || GetLocState(newLoc) == State::poison );

	SetLocState(newLoc, state);
}

void Board::DrawBorder()
{
	const int top = y;
	const int left = x;
	const int bottom = top + (borderWidth + borderPadding) * 2 + height * dimension;
	const int right = left + (borderWidth + borderPadding) * 2 + width * dimension;

	// top
	gfx.DrawRect( left,top,right,top + borderWidth,borderColor );
	// left
	gfx.DrawRect( left,top + borderWidth,left + borderWidth,bottom - borderWidth,borderColor );
	// right
	gfx.DrawRect( right - borderWidth,top + borderWidth,right,bottom - borderWidth,borderColor );
	// bottom
	gfx.DrawRect( left,bottom - borderWidth,right,bottom,borderColor );
}

void Board::DrawBoard()
{
	for( int y = 0; y < height; y++ )
	{
		for( int x = 0; x < width; x++ )
		{
			switch (GetLocState({ x,y }))
			{
			case State::empty:
				break;
			case State::obstacle:
				DrawCell({ x,y }, obstacleColor);
				break;
			case State::food:
				DrawCell({ x,y }, foodColor);
				break;
			case State::poison:
				DrawCell({ x,y }, poisonColor);
				break;
			}
		}
	}
}
