#include "Button.h"

// funkcje

SDL_Texture* loadTexture(string path);
void generuj(vector <Pole> &tab);
void generuj_bomby(vector <Pole> &tab, int level);
int ile_bomb_obok(vector <Pole> &tab, int i);
string inttostring(int x);
void render_text(vector <Pole> &tab);
void handleEvent(vector <Pole> &tab, bool *running, SDL_Event e, int x, int y);
void buttonHandleEvent(bool *running, bool *run_game, SDL_Event e, int x, int y, Button b);
void odslon(vector <Pole> &tab, int i);

// stale

const int WINDOW_WIDTH = 400;
const int WINDOW_HEIGHT = 450;
const int MARGINES = 50;
int POLE = 30;
int level = 0;
int POLA_X = WINDOW_WIDTH / POLE;
int POLA_Y = (WINDOW_HEIGHT - MARGINES) / POLE;
int LICZBA_POL = POLA_X * POLA_Y;
SDL_Window* okno = SDL_CreateWindow("Saper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
SDL_Renderer* rendi = SDL_CreateRenderer(okno, NULL, SDL_RENDERER_ACCELERATED);
SDL_Texture* pole_zakryte = loadTexture("hiden2.jpg");
SDL_Texture* pole_odkryte = loadTexture("hiden.jpg");
SDL_Texture* bomba = loadTexture("bomba.jpg");
SDL_Texture* nowa_gra_text = loadTexture("bomba.jpg");
SDL_Texture* pole_oznaczone = loadTexture("hiden3.jpg");
Button nowa_gra(WINDOW_WIDTH * 0.375, 0, WINDOW_WIDTH / 4, MARGINES);
Button zwieksz_pole(0, 0, WINDOW_WIDTH / 15, MARGINES / 2);
Button zmniejsz_pole(0, MARGINES / 2, WINDOW_WIDTH / 15, MARGINES / 2);
Button zmniejsz_level(WINDOW_WIDTH * 0.1875, MARGINES / 2, WINDOW_WIDTH / 15, MARGINES / 2);
Button zwieksz_level(WINDOW_WIDTH * 0.1875, 0, WINDOW_WIDTH / 15, MARGINES / 2);
SDL_Event e;


int main(int argc, char* argv[])
{
    TTF_Init();
    srand(time(NULL));
    bool running;
    bool run_game = true;
    int x, y;

    while (run_game == true)
    {
        vector <Pole> tab;
        POLA_X = WINDOW_WIDTH / POLE;
        POLA_Y = (WINDOW_HEIGHT - MARGINES) / POLE;
        LICZBA_POL = POLA_X * POLA_Y;
        generuj(tab);
        generuj_bomby(tab, level);
        running = true;

        while (running == true)
        {

            SDL_RenderClear(rendi);
            render_text(tab);
            nowa_gra.render(rendi, nowa_gra_text);
            zwieksz_pole.render(rendi, nowa_gra_text);
            zmniejsz_pole.render(rendi, nowa_gra_text);
            zwieksz_level.render(rendi, nowa_gra_text);
            zmniejsz_level.render(rendi, nowa_gra_text);
            SDL_RenderPresent(rendi);
            SDL_PollEvent(&e);
            if (e.type == SDL_QUIT)
            {
                run_game = false;
                running = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x, &y);

                if (nowa_gra.inButton(x, y) == true)
                    buttonHandleEvent(&running, &run_game, e, x, y, nowa_gra);
                else if (zwieksz_pole.inButton(x, y) == true)
                {
                    if (POLE < 42)
                    {
                        POLE = POLE + 3;
                        running = false;
                    }
                }
                 else if (zmniejsz_pole.inButton(x, y) == true)
                {
                    if (POLE > 10)
                    {
                        POLE = POLE - 3;
                        running = false;
                    }
                }
                else if (zmniejsz_level.inButton(x,y) == true)
                {
                    if (level > 0)
                    {
                        level--;
                        running = false;
                        SDL_Delay(1);
                    }
                }
                else if (zwieksz_level.inButton(x,y) == true)
                {
                    if (level < 2)
                    {
                        level++;
                        running = false;
                    }
                }
                else
                    handleEvent(tab, &running, e, x, y);

                SDL_Delay(50);
            }


        }
        tab.clear();
    }
    SDL_Quit();
    return 0;
}

