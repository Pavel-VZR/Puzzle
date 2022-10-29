#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture.h"
#include "Square.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

//Инициализация SDL и создание окна
bool init(SDL_Window**, SDL_Renderer**);
void close(SDL_Window**, SDL_Renderer**);

int main(int argc, char** args)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture textTexture;


	if (init(&window, &renderer))
	{
		//Шрифт
		TTF_Font* font = nullptr;
		font = TTF_OpenFont("Font/BuyanBold.ttf", 72);
		if (font == nullptr)
			std::cerr<<"Failed to load font! SDL_ttf Error: "<<TTF_GetError();
		
		SDL_Color textColor = { 0, 0, 0 };
		textTexture.loadFromRenderedText(&renderer, "WIN!", font, textColor);


		//Устанавливает режим смешивания при работе с альфа каналом
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		SDL_Color black = { 0x00, 0x00, 0x00, 0xFF };
		SDL_Color white = { 0xFF, 0xFF, 0xFF, 0xFF };
		SDL_Color red = { 0xFF, 0x00, 0x00, OFF_SQUARE_ALPHA };
		SDL_Color green = { 0x00, 0xFF, 0x00, OFF_SQUARE_ALPHA };
		SDL_Color blue = { 0x00, 0x00, 0xFF, OFF_SQUARE_ALPHA };
		SDL_Color yellow = { 0xFF, 0xFF, 0x00, OFF_SQUARE_ALPHA };


		const int fieldSizeX = 5 * CONTROL_SQUARE_SIZE_X;		//500
		const int fieldSizeY = 5 * CONTROL_SQUARE_SIZE_Y;		//500

		//Массив игрового поля 
		int aPlayField[SQUARE_TOTAL][SQUARE_TOTAL] = {};
		//Расстановка неподвижный блоков
		aPlayField[1][0] = BLOCK_SQUARE;
		aPlayField[1][2] = BLOCK_SQUARE;
		aPlayField[1][4] = BLOCK_SQUARE;
		aPlayField[3][0] = BLOCK_SQUARE;
		aPlayField[3][2] = BLOCK_SQUARE;
		aPlayField[3][4] = BLOCK_SQUARE;

		//Координаты верхнего левого угла игрового поля
		int leftTopCornerPFX = (WINDOW_WIDTH - fieldSizeX) / 2;
		int leftTopCornerPFY = (WINDOW_HEIGHT - fieldSizeY) / 2;

		Square* aSquareField[SQUARE_TOTAL][SQUARE_TOTAL];
		for (int i = 0; i < SQUARE_TOTAL; i++)
			for (int j = 0; j < SQUARE_TOTAL; j++)
				aSquareField[i][j] = nullptr;

		aSquareField[0][0] = new Square(leftTopCornerPFX + 5, leftTopCornerPFY + 5, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		aSquareField[0][1] = new Square(leftTopCornerPFX + 5, leftTopCornerPFY + 105, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);
		aSquareField[0][2] = new Square(leftTopCornerPFX + 5, leftTopCornerPFY + 205, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);
		aSquareField[0][3] = new Square(leftTopCornerPFX + 5, leftTopCornerPFY + 305, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		aSquareField[0][4] = new Square(leftTopCornerPFX + 5, leftTopCornerPFY + 405, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);

		aSquareField[2][0] = new Square(leftTopCornerPFX + 205, leftTopCornerPFY + 5, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);
		aSquareField[2][1] = new Square(leftTopCornerPFX + 205, leftTopCornerPFY + 105, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);
		aSquareField[2][2] = new Square(leftTopCornerPFX + 205, leftTopCornerPFY + 205, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);
		aSquareField[2][3] = new Square(leftTopCornerPFX + 205, leftTopCornerPFY + 305, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		aSquareField[2][4] = new Square(leftTopCornerPFX + 205, leftTopCornerPFY + 405, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);

		aSquareField[4][0] = new Square(leftTopCornerPFX + 405, leftTopCornerPFY + 5, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		aSquareField[4][1] = new Square(leftTopCornerPFX + 405, leftTopCornerPFY + 105, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		aSquareField[4][2] = new Square(leftTopCornerPFX + 405, leftTopCornerPFY + 205, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);
		aSquareField[4][3] = new Square(leftTopCornerPFX + 405, leftTopCornerPFY + 305, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);
		aSquareField[4][4] = new Square(leftTopCornerPFX + 405, leftTopCornerPFY + 405, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);

		aPlayField[0][0] = GREEN_SQUARE;
		aPlayField[0][1] = RED_SQUARE;
		aPlayField[0][2] = YELLOW_SQUARE;
		aPlayField[0][3] = GREEN_SQUARE;
		aPlayField[0][4] = RED_SQUARE;

		aPlayField[2][0] = YELLOW_SQUARE;
		aPlayField[2][1] = YELLOW_SQUARE;
		aPlayField[2][2] = RED_SQUARE;
		aPlayField[2][3] = GREEN_SQUARE;
		aPlayField[2][4] = RED_SQUARE;

		aPlayField[4][0] = GREEN_SQUARE;
		aPlayField[4][1] = GREEN_SQUARE;
		aPlayField[4][2] = RED_SQUARE;
		aPlayField[4][3] = YELLOW_SQUARE;
		aPlayField[4][4] = YELLOW_SQUARE;

		//При помощи этого квадрата происходит перестановка фишек
		Square controlSquare(leftTopCornerPFX, leftTopCornerPFY, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &blue);
		//controlSquare Field Postion
		int CSqFieldPositionX = 0;
		int CSqFieldPositionY = 0;

		//Блоки
		Square* aBlockSquare[BLOCK_NUMBER];
		aBlockSquare[0] = new Square(leftTopCornerPFX + 100, leftTopCornerPFY, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);
		aBlockSquare[1] = new Square(leftTopCornerPFX + 100, leftTopCornerPFY + 200, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);
		aBlockSquare[2] = new Square(leftTopCornerPFX + 100, leftTopCornerPFY + 400, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);
		aBlockSquare[3] = new Square(leftTopCornerPFX + 300, leftTopCornerPFY, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);
		aBlockSquare[4] = new Square(leftTopCornerPFX + 300, leftTopCornerPFY + 200, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);
		aBlockSquare[5] = new Square(leftTopCornerPFX + 300, leftTopCornerPFY + 400, CONTROL_SQUARE_SIZE_X, CONTROL_SQUARE_SIZE_Y, &black);

		//Фишка под управляющим квадратом
		Square* squareOverCSq = nullptr;

		//Шапка с фишками над игровым полем
		Square redSquarePosition(leftTopCornerPFX + 5, leftTopCornerPFY - CONTROL_SQUARE_SIZE_Y, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &red);
		Square greenSquarePosition(leftTopCornerPFX + 205, leftTopCornerPFY - CONTROL_SQUARE_SIZE_Y, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &green);
		Square yellowSquarePosition(leftTopCornerPFX + 405, leftTopCornerPFY - CONTROL_SQUARE_SIZE_Y, PLAY_SQUARE_SIZE_X, PLAY_SQUARE_SIZE_Y, &yellow);


		bool quit = false;
		SDL_Event evt;

		while (!quit)
		{
			while (SDL_PollEvent(&evt))	//Взять событие из очереди
			{
				//Определение под каким квадратом находится управляющий квадрат
				squareOverCSq = aSquareField[CSqFieldPositionX][CSqFieldPositionY];
				//if (squareOverCSq)
				//	squareOverCSq->SetBlueOver(true);

				if (evt.type == SDL_QUIT)
				{
					quit = true;
				}
				else if (evt.type == SDL_KEYDOWN)
				{
					//Проверить все квадраты 
					switch (evt.key.keysym.sym)
					{
					case SDLK_UP:
						//Проверка условия "можно ли передвинуть управляющий квадрат"
						if (controlSquare.GetPositionY() - controlSquare.GetSquareHeight() >= leftTopCornerPFY &&
							aPlayField[CSqFieldPositionX][CSqFieldPositionY - 1] != 1)
						{
							//Если фишка выбрана, то управляющий квадрат может передвигаться только вместе с фишкой по свободым ячейкам
							if (squareOverCSq && squareOverCSq->GetSelect())
							{
								//Проверка свободня ли ячейка
								if (!aPlayField[CSqFieldPositionX][CSqFieldPositionY - 1])
								{
									//Передвинуть фишку
									squareOverCSq->SetPositionY(squareOverCSq->GetPositionY() - controlSquare.GetSquareHeight());
									//Изменить значения полей
									aPlayField[CSqFieldPositionX][CSqFieldPositionY - 1] = aPlayField[CSqFieldPositionX][CSqFieldPositionY];
									aPlayField[CSqFieldPositionX][CSqFieldPositionY] = EMPTY_SQUARE;
									aSquareField[CSqFieldPositionX][CSqFieldPositionY - 1] = aSquareField[CSqFieldPositionX][CSqFieldPositionY];
									aSquareField[CSqFieldPositionX][CSqFieldPositionY] = nullptr;
									//Передвинуть управляющий квадрат
									controlSquare.SetPositionY(controlSquare.GetPositionY() - controlSquare.GetSquareHeight());
									CSqFieldPositionY--;
								}
							}
							else
							{
								controlSquare.SetPositionY(controlSquare.GetPositionY() - controlSquare.GetSquareHeight());
								CSqFieldPositionY--;
							}

						}
						break;

					case SDLK_DOWN:
						if (controlSquare.GetPositionY() + controlSquare.GetSquareHeight() < leftTopCornerPFY + fieldSizeY &&
							aPlayField[CSqFieldPositionX][CSqFieldPositionY + 1] != 1)
						{
							if (squareOverCSq && squareOverCSq->GetSelect())
							{
								if (!aPlayField[CSqFieldPositionX][CSqFieldPositionY + 1])
								{
									squareOverCSq->SetPositionY(squareOverCSq->GetPositionY() + controlSquare.GetSquareHeight());

									aPlayField[CSqFieldPositionX][CSqFieldPositionY + 1] = aPlayField[CSqFieldPositionX][CSqFieldPositionY];
									aPlayField[CSqFieldPositionX][CSqFieldPositionY] = EMPTY_SQUARE;
									aSquareField[CSqFieldPositionX][CSqFieldPositionY + 1] = aSquareField[CSqFieldPositionX][CSqFieldPositionY];
									aSquareField[CSqFieldPositionX][CSqFieldPositionY] = nullptr;

									controlSquare.SetPositionY(controlSquare.GetPositionY() + controlSquare.GetSquareHeight());
									CSqFieldPositionY++;
								}
							}
							else
							{
								controlSquare.SetPositionY(controlSquare.GetPositionY() + controlSquare.GetSquareHeight());
								CSqFieldPositionY++;
							}

						}
						break;

					case SDLK_LEFT:
						if (controlSquare.GetPositionX() - controlSquare.GetSquareWidht() >= leftTopCornerPFX &&
							aPlayField[CSqFieldPositionX - 1][CSqFieldPositionY] != 1)
						{
							if (squareOverCSq && squareOverCSq->GetSelect())
							{
								if (!aPlayField[CSqFieldPositionX - 1][CSqFieldPositionY])
								{
									squareOverCSq->SetPositionX(squareOverCSq->GetPositionX() - controlSquare.GetSquareWidht());

									aPlayField[CSqFieldPositionX - 1][CSqFieldPositionY] = aPlayField[CSqFieldPositionX][CSqFieldPositionY];
									aPlayField[CSqFieldPositionX][CSqFieldPositionY] = EMPTY_SQUARE;
									aSquareField[CSqFieldPositionX - 1][CSqFieldPositionY] = aSquareField[CSqFieldPositionX][CSqFieldPositionY];
									aSquareField[CSqFieldPositionX][CSqFieldPositionY] = nullptr;

									controlSquare.SetPositionX(controlSquare.GetPositionX() - controlSquare.GetSquareWidht());
									CSqFieldPositionX--;
								}
							}
							else
							{
								controlSquare.SetPositionX(controlSquare.GetPositionX() - controlSquare.GetSquareWidht());
								CSqFieldPositionX--;
							}
						}
						break;

					case SDLK_RIGHT:
						if (controlSquare.GetPositionX() + controlSquare.GetSquareWidht() < leftTopCornerPFX + fieldSizeX &&
							aPlayField[CSqFieldPositionX + 1][CSqFieldPositionY] != 1)
						{
							if (squareOverCSq && squareOverCSq->GetSelect())
							{
								if (!aPlayField[CSqFieldPositionX + 1][CSqFieldPositionY])
								{
									squareOverCSq->SetPositionX(squareOverCSq->GetPositionX() + controlSquare.GetSquareWidht());

									aPlayField[CSqFieldPositionX + 1][CSqFieldPositionY] = aPlayField[CSqFieldPositionX][CSqFieldPositionY];
									aPlayField[CSqFieldPositionX][CSqFieldPositionY] = EMPTY_SQUARE;
									aSquareField[CSqFieldPositionX + 1][CSqFieldPositionY] = aSquareField[CSqFieldPositionX][CSqFieldPositionY];
									aSquareField[CSqFieldPositionX][CSqFieldPositionY] = nullptr;

									controlSquare.SetPositionX(controlSquare.GetPositionX() + controlSquare.GetSquareWidht());
									CSqFieldPositionX++;
								}
							}
							else
							{
								controlSquare.SetPositionX(controlSquare.GetPositionX() + controlSquare.GetSquareWidht());
								CSqFieldPositionX++;
							}
						}
						break;

						//Клавиша ENTER(ВВОД)
					case SDLK_RETURN:
						if (squareOverCSq)
						{
							bool bSquarePositionOnOff;
							if (squareOverCSq->GetSelect())
							{
								squareOverCSq->SetSelect(false);
								bSquarePositionOnOff = false;
							}
							else
							{
								squareOverCSq->SetSelect(true);
								bSquarePositionOnOff = true;
							}
							//Прикольно подсвечивает куда тащить)
							switch (aPlayField[CSqFieldPositionX][CSqFieldPositionY])
							{
							case RED_SQUARE:
								redSquarePosition.SetSelect(bSquarePositionOnOff);
								break;
							case GREEN_SQUARE:
								greenSquarePosition.SetSelect(bSquarePositionOnOff);
								break;
							case YELLOW_SQUARE:
								yellowSquarePosition.SetSelect(bSquarePositionOnOff);
								break;
							}
						}
						break;
					}
				}
			}


			SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
			//Заполняет экран последним установленным цветом 
			SDL_RenderClear(renderer);

			//Фон под игровым полем
			SDL_Rect fillRect = { leftTopCornerPFX, leftTopCornerPFY, fieldSizeX, fieldSizeY };
			SDL_SetRenderDrawColor(renderer, 0xC0, 0xC0, 0xC0, 0xFF);
			SDL_RenderFillRect(renderer, &fillRect);

			//Отрисовка блоков на поле
			for (int i = 0; i < BLOCK_NUMBER; i++)
				aBlockSquare[i]->RenderSquare(&renderer);

			//Отрисовка управляющего квадрата
			controlSquare.RenderSquare(&renderer);

			//Отрисовка фишек
			for (int i = 0; i < SQUARE_TOTAL; i++)
				for (int j = 0; j < SQUARE_TOTAL; j++)
					if (aSquareField[i][j])
						aSquareField[i][j]->RenderSquare(&renderer);

			//Отрисовка шапки сверху 
			redSquarePosition.RenderSquare(&renderer);
			greenSquarePosition.RenderSquare(&renderer);
			yellowSquarePosition.RenderSquare(&renderer);


			//Обновления экрана
			SDL_RenderPresent(renderer);

			//Условие победы 
			bool bWIN = true;
			for (int i = 0; i < SQUARE_TOTAL; i++)
			{
				if (aPlayField[0][i] != RED_SQUARE || aPlayField[2][i] != GREEN_SQUARE || aPlayField[4][i] != YELLOW_SQUARE)
				{
					bWIN = false;
					break;
				}
			}

			if (bWIN)
			{
				bool endMenuQuit = false;
				while (!endMenuQuit)
				{
					while (SDL_PollEvent(&evt))
					{
						if (evt.type == SDL_QUIT)
						{
							endMenuQuit = true;
							quit = true;
						}
					}

					SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
					SDL_RenderClear(renderer);

					textTexture.render(&renderer, 300, 300);
					SDL_RenderPresent(renderer);
				}
			}
		}
		for (int i = 0; i < BLOCK_SQUARE; i++)
			delete aBlockSquare[i];


		for (int i = 0; i < SQUARE_TOTAL; i++)
			for (int j = 0; j < SQUARE_TOTAL; j++)
				delete aSquareField[i][j];
	}


	close(&window, &renderer);
	return 0;
}

bool init(SDL_Window** win, SDL_Renderer** ren)
{
	bool flag = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)	//Инициализация SDL
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		flag = false;
	}
	else
	{
		//Создание окна SDL
		*win = SDL_CreateWindow("Puzzle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (*win == NULL)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError();
			flag = false;
		}
		else
		{

			if (TTF_Init() == -1)
			{
				std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError();
				return false;
			}


			*ren = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (*ren == NULL)
			{
				std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError();
				return false;
			}
		}
	}

	return flag;
}

void close(SDL_Window** win, SDL_Renderer** ren)
{
	SDL_DestroyRenderer(*ren);
	SDL_DestroyWindow(*win);
	*win = nullptr;
	*ren = nullptr;

	TTF_Quit();
	SDL_Quit();
}


