#include "Square.h"

Square::Square(int PositionX, int PositionY, int SizeX, int SizeY, SDL_Color* Color) : mSquare(nullptr), mSquareColor(nullptr)
{
	mSquare = new SDL_Rect;
	mSquare->x = PositionX;
	mSquare->y = PositionY;
	mSquare->h = SizeX;
	mSquare->w = SizeY;

	mSquareColor = new SDL_Color;
	mSquareColor->r = Color->r;
	mSquareColor->g = Color->g;
	mSquareColor->b = Color->b;
	mSquareColor->a = Color->a;
}

Square::~Square()
{
	delete mSquare;
	delete mSquareColor;
}

void Square::SetSelect(bool select)
{
	mSelect = select;
	if (mSelect)
		mSquareColor->a = ON_SQUARE_ALPHA;
	else
		mSquareColor->a = OFF_SQUARE_ALPHA;
}

void Square::RenderSquare(SDL_Renderer** rend)
{
	SDL_SetRenderDrawColor(*rend, mSquareColor->r, mSquareColor->g, mSquareColor->b, mSquareColor->a);
	SDL_RenderFillRect(*rend, mSquare);
}
