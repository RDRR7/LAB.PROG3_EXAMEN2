#ifndef MENU_H
#define MENU_H

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include "juego.h"
#include "SDL_mixer.h"


using namespace std;

class MenuItem
{
public:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    SDL_Rect rect;
    string type;


    MenuItem(SDL_Renderer* renderer, int x, int y)
    {
        this->rect.x=x;
        this->rect.y=y;
        this->renderer=renderer;
        type="MenuItem";


    }

    void draw()
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
};

class MenuText : public MenuItem
{
public:
    MenuText(SDL_Renderer* renderer,string text, int x, int y):MenuItem(renderer,x,y)
    {
        SDL_Color textColor = { 0, 0, 0 };
        TTF_Font *gFont = TTF_OpenFont( "mi_font.ttf", 28 );

        SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface( textSurface );

        SDL_QueryTexture(texture, NULL, NULL, &(this->rect.w), &(this->rect.h));

        type="MenuText";
    }
};

class MenuImage : public MenuItem
{
public:
    MenuImage(SDL_Renderer* renderer, string path, int x, int y):MenuItem(renderer,x,y)
    {
        texture = IMG_LoadTexture(renderer, path.c_str());
        SDL_QueryTexture(texture, NULL, NULL, &(this->rect.w), &(this->rect.h));

        type="MenuImage";
    }
};

class MenuButton : public MenuItem
{
public:

    string text;

    MenuButton(SDL_Renderer* renderer,string text, int x, int y):MenuItem(renderer,x,y)
    {
        this->text=text;

        SDL_Color textColor = { 0, 0, 0 };
        TTF_Font *gFont = TTF_OpenFont( "mi_font.ttf", 28 );

        SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text.c_str(), textColor );
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface( textSurface );

        SDL_QueryTexture(texture, NULL, NULL, &(this->rect.w), &(this->rect.h));

        type="MenuButton";
    }

    void action()
    {
    }
};


class Menu
{
    public:
        SDL_Renderer *renderer;
        vector<MenuItem*>items;
        SDL_Texture* texture_test;
        Menu(SDL_Renderer *renderer,string path);
        void draw();
        void loop();
        virtual ~Menu();
    protected:
    private:
};

#endif // MENU_H
