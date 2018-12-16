#include "Button.h"

Button::Button(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    r = {x, y, w, h};
}
void Button::render(SDL_Renderer* rendi, SDL_Texture* texta)
{
    SDL_RenderCopy(rendi, texta, NULL, &r);
}

bool Button::inButton(int x, int y)
{
    if (x >= this->x && x <= this->x + w && y >= this->y && y <= this->y + h)
        return true;
    return false;
}
