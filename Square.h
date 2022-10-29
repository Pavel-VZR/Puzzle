#pragma once
#include <SDL.h>

//Число блоков
const int BLOCK_NUMBER = 6;

//Значения фишек на поле в массиве aPlayField
enum FIELD_SQUARE_CONSTANT
{
	EMPTY_SQUARE,
	BLOCK_SQUARE,
	RED_SQUARE,
	GREEN_SQUARE,
	YELLOW_SQUARE,
	SQUARE_TOTAL
};

//Значения альфы когда фишка выбрана и невыбрана
enum ONOFF_SQUARE_ALPHA_CONSTANT
{
	ON_SQUARE_ALPHA = 255,
	OFF_SQUARE_ALPHA = 155
};

//Размеры фишек и управляющего квадрата
enum SQUARE_SIZE_CONSTANT
{
	CONTROL_SQUARE_SIZE_X = 100,
	CONTROL_SQUARE_SIZE_Y = 100,
	PLAY_SQUARE_SIZE_X = 90,
	PLAY_SQUARE_SIZE_Y = 90
};

class Square
{
	bool mSelect = false;	//Синий квадрат снизу + был нажат enter 

	SDL_Rect* mSquare;
	SDL_Color* mSquareColor;

public:
	Square(int PositionX = 0, int PositionY = 0, int SizeX = 0, int SizeY = 0, SDL_Color* Color = nullptr);
	~Square();

	void SetSelect(bool select);
	bool GetSelect() { return mSelect; };

	void SetPositionX(int PositionX) { mSquare->x = PositionX; };
	void SetPositionY(int PositionY) { mSquare->y = PositionY; };
	int GetPositionX() { return mSquare->x; };
	int GetPositionY() { return mSquare->y; };

	int GetSquareHeight() { return mSquare->h; };
	int GetSquareWidht() { return mSquare->w; };

	void RenderSquare(SDL_Renderer**);
};
