#ifndef JUEGO_H
#define JUEGO_H

#include<iostream>
#include<list>
#include <stdlib.h>
#include <fstream>
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "SDL_mixer.h"

using namespace std;

class Juego
{
public:

Juego(SDL_Renderer* renderer)
{
    this->renderer=renderer;
}

SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character, *bullet, *enemy;
SDL_Rect rect_background,rect_character, rect_bullet, rect_enemy;

int screen_width = 500;
int screen_height= 250;

double getAngle(double distance_x, double distance_y)
{
    double angle = atan (distance_y/distance_x) * 180 / PI;
    if(distance_x<0)
    {
        angle=180+angle;
    }
    if(distance_x>0 && distance_y<0)
    {
        angle=360+angle;
    }
    return angle;
}

bool isOutOfBounds(int x, int y)
{
    return x>screen_width || x<0 || y>screen_height || y<0;
}

bool collisionCheck(SDL_Rect r1, SDL_Rect r2)
{
    if(r1.x > r2.x+r2.w)//Muy a la derecha
        return false;
    if(r1.x+r1.w < r2.x)//Muy a la izquierda
        return false;
    if(r1.y > r2.y+r2.h)//Muy abajo
        return false;
    if(r1.y+r1.h < r2.y)//Muy arriba
        return false;
    return true;
}

void changeScores(int score)
{
    string text[36];
    int points[4];
    points[3]=score;
    int z=0;
    ifstream in("menu/scores.txt");
    for(int x=0; x<36; x++)
    {
        if(x==17 || x==25 || x==33)
        {
            in>>points[z];
            z++;
        }
        else
            in>>text[x];
    }
    in.close();
    for(int x=0; x<4; x++)
        for(int y=x+1; y<4; y++)
            if(points[x]<points[y])
            {
                int tmp=points[x];
                points[x]=points[y];
                points[y]=tmp;
            }
    ofstream out("menu/scores.txt");
    z=0;
    for(int x=0; x<36; x++)
    {
        if(x==17 || x==25 || x==33)
        {
            out<<points[z];
            out<<" ";
            z++;
        }
        else
            out<<text[x]+" ";
    }
    out.close();
}

    bool start();
};

#endif // JUEGO_H
