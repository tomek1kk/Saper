#include "Pole.h"

Pole::Pole(int x, int y, int a)
{
    this->a = a;
    this->x = x;
    this->y = y;
    visible = false;
    bomb = false;
    r.x = x;
    r.y = y;
    r.h = a;
    r.w = a;
    active = true;
    marked = false;

}

void Pole::render(SDL_Renderer* rendi, SDL_Texture* texta, SDL_Texture* bomba)
{
    if (bomb == true && visible == true)
        SDL_RenderCopy(rendi, bomba, NULL, &r);
    else
        SDL_RenderCopy(rendi, texta, NULL, &r);
}

void Pole::addBomb()
{
    bomb = true;
}

void Pole::click()
{

    visible = true;

}
bool Pole::isBomb()
{
    return bomb;
}

void Pole::textRender(string text, SDL_Color kolor, SDL_Renderer* rendi, TTF_Font* czcionka)
{
    //TTF_Font* czcionka = TTF_OpenFont("Lucida.ttf", 30 * 0.75);
    SDL_Surface* textSurface = TTF_RenderText_Solid(czcionka, text.c_str(), kolor);
    SDL_Rect r1 = {x + (a / 3), y + 1, textSurface->w, textSurface->h};
    SDL_Texture* texta = SDL_CreateTextureFromSurface(rendi, textSurface);
    SDL_RenderCopy(rendi, texta, NULL, &r1);
    SDL_DestroyTexture(texta);
    SDL_FreeSurface(textSurface);
}

bool Pole::isVisible()
{
    return visible;
}

void Pole::disactive()
{
    active = false;
}

bool Pole::isMarked()
{
    return marked;
}

void Pole::mark()
{
    marked = true;
}

void Pole::changeMark()
{
    if (marked == true)
        marked = false;
    else
        marked = true;
}


