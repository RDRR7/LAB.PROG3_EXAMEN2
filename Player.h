#ifndef PLAYER_H
#define PLAYER_H

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

class Player
{
    public:
        double x;
        double y;
        double velocity;
        map<string, vector<SDL_Texture*> > textures;
        SDL_Rect rect;
        SDL_Renderer *renderer;
        string current_animation;
        int current_animation_frame;
        int frame;
        int animation_frequency;
        Player(double x,double y, double velocity,SDL_Renderer* renderer);
        void logic();
        void draw();
        virtual ~Player();
        void animationLogic();
    protected:
    private:
};

#endif // PLAYER_H
