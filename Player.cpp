#include "Player.h"

Player::Player(double x,double y, double velocity,SDL_Renderer* renderer)
{
    this->x=x;
    this->y=y;
    this->renderer=renderer;
    this->velocity = velocity;

    int w,h;

    vector<SDL_Texture*>textures_up;
    textures_up.push_back(IMG_LoadTexture(renderer,"character/up/1.gif"));
    textures_up.push_back(IMG_LoadTexture(renderer,"character/up/2.gif"));

    vector<SDL_Texture*>textures_down;
    textures_down.push_back(IMG_LoadTexture(renderer,"character/down/1.gif"));
    textures_down.push_back(IMG_LoadTexture(renderer,"character/down/2.gif"));

    vector<SDL_Texture*>textures_left;
    textures_left.push_back(IMG_LoadTexture(renderer,"character/left/1.gif"));
    textures_left.push_back(IMG_LoadTexture(renderer,"character/left/2.gif"));

    vector<SDL_Texture*>textures_right;
    textures_right.push_back(IMG_LoadTexture(renderer,"character/right/1.gif"));
    textures_right.push_back(IMG_LoadTexture(renderer,"character/right/2.gif"));

    textures["up"]=textures_up;
    textures["down"]=textures_down;
    textures["left"]=textures_left;
    textures["right"]=textures_right;

    //SDL_QueryTexture(textures["up"][0], NULL, NULL, &w, &h);
    rect.x = 0;
    rect.y = 100;
    rect.w = 32;
    rect.h = 32;

    current_animation="down";
    current_animation_frame=0;
    frame=0;
    animation_frequency=30;
}

Player::~Player()
{
    //dtor
}

void Player::logic()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        rect.y-=velocity;
        current_animation="up";
        animationLogic();
    }
    if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        rect.y+=velocity;
        current_animation="down";
        animationLogic();
    }
    if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        rect.x+=velocity;
        current_animation="right";
        animationLogic();
    }
    if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        rect.x-=velocity;
        current_animation="left";
        animationLogic();
    }
    frame++;
}

void Player::draw()
{
    SDL_RenderCopy(renderer, textures[current_animation][current_animation_frame], NULL, &rect);
}

void Player::animationLogic()
{
    if(frame%animation_frequency==0)
    {
        current_animation_frame++;
        if(current_animation_frame >= textures[current_animation].size())
        {
           current_animation_frame=0;
        }
    }
}
