#include "Texture.h"

Texture::Texture()
{
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    free();
}

void Texture::free()
{
    if (mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(SDL_Renderer** rend, int x, int y)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    SDL_RenderCopy(*rend, mTexture, nullptr, &renderQuad);
}

bool Texture::loadFromRenderedText(SDL_Renderer** rend, const std::string& textureText, TTF_Font* fnt,  SDL_Color textColor)
{
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(fnt, textureText.c_str(), textColor);
    if (textSurface == nullptr)
    {
        std::cerr<< "Unable to render text surface! SDL_ttf Error: " << TTF_GetError();
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(*rend, textSurface);
        if (mTexture == nullptr)
        {
            std::cerr<<"Unable to create texture from rendered text! SDL Error: " << SDL_GetError();
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture != nullptr;
}