SDL_Texture* loadTexture(string path)
{
    SDL_Surface* surf = IMG_Load(path.c_str());
    SDL_Texture* texta = SDL_CreateTextureFromSurface(rendi, surf);
    if (texta == NULL)
        cout << "Blad ladowania tekstury!" << endl;
    SDL_FreeSurface(surf);
    return texta;
}

void generuj(vector <Pole> &tab)
{
      for (int i = 0; i < POLA_X; i++)
    {
        for (int j = 0; j < POLA_Y; j++)
        {
        Pole p(POLE * (i % POLA_X), (j % POLA_Y) * POLE + MARGINES, POLE);
        tab.push_back(p);
        }
    }

}

void generuj_bomby(vector <Pole> &tab, int level)
{
        // iloœæ bomb
    int LICZBA_BOMB;
    if (level == 0)
        LICZBA_BOMB = LICZBA_POL * 0.14;
    else if (level ==  1)
        LICZBA_BOMB = LICZBA_POL * 0.21;
    else
        LICZBA_BOMB = LICZBA_POL * 0.36;

    // losowanie bomb
    int x;
    for (int i = 0; i < LICZBA_BOMB; i++)
    {

        do
        {
            x = rand() % LICZBA_POL;
        } while (tab[x].isBomb() == true);

    tab[x].addBomb();

    }
}

int ile_bomb_obok(vector <Pole> &tab, int i)
{
    int ilosc_bomb = 0;

    // LEWY GORNY
    if (i > POLA_X && i % POLA_X != 0)
        if (tab[i - POLA_X - 1].isBomb() == true)
            ilosc_bomb++;
    // GORNY
    if (i >= POLA_X)
        if (tab[i - POLA_X].isBomb() == true)
            ilosc_bomb++;
    // PRAWY GORNY
    if (i >= POLA_X && (i + 1) % POLA_X != 0)
        if (tab[i - POLA_X + 1].isBomb() == true)
            ilosc_bomb++;
    // LEWY
    if (i % POLA_X != 0)
        if (tab[i - 1].isBomb() == true)
            ilosc_bomb++;
    // PRAWY
    if ((i + 1) % POLA_X != 0)
        if (tab[i + 1].isBomb() == true)
            ilosc_bomb++;
    // LEWY DOLNY
    if ((i % POLA_X) != 0 && i + POLA_X < tab.size())
        if (tab[i + POLA_X - 1].isBomb() == true)
            ilosc_bomb++;
    // DOLNY
    if (i + POLA_X < tab.size())
        if (tab[i + POLA_X].isBomb() == true)
            ilosc_bomb++;
    // PRAWY DOLNY
    if (i + POLA_X < tab.size() && (i + 1) % POLA_X != 0)
        if (tab[i + POLA_X + 1].isBomb() == true)
            ilosc_bomb++;

    return ilosc_bomb;

}

string inttostring(int x)
{
    stringstream xx;
    string napis;
    xx << x;
    xx >> napis;
    return napis;
}

void render_text(vector <Pole> &tab)
{
    TTF_Font* czcionka = TTF_OpenFont("Lucida.ttf", POLE * 0.75);
        for (int i = 0; i < LICZBA_POL; i++)
        {
            if (tab[i].isVisible() == false)
            {
                if (tab[i].isMarked() == false)
                    tab[i].render(rendi, pole_zakryte, bomba);
                else
                    tab[i].render(rendi, pole_oznaczone, bomba);
            }
            else
                 tab[i].render(rendi, pole_odkryte, bomba);

           if (tab[i].isBomb() == false && ile_bomb_obok(tab, i) != 0 && tab[i].isVisible() == true)
           {
                SDL_Color kolor;

                switch(ile_bomb_obok(tab, i))
                {
                case 1:
                    kolor = {0, 0, 255, 255};
                    break;
                case 2:
                    kolor = {4, 180, 4, 255};
                    break;
                case 3:
                    kolor = {255, 0, 0, 255};
                    break;
                case 4:
                    kolor = {10, 10, 42, 255};
                    break;
                case 5:
                    kolor = {97, 11, 11, 255};
                    break;
                case 6:
                    kolor = {250, 130, 88, 255};
                    break;
                case 7:
                    kolor = {255, 255, 0, 255};
                    break;
                default:
                    kolor = {0, 0, 0, 255};
                    break;
                }
                tab[i].textRender(inttostring(ile_bomb_obok(tab, i)), kolor, rendi, czcionka);

           }
        }
}

