#include "SDL_mixer.h"
#include "Menu.h"



int main( int argc, char* args[] )
{
    SDL_Window* window;
    SDL_Renderer* renderer;//Hya q  ue mandarlo

    int screen_width = 500;
    int screen_height= 250;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        exit(0);
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, screen_width/*WIDTH*/, screen_height/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        exit(0);
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        exit(0);
    }

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

    SDL_Init( SDL_INIT_AUDIO );
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    Mix_Music *gMusic= Mix_LoadMUS( "unity.wav" );
    Mix_PlayMusic( gMusic, -1 );

    Menu menu(renderer,"menu/menu.txt");
    menu.loop();

    Mix_FreeMusic( gMusic ); gMusic = NULL;
    Mix_Quit(); IMG_Quit(); SDL_Quit();
	return 0;
}
