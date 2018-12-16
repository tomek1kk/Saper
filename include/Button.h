#include "Pole.h"
class Button
{
    public:
        Button(int x, int y, int w, int h);
        void render(SDL_Renderer* rendi, SDL_Texture* texta);
        bool inButton(int x, int y);

    protected:

    private:
        int x, y, w ,h;
        SDL_Rect r;
};