void handleEvent(vector <Pole> &tab, bool *running, SDL_Event e, int x, int y)
{
            x = x / POLE;
            y = (y - MARGINES) / POLE;
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                if (tab[(POLA_X * x) + y].isMarked() == true)
                    tab[(POLA_X * x) + y].mark();
                else
                {
                    tab[(POLA_X * x) + y].click();
                    if (ile_bomb_obok(tab, (POLA_X * x) + y) == 0 && tab[(POLA_X * x) + y].isBomb() == false)
                        odslon(tab, (POLA_X * x) + y);
                    if (tab[(POLA_X * x) + y].isBomb() == true)
                    {
                        for (int i = 0; i < tab.size(); i++)
                            tab[i].click();
                    }
                }
            }
            else
                tab[(POLA_X * x) + y].mark();

}

void buttonHandleEvent(bool *running, bool *run_game, SDL_Event e, int x, int y, Button b)
{
            if (b.inButton(x, y) == true)
                *running = false;

}

void odslon(vector <Pole> &tab, int i)
{
    // LEWY GORNY
    if (i > POLA_X && i % POLA_X != 0)
    {
        if (tab[i - POLA_X - 1].isVisible() == false)
        {
            tab[i - POLA_X - 1].click();
            if (ile_bomb_obok(tab, i - POLA_X - 1) == 0)
                odslon(tab, i - POLA_X - 1);
        }
    }
    // GORNY
    if (i >= POLA_X)
    {

        if (tab[i - POLA_X].isVisible() == false)
        {
            tab[i - POLA_X].click();
            if (ile_bomb_obok(tab, i - POLA_X) == 0)
                odslon(tab, i - POLA_X);
        }
    }
    // PRAWY GORNY
    if (i >= POLA_X && (i + 1) % POLA_X != 0)
    {

        if (tab[i - POLA_X + 1].isVisible() == false)
        {
            tab[i - POLA_X + 1].click();
            if (ile_bomb_obok(tab, i - POLA_X + 1) == 0)
                odslon(tab, i - POLA_X + 1);
        }
    }
    // LEWY
    if (i % POLA_X != 0)
    {

        if (tab[i - 1].isVisible() == false)
        {
            tab[i - 1].click();
            if (ile_bomb_obok(tab, i - 1) == 0)
                odslon(tab, i - 1);
        }
    }
    // PRAWY
    if ((i + 1) % POLA_X != 0)
    {

        if (tab[i + 1].isVisible() == false)
        {
            tab[i + 1].click();
            if (ile_bomb_obok(tab, i + 1) == 0)
                odslon(tab, i + 1);
        }
    }
    // LEWY DOLNY
    if ((i % POLA_X) != 0 && i + POLA_X < tab.size())
    {

        if (tab[i + POLA_X - 1].isVisible() == false)
        {
            tab[i + POLA_X - 1].click();
            if (ile_bomb_obok(tab, i + POLA_X - 1) == 0)
                odslon(tab, i + POLA_X - 1);
        }
    }
    // DOLNY
    if (i + POLA_X < tab.size())
    {

        if (tab[i + POLA_X].isVisible() == false)
        {
            tab[i + POLA_X].click();
            if (ile_bomb_obok(tab, i + POLA_X) == 0)
                odslon(tab, i + POLA_X);
        }
    }
    // PRAWY DOLNY
    if (i + POLA_X < tab.size() && (i + 1) % POLA_X != 0)
    {

        if (tab[i + POLA_X + 1].isVisible() == false)
        {
            tab[i + POLA_X + 1].click();
            if (ile_bomb_obok(tab, i + POLA_X + 1) == 0)
                odslon(tab, i + POLA_X + 1);
        }
    }
}
