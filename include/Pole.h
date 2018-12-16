#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <SDL_ttf.h>
#include <sstream>

using namespace std;

class Pole
{
    public:
        Pole(int x, int y, int a);
        void render(SDL_Renderer* rendi, SDL_Texture* texta, SDL_Texture* bomba);
        void addBomb();
        void click();
        bool isBomb();
        bool isVisible();
        void textRender(string text, SDL_Color kolor, SDL_Renderer* rendi, TTF_Font* czcionka);
        void disactive();
        bool isMarked();
        void mark();
        void changeMark();


    protected:

    private:
        bool bomb;
        int x, y, a;
        bool visible;
        SDL_Rect r;
        SDL_Event e;
        bool active;
        bool marked;

};


