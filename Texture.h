#pragma once
#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Texture
{
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;

public:
    Texture();
    ~Texture();

    void free();

    bool loadFromRenderedText(SDL_Renderer** rend, const std::string& textureText, TTF_Font* font, SDL_Color textColor);
    void render(SDL_Renderer** rend, int x, int y);
};