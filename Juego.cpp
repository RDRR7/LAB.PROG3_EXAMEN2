#include "Menu.h"
#include "juego.h"

bool Juego::start()
{
    int w=0,h=0;
    int enemiesKilled=0;
    int lifes=3;
    bool levelBool=true;
    Mix_Chunk *gWin = Mix_LoadWAV( "win.wav" );
    Mix_Chunk *gPew= Mix_LoadWAV( "pew.wav" );
    Mix_Chunk *gLose= Mix_LoadWAV( "lose.wav" );
    Mix_Chunk *gPunch= Mix_LoadWAV( "punch.wav" );

    background = IMG_LoadTexture(renderer,"fondo.png");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = w;
    rect_background.h = h;

    character = IMG_LoadTexture(renderer, "personaje.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 0;
    rect_character.y = 100;
    rect_character.w = w;
    rect_character.h = h;

    enemy = IMG_LoadTexture(renderer, "enemy.png");
    SDL_QueryTexture(enemy, NULL, NULL, &w, &h);
    rect_enemy.x = 0;
    rect_enemy.y = 100;
    rect_enemy.w = w;
    rect_enemy.h = h;

    list<Bullet*>bullets;
    list<Enemy*>enemies;
    int frame=0;
    bool repeat=true;

    double player_velocity=3;
    double last_frame_ticks=SDL_GetTicks();
    Player *player = new Player(30,30,1,renderer);

    while(repeat)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                //Menu *menu=new Menu(renderer,"menu/lose.txt");
                //menu->loop();
                changeScores(enemiesKilled);
                return false;
                //repeat=false;
            }
        }

        int mouse_x, mouse_y;
        SDL_GetMouseState( &mouse_x, &mouse_y );

        if(frame%30==0)
        {
            double dist_x = mouse_x - player->rect.x;
            double dist_y = player->rect.y - mouse_y;
            bullets.push_back(new Bullet(player->rect.x,player->rect.y,getAngle(dist_x,dist_y),8,renderer));
        }

        if(frame%100==0)
        {
            enemies.push_back(new Enemy(0,rand()%screen_height-rect_enemy.h,renderer));
        }

        SDL_RenderCopy(renderer, background, NULL, &rect_background);

        for(list<Bullet*>::iterator i=bullets.begin();
            i!=bullets.end();
            i++)
        {
            Bullet* bullet_actual = *i;

            bullet_actual->logic();
            bullet_actual->draw();

            if(isOutOfBounds(bullet_actual->x,bullet_actual->y))
            {
                list<Bullet*>::iterator to_erase=i;
                i--;
                bullets.erase(to_erase);
                delete bullet_actual;
            }
        }

        for(list<Enemy*>::iterator i=enemies.begin();
            i!=enemies.end();
            i++)
        {
            Enemy* current_enemy = *i;

            current_enemy->logic();
            current_enemy->draw();

            if(isOutOfBounds(current_enemy->x,current_enemy->y))
            {
                list<Enemy*>::iterator to_erase=i;
                i--;
                enemies.erase(to_erase);
                delete current_enemy;
            }
        }

        player->logic();
        player->draw();

        for(list<Enemy*>::iterator i=enemies.begin();
            i!=enemies.end();
            i++)
        {
            Enemy*current_enemy = *i;
            if(collisionCheck(player->rect, current_enemy->rect))
            {
                Mix_PlayChannel( -1, gPunch, 0 );
                lifes--;
                list<Enemy*>::iterator to_erase_enemy=i;
                i--;
                enemies.erase(to_erase_enemy);
                delete current_enemy;
                break;
            }
            for(list<Bullet*>::iterator j=bullets.begin();
                j!=bullets.end();
                j++)
            {
                Bullet*current_bullet = *j;
                if(collisionCheck(current_enemy->rect,current_bullet->rect))
                {
                    Mix_PlayChannel( -1, gPew, 0 );
                    enemiesKilled++;
                    list<Bullet*>::iterator to_erase=j;
                    j--;
                    bullets.erase(to_erase);
                    delete current_bullet;

                    list<Enemy*>::iterator to_erase_enemy=i;
                    i--;
                    enemies.erase(to_erase_enemy);
                    delete current_enemy;
                    break;
                }
            }
        }
        if(lifes==0)
        {
            //Menu *menu=new Menu(renderer,"menu/lose.txt");
            //menu->loop();
            Mix_PlayChannel( -1, gLose, 0 );
            changeScores(enemiesKilled);
            //repeat=false;
            return false;
        }
        if(enemiesKilled==10 && levelBool)
        {
            background = IMG_LoadTexture(renderer,"fondo_2.jpg");
            levelBool=false;
        }
        else if(enemiesKilled==20 && !levelBool)
        {
            background = IMG_LoadTexture(renderer,"fondo_3.png");
            levelBool=true;
        }
        else if(enemiesKilled==30)
        {
            //Menu *menu=new Menu(renderer,"menu/win.txt");
            //menu->loop();
            Mix_PlayChannel( -1, gWin, 0 );
            changeScores(enemiesKilled);
            //repeat=false;
            return true;
        }

        SDL_RenderPresent(renderer);
        double current_ticks = SDL_GetTicks();
        double ticks_diff = current_ticks-last_frame_ticks;
        double sleep_time = 17-ticks_diff;
        //cout<<ticks_diff<<","<<sleep_time<<endl;
        last_frame_ticks=SDL_GetTicks();
        if(sleep_time>0)
            SDL_Delay(sleep_time);

        frame++;
    }
}
