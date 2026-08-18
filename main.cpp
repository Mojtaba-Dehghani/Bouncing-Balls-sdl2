#include <iostream>
#include <cmath>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <bits/stdc++.h>
#include <SDL2/SDL_mixer.h>
#include "functions.h"
#include "bubble.h"
#include "entity.h"
#include "singletons.h"
#include "game.h"
#include "math.h"
#include "levelmanager.h"
#include "matchfinding.h"
#include "soundmanager.h"

using namespace std;
///////////////////////////leader board
struct User
{
    string name;
    int score;
};

vector<User> readUsers(const std::string& filename)
{
    vector<User> users;
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            if (!line.empty())
            {
                User user;
                size_t pos = line.find(' ');
                if (pos != std::string::npos)
                {
                    user.name = line.substr(0, pos);
                    user.score = std::stoi(line.substr(pos + 1));
                    users.push_back(user);
                }
            }
        }
        file.close();
    }
    return users;
}

bool compareUsers(const User& a, const User& b)
{
    return a.score > b.score;
}

void showLeaderboard(SDL_Renderer* renderer, const std::string& filename, TTF_Font* font, SDL_Color color)
{
    vector<User> users = readUsers(filename);
    sort(users.begin(), users.end(), compareUsers);
    int x = 100;
    int y = 100;
    int dy = 50;
    for (const User& user : users)
    {
        string text = user.name + " " + to_string(user.score);
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = surface->w;
        rect.h = surface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
//        SDL_DestroyTexture(texture);
        y += dy;
    }
}

SDL_Event* e = new SDL_Event();

////////////////////////
SDL_Texture* wall_img_day = NULL;
SDL_Texture* wall_img_night = NULL;
SDL_Texture* logo_asli_png = NULL;
SDL_Texture* theme_dokme_png= NULL;
SDL_Texture* regidter_dokme_png = NULL;
SDL_Texture*  leader_board_png= NULL;
SDL_Texture*  wall_img_day_blur= NULL;
SDL_Texture*  wall_img_night_blur= NULL;
SDL_Texture*  setting_window_png =NULL;
SDL_Texture*  exit_dokme_png= NULL;
SDL_Texture*  game_bg= NULL;
SDL_Texture*  thunder_png= NULL;

SDL_Texture* blur_day_version_jpg= NULL;
SDL_Texture* blur_night_version_jpg = NULL;
SDL_Texture* login_img = NULL;
SDL_Texture* mute_dokme_png = NULL;
SDL_Texture* unmute_dokme_png = NULL;
SDL_Texture* quit_dokme_png = NULL;
SDL_Texture* time_mode_dokme_png = NULL;
SDL_Texture* cheat_png = NULL;

SDL_Texture* normal_mode_dokme_png = NULL;
SDL_Texture* setting_dokme_png = NULL;
SDL_Texture* music_dokme_png = NULL;
SDL_Texture* pause_dokme_png = NULL;
SDL_Texture* start_dokme_png = NULL;
SDL_Texture* canon = NULL;
SDL_Texture* help_img = NULL;
SDL_Texture* settingwood_img = NULL;
SDL_Texture*  full_music_dokme_png= NULL;
SDL_Texture*  half_music_dokme_png= NULL;
SDL_Texture*  zero_music_dokme_png= NULL;

/////////////////
SDL_Rect setting_dokme_rect;
SDL_Rect thunder_rect;

SDL_Rect music_dokme_rect;
SDL_Rect quit_dokme_rect;
SDL_Rect mute_dokme_rect;
SDL_Rect exit_bazi_dokme_rect;
SDL_Rect full_music_dokme_rect;
SDL_Rect half_music_dokme_rect;
SDL_Rect canon_rect;
SDL_Rect zero_music_dokme_rect;
SDL_Rect normal_mode_dokme_rect;
SDL_Rect time_mode_dokme_rect;
SDL_Rect unmute_dokme_rect;
SDL_Rect theme_dokme_rect;
SDL_Rect leader_board_rect;
SDL_Rect regidter_dokme_rect;
SDL_Rect setting_window_rect;
SDL_Rect game_bg_rect;
SDL_Rect blur_day_version_rect;
SDL_Rect blur_night_version_rect;
SDL_Rect  exit_dokme_rect;
//SDL_Rect rect home;
//SDL_Rect rect map1;
//SDL_Rect rect map2;
//SDL_Rect rect map3;
//SDL_Rect rect score board;
SDL_Rect pause_dokme_rect;
SDL_Rect cheat_rect;
SDL_Rect play_dokme_rect;
SDL_Rect start_dokme_rect;
//SDL_Rect rect canon badan ezafe mishavad;
SDL_Rect logo_asli_rect;
SDL_Rect wall_rect_day;
SDL_Rect wall_rect_night;


void canon_pain();

SDL_Window* m_window;
SDL_Renderer* m_renderer;
int  mogh_x, mogh_y,volume=2;
bool khoroj , exite = 0 , exit_setting =0;
bool setting= false, game_run =false, menu_run_beshe =false, register_menu=false,normal=true,music_change=false;


const int IMAGE_WIDTH = 100;
const int IMAGE_HEIGHT = 50;

const SDL_Color BLACK = {0, 0, 0, 255};

Mix_Music *bg_sound = NULL;

class d_or_night;


int main(int argc, char* argv[])
{
    ///////////////////////////
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);

    bg_sound = Mix_LoadMUS("paszamine.mp3");
    //////////////////////////
    Mix_PlayMusic(bg_sound, 0);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    srand(time(NULL));
    Uint32 WND_flags = SDL_WINDOW_SHOWN;//SDL_WINDOW_BORDERLESS ;
    SDL_Init(SDL_flags);
    SDL_CreateWindowAndRenderer(1280, 800, WND_flags, &m_window, &m_renderer);
    SDL_RaiseWindow(m_window);
    /** rez safe ro begirim  ke niazi ham nist chon  dasti midim **/
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int W = DM.w;
    int H = DM.h;
    ////////////////////////////////////////////////////////////////
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_RenderPresent(m_renderer);
    /** inja bayad texture add konim  va ax hashon ro link konim **/

    wall_img_day = IMG_LoadTexture(m_renderer, "day_version_blego.jpg");

    wall_img_night = IMG_LoadTexture(m_renderer, "night_version_blego.jpg");

    logo_asli_png = IMG_LoadTexture(m_renderer, "logo_asli.png");

    start_dokme_png = IMG_LoadTexture(m_renderer, "start_dokme.png");

    mute_dokme_png = IMG_LoadTexture(m_renderer, "mute_dokme.png");

    unmute_dokme_png = IMG_LoadTexture(m_renderer, "unmute_dokme.png");

    quit_dokme_png = IMG_LoadTexture(m_renderer, "quit_dokme.png");

    pause_dokme_png= IMG_LoadTexture(m_renderer,"pause_dokme.png");

    setting_dokme_png = IMG_LoadTexture(m_renderer, "setting_dokme.png");
    thunder_png = IMG_LoadTexture(m_renderer, "thunder.png");


    music_dokme_png = IMG_LoadTexture(m_renderer, "music_dokme.png");

    setting_dokme_png = IMG_LoadTexture(m_renderer, "setting_dokme.png");

    canon = IMG_LoadTexture(m_renderer, "canon.png");

    cheat_png = IMG_LoadTexture(m_renderer, "cheat.png");


    theme_dokme_png = IMG_LoadTexture(m_renderer, "theme_dokme.png");

    leader_board_png = IMG_LoadTexture(m_renderer, "leader_board.png");

    regidter_dokme_png = IMG_LoadTexture(m_renderer, "register_dokme.png");

    setting_window_png = IMG_LoadTexture(m_renderer, "test_1.png");

    game_bg = IMG_LoadTexture(m_renderer, "test_2.jpg");

    normal_mode_dokme_png = IMG_LoadTexture(m_renderer, "normal_mode_dokme.png");

    time_mode_dokme_png = IMG_LoadTexture(m_renderer, "time_mode_dokme.png");

    exit_dokme_png = IMG_LoadTexture(m_renderer, "exit_dokme.png");

    full_music_dokme_png= IMG_LoadTexture(m_renderer, "full_music_dokme.png");

    half_music_dokme_png = IMG_LoadTexture(m_renderer, "half_music_dokme.png");

    zero_music_dokme_png = IMG_LoadTexture(m_renderer, "zero_music_dokme.png");

    blur_day_version_jpg = IMG_LoadTexture(m_renderer, "blur_day_version.jpg");

    blur_night_version_jpg = IMG_LoadTexture(m_renderer, "blur_night_version.jpg");
    /** safe menu baz mishe **/
    ///////////////////////////
    ///////////////////////////

    e->type = 0;

    bool mode = true;
    while (true) {
        if (e->type == SDL_QUIT) {
            SDL_DestroyTexture(wall_img_day);
            SDL_DestroyTexture(wall_img_night);
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
            IMG_Quit();
            SDL_Quit();
        }
        SDL_PollEvent(e);
        menu(m_renderer,mode);
        SDL_ShowCursor(SDL_ENABLE);
        mogh_x = e->button.x;
        mogh_y = e->button.y;


        /** shoro if ha va ezafe kardan ghesmat haye mokhtalef **/


        if( (is_clicked( mogh_x ,mogh_y,70, 340, 150, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        {
                mode=!mode;
                menu(m_renderer, mode);
//            Leaderboard leaderboard;
//            leaderboard.run();
            SDL_RenderPresent(m_renderer);
        }

        if((is_clicked( mogh_x ,mogh_y,70, 100, 150, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        {
            e ->type = 0 ;
            exite = 1;
        }
        if((is_clicked( mogh_x ,mogh_y,70, 220, 150, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        {
            setting = 1;
            e->type = 0 ;
            SDL_RenderClear(m_renderer);
            setting_ma(m_renderer,mode);
            SDL_RenderPresent(m_renderer);


        }

        if((is_clicked( mogh_x ,mogh_y,520, 390, 240, 300)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        {
            menu_run_beshe=true;
            e->type = 0 ;
            SDL_RenderClear(m_renderer);
            menu_run(m_renderer , mode);
            SDL_RenderPresent(m_renderer);

        }

        while(menu_run_beshe){
            menu_run_actions(m_renderer);
            while (game_run){

                Game game = Game("Bouncing Balls", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);
                game.Play();
                game_run=false;

            }
            exite = 1;


        }
        while (setting)
        {
            setting_ma_actions(m_renderer);
            if (volume==0)
                Mix_VolumeMusic(0);
            else if (volume ==1)
                Mix_VolumeMusic(30);
            else if (volume ==2)
                Mix_VolumeMusic(128);
            SDL_RenderPresent(m_renderer);

        }
        if(exite == 1)
            break;
        e->type = 0;

    }


    /** akhar kar bayad inja bashe  va az ghesmat dstroy dar tabe hamon bayad estefade bokonim **/
/**    SDL_DestroyTexture(m_img); **/
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
void draw(SDL_Renderer* m_renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h) {
    img_rect.x = x;
    img_rect.y = y;
    img_rect.w = w;
    img_rect.h = h;
    SDL_RenderCopy(m_renderer, m_img, NULL, &img_rect);

}
void menu( SDL_Renderer* m_renderer,bool d_or_night)
{
    SDL_RenderClear(m_renderer);
    if(d_or_night)
        draw(m_renderer, wall_img_day, wall_rect_day, 0, 0, 1280, 800);
    else
        draw(m_renderer, wall_img_night, wall_rect_night, 0, 0, 1280, 800);

    draw(m_renderer, logo_asli_png, logo_asli_rect, 430, 80, 450, 380);
    draw(m_renderer, start_dokme_png, start_dokme_rect, 520, 390, 240, 300);
    draw(m_renderer, quit_dokme_png, quit_dokme_rect, 70, 100, 150, 240);
    draw(m_renderer, setting_dokme_png, setting_dokme_rect, 70, 220, 150, 240);
    draw(m_renderer, theme_dokme_png, theme_dokme_rect, 70, 340, 150, 240);
    showLeaderboard(m_renderer, "user.txt", (TTF_Font *) "arial.ttf", BLACK);

    SDL_RenderPresent(m_renderer);

    SDL_Delay(50);
}
void setting_ma_actions(SDL_Renderer* m_renderer){
    SDL_PollEvent(e);
//    SDL_ShowCursor(SDL_ENABLE);
    mogh_x = e->button.x;
    mogh_y= e->button.y;
//    SDL_Delay(50);
    if((is_clicked( mogh_x ,mogh_y,70, 100, 150, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        setting=0;
    if((is_clicked( mogh_x ,mogh_y,95, 630, 70, 150)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        Mix_VolumeMusic(0);
    if((is_clicked( mogh_x ,mogh_y,95, 560, 70, 150)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        Mix_VolumeMusic(128);
    if((is_clicked( mogh_x ,mogh_y,505, 210, 100, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        volume=0;
        draw(m_renderer,zero_music_dokme_png,zero_music_dokme_rect,505, 210, 295, 240);
    }
    if((is_clicked( mogh_x ,mogh_y,605, 210, 100, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        volume=1;
        draw(m_renderer,half_music_dokme_png,half_music_dokme_rect,505, 210, 295, 240);
    }
    if((is_clicked( mogh_x ,mogh_y,705, 210, 95, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        volume=2;
        draw(m_renderer,full_music_dokme_png,full_music_dokme_rect,505, 210, 295, 240);
    }

    e->type = 0 ;



}

void setting_ma(SDL_Renderer* m_renderer ,bool mode){

    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mogh_x = e->button.x;
    mogh_y= e->button.y;
    SDL_RenderClear(m_renderer);

    if (mode==0)
        draw(m_renderer,blur_night_version_jpg,blur_night_version_rect,0,0,1280,800);
    else
        draw(m_renderer,blur_day_version_jpg,blur_day_version_rect,0,0,1280,800);
    draw(m_renderer,setting_window_png,setting_window_rect,0,-100,1300,1000);
    draw(m_renderer,unmute_dokme_png,unmute_dokme_rect,95, 560, 70, 150);
    draw(m_renderer,mute_dokme_png,mute_dokme_rect,95, 630, 70, 150);
    draw(m_renderer,full_music_dokme_png,full_music_dokme_rect,505, 210, 295, 240);
    draw(m_renderer, setting_dokme_png, setting_dokme_rect, 577, 30, 150, 240);
    draw(m_renderer, music_dokme_png, music_dokme_rect, 530, 460, 250, 80);
    draw(m_renderer, exit_dokme_png, exit_dokme_rect, 70, 100, 150, 240);
    if((is_clicked( mogh_x ,mogh_y,530, 460, 250, 80)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        music_change=!music_change;
    if(music_change){
        bg_sound = Mix_LoadMUS("paszamine2.mp3");
        Mix_PlayMusic(bg_sound, 0);

    }else{
        bg_sound = Mix_LoadMUS("paszamine1.mp3");
        Mix_PlayMusic(bg_sound, 0);


    }
    SDL_Delay(50);



    e ->type = 0 ;

}

void menu_run_actions(SDL_Renderer* m_renderer){
    SDL_PollEvent(e);
    mogh_x = e->button.x;
    mogh_y= e->button.y;
    SDL_Delay(50);
    if((is_clicked( mogh_x ,mogh_y,380, 400, 180, 80)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        game_run=true;
        normal=false;
    }
    if((is_clicked( mogh_x ,mogh_y,570, 300, 180, 80)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN)){
        game_run=true;
        normal=true;}
    if((is_clicked( mogh_x ,mogh_y,70, 100, 150, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        menu_run_beshe = false;
    if((is_clicked( mogh_x ,mogh_y,760, 320, 180, 240)) && (e->button.button == SDL_BUTTON_LEFT && e->type == SDL_MOUSEBUTTONDOWN))
        register_menu = true;








}
void menu_run(SDL_Renderer* m_renderer ,bool mode){

    SDL_PollEvent(e);
    SDL_ShowCursor(SDL_ENABLE);
    mogh_x = e->button.x;
    mogh_y= e->button.y;
    SDL_RenderClear(m_renderer);

    if (mode==0)
        draw(m_renderer,blur_night_version_jpg,blur_night_version_rect,0,0,1280,800);
    else
        draw(m_renderer,blur_day_version_jpg,blur_day_version_rect,0,0,1280,800);
    draw(m_renderer,setting_window_png,setting_window_rect,0,-100,1300,1000);
    draw(m_renderer, normal_mode_dokme_png, normal_mode_dokme_rect, 570, 300, 180, 80);
    draw(m_renderer, time_mode_dokme_png, time_mode_dokme_rect, 380, 400, 180, 80);
    draw(m_renderer, exit_dokme_png, exit_dokme_rect, 70, 100, 150, 240);
    draw(m_renderer, regidter_dokme_png, regidter_dokme_rect, 760, 320, 180, 240);




    SDL_Delay(50);


    e ->type = 0 ;

}

bool is_clicked(int x1,int y1,int x,int y,int w,int h){

    h/=3;
    y=y+h;

    if((x1>x)&&(x1<x+w)&&(y1>y)&&(y1<y+h))
        return true;
    else
        return false;
}


void draw_rect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    GUIManager::getInstance()->SetRenderer(renderer);
}



void draw_image(SDL_Renderer* renderer, SDL_Texture* texture, double angle) {
    int x = (WINDOW_WIDTH - IMAGE_WIDTH) / 2;
    int y = WINDOW_HEIGHT - IMAGE_HEIGHT;
    SDL_Rect rect = {x, y, IMAGE_WIDTH, IMAGE_HEIGHT};
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle * 180 / M_PI, NULL, SDL_FLIP_NONE);
    GUIManager::getInstance()->SetRenderer(renderer);
}
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h)
{
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("arial.ttf", 24);
    if (font == NULL)
    {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        return;
    }
    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        cout << "Failed to create text surface: " << TTF_GetError() << endl;
        return;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        cout << "Failed to create text texture: " << SDL_GetError() << endl;
        return;
    }
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
//    TTF_CloseFont(font);
}
void user_input()
{
    SDL_Window* window = SDL_CreateWindow("User Input", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_StartTextInput();
    bool ejra = true;
    string input = "";
    while (ejra)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                ejra = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    if (!input.empty())
                    {
                        ofstream file(input + ".txt");
                        if (file.is_open())
                        {
                            file << input << endl;
                            file.close();
                            ejra = false;
                        }

                    }
                }
                if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (!input.empty())
                    {
                        input.pop_back();
                    }
                }
            }
            if (event.type == SDL_TEXTINPUT)
            {
                input += event.text.text;
            }
        }

        SDL_RenderClear(m_renderer);

        renderText(m_renderer, "Please enter your name:", 100, 100,400,100);

        renderText(m_renderer, input.c_str(), 100, 200, 400, 100);

        renderText(m_renderer, "Press enter to save your name in a txt file and close the window.", 100, 300, 400, 100);

        SDL_RenderPresent(m_renderer);
    }
    SDL_StopTextInput();
    register_menu = false ;
    ejra=false;
    SDL_DestroyWindow(window);

}


SoundManager* SoundManager::instance = nullptr;

SoundManager::SoundManager()
{
    Load("assets_sounds_shoot_bubble.wav", SOUND_SHOOT_BUBBLE);
    Load("assets_sounds_failed_shot.wav", SOUND_FAILED_SHOT);
    Load("assets_sounds_combo.wav", SOUND_COMBO);
    Load("assets_sounds_combo_bonus1.wav", SOUND_COMBO_BONUS1);
    Load("assets_sounds_combo_bonus2.wav", SOUND_COMBO_BONUS2);
    Load("assets_sounds_fully_loaded.wav", SOUND_FULLY_LOADED);
    Load("assets_sounds_hit_wall.wav", SOUND_HIT_WALL);
    Load("assets_sounds_level_up.wav", SOUND_LEVEL_UP);
    Load("assets_sounds_reset_bonus.wav", SOUND_RESET_BONUS);
}

void SoundManager::Load(const char *filename, SoundType soundType)
{
    if(SDL_LoadWAV(filename, &wavSpec[soundType], &wavBuffer[soundType], &wavLength[soundType]) == nullptr)
    {
        printf("Error loading file %s: %s", filename, SDL_GetError());
        exit(EXIT_FAILURE);
    }
    deviceId[soundType] = SDL_OpenAudioDevice(nullptr, 0, &wavSpec[soundType], nullptr, 0);
}

 void SoundManager::PlaySound(SoundType soundType)
{
    SDL_QueueAudio(deviceId[soundType], wavBuffer[soundType], wavLength[soundType]);
    SDL_PauseAudioDevice(deviceId[soundType], 0);
}

SoundManager::~SoundManager()
{
    for(long long int j = 0; j < NUM_SOUNDS; j++)
    {
        SDL_CloseAudioDevice(deviceId[j]);
        SDL_FreeWAV(wavBuffer[j]);
    }
}

SoundManager* SoundManager::getInstance()
{
    if(instance == nullptr)
        instance = new SoundManager;
    return instance;
}

FontRenderer* FontRenderer::instance = nullptr;
FontRenderer::FontRenderer()
{
    if(TTF_Init() == -1)
    {
        fprintf(stderr,"Could not initialize TTF library: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    font = TTF_OpenFont("Sans.ttf", 36);
    if(font == nullptr)
    {
        fprintf(stderr, "Loading font failed: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

FontRenderer::~FontRenderer()
{
    TTF_CloseFont(font);
    TTF_Quit();
    instance = nullptr;
}

FontRenderer* FontRenderer::getInstance()
{
    if(!instance)
        instance = new FontRenderer;
    return instance;
}

void FontRenderer::DisplayText(const char *msg, int x, int y)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Color color = {.r = 0, .g = 0, .b = 0, .a = SDL_ALPHA_OPAQUE};
    SDL_Rect rect;

    surface = TTF_RenderText_Solid(font, msg, color);
    texture = SDL_CreateTextureFromSurface(GUIManager::getInstance()->GetRenderer(), surface);

    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(GUIManager::getInstance()->GetRenderer(), texture, nullptr, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


TextureManager* TextureManager::instance = nullptr;
TextureManager::TextureManager()
{
    background = CreateTextureFromImage("test_2.jfif");
    char bubbleColors[NUM_BUBBLES][16] = {"blue", "yellow", "green", "red", "transparent"};
    for(long long int k = 0; k < NUM_BUBBLES; k++)
    {
        char path[64];
        sprintf(path, "bubble_%s.png", bubbleColors[k]);
        bubbles[k] = CreateTextureFromImage(path);
    }
}

TextureManager::~TextureManager()
{
    if(background)
        SDL_DestroyTexture(background);
    for(auto & bubble : bubbles)
    {
        if(bubble)
            SDL_DestroyTexture(bubble);
    }
    instance = nullptr;
}

TextureManager* TextureManager::getInstance()
{
    if(!instance)
        instance = new TextureManager;
    return instance;
}

SDL_Texture* TextureManager::CreateTextureFromImage(const char *path)
{
    SDL_Surface *surface;
    SDL_Texture *texture;
    surface = IMG_Load(path);
    if(surface == nullptr)
    {
        fprintf(stderr, "File %s not found\n", path);
        exit(EXIT_FAILURE);
    }
    texture = SDL_CreateTextureFromSurface(GUIManager::getInstance()->GetRenderer(), surface);
    SDL_FreeSurface(surface);
    return texture;
}

GUIManager* GUIManager::instance = nullptr;
GUIManager* GUIManager::getInstance()
{
    if(instance == nullptr)
        instance = new GUIManager;
    return instance;
}
/////////////////////////////////////////// ina kheili dar renderer moheman ////////////////////////////////////////////////////

GUIManager::GUIManager()
{
    window = nullptr;
    renderer = nullptr;
}

GUIManager::~GUIManager()
{
//    SDL_DestroyWindow(window);
//    SDL_DestroyRenderer(renderer);
    instance = nullptr;
}

Matchfinder* Matchfinder::instance = nullptr;
Matchfinder* Matchfinder::getInstance()
{
    if(!instance)
        instance = new Matchfinder;
    return instance;
}

Matchfinder::Matchfinder()
{
    numBubbles = 0;
    memset(graph, 0, NUM_NODES*NUM_NODES*sizeof(int8_t));
    memset(matrix,0, BOARD_SIZE_X*BOARD_SIZE_Y*sizeof(int8_t));
}

Matchfinder::~Matchfinder()
{
    instance = nullptr;
}

bool Matchfinder::BoardContains(BubbleColor bubbleColor)
{
    for(auto & o : matrix)
        for(signed char j : o)
            if(j == (int8_t) bubbleColor)
                return true;
    return false;
}
void Matchfinder::SetMatrix(int i, int j, BubbleColor bubbleColor)
{
    matrix[i][j] = (int8_t) bubbleColor;
    if(bubbleColor != BUBBLE_NONE && bubbleColor != BUBBLE_TRANSPARENT)
        numBubbles++;
}

//int8_t Matchfinder::GetMatrix(int i, int j)
//{
//    return matrix[i][j];
//}

bool Matchfinder::PathContains(vector<Path*> &p, int x, int y)
{
    for (auto &i: p)
        if ( i-> x == x && i->y == y)
            return true;
    return false;
}

bool Matchfinder::IsIsolated(int x, int y)
{
    long long int num_visited = 0;
    bool containsTransparent = false;
    vector< Path* > tempPath;
    tempPath.push_back(new Path(x, y, false));
    while(tempPath.size() > num_visited && !containsTransparent)
    {
        size_t size = tempPath.size();
        for(int i = 0; i < tempPath.size(); i++)
        {
            if(containsTransparent)
                break;
            if(tempPath[i]->visited)
                continue;
            x = tempPath[i]->x;
            y = tempPath[i]->y;
            tempPath[i]->visited = true;
            num_visited++;

            if (y+1 < BOARD_SIZE_Y && matrix[x][y+1] != BUBBLE_NONE)
            {
                if(matrix[x][y+1] == BUBBLE_TRANSPARENT)
                    containsTransparent = true;
                else if(!PathContains(tempPath, x, y + 1))
                    tempPath.push_back(new Path(x, y+1, false));
            }

            if (y-1 >= 0 && matrix[x][y-1] != BUBBLE_NONE)
            {

                if(matrix[x][y-1] == BUBBLE_TRANSPARENT)
                {
                    containsTransparent = true;
                }
                else if(!PathContains(tempPath, x, y - 1))
                    tempPath.push_back(new Path(x, y-1, false));
            }

            if (x-1 >= 0 && matrix[x-1][y] != BUBBLE_NONE)
            {
                if(matrix[x-1][y] == BUBBLE_TRANSPARENT)
                    containsTransparent = true;
                else if(!PathContains(tempPath, x - 1, y))
                    tempPath.push_back(new Path(x-1, y, false));
            }

            if(x+1 < BOARD_SIZE_X && matrix[x+1][y] != BUBBLE_NONE)
            {
                if(matrix[x+1][y] == BUBBLE_TRANSPARENT)
                    containsTransparent = true;
                else if(!PathContains(tempPath, x + 1, y))
                    tempPath.push_back(new Path(x+1, y, false));
            }

            if(x % 2 == 0)
            {
                if(x-1 >= 0 && y-1 >= 0 && matrix[x-1][y-1] != BUBBLE_NONE)
                {
                    if(matrix[x-1][y-1] == BUBBLE_TRANSPARENT)
                        containsTransparent = true;
                    else if(!PathContains(tempPath, x - 1, y - 1))
                        tempPath.push_back(new Path(x-1, y-1, false));
                }

                if(x+1 < BOARD_SIZE_X && y-1 >= 0 && matrix[x+1][y-1] != BUBBLE_NONE)
                {
                    if(matrix[x+1][y-1] == BUBBLE_TRANSPARENT)
                        containsTransparent = true;
                    else  if(!PathContains(tempPath, x + 1, y - 1))
                        tempPath.push_back(new Path(x+1, y-1, false));
                }
            }
            else
            {
                if(x-1 >= 0 && y+1 >= 0 && matrix[x-1][y+1] != BUBBLE_NONE)
                {
                    if(matrix[x-1][y+1] == BUBBLE_TRANSPARENT)
                        containsTransparent = true;
                    else if(!PathContains(tempPath, x - 1, y + 1))
                        tempPath.push_back(new Path(x-1, y+1, false));
                }
                if(x+1 >= 0 && y+1 >= 0 && matrix[x+1][y+1] != BUBBLE_NONE)
                {
                    if(matrix[x+1][y+1] == BUBBLE_TRANSPARENT)
                        containsTransparent = true;
                    else if(!PathContains(tempPath, x + 1, y + 1))
                        tempPath.push_back(new Path(x+1, y+1, false));
                }
            }
        }
    }

    for(auto & i : tempPath)
        delete i;
    tempPath.clear();

    return !containsTransparent;
}

void Matchfinder::ClearPath(Bubble *bubbles[BOARD_SIZE_X][BOARD_SIZE_Y], int *pscore, int *pbubbles)
{
    long long int startBubbles = numBubbles;
    for(auto & i : path)
    {
        long long int x = i->x;
        long long int y = i->y;
        bubbles[x][y]->Clear();
        matrix[x][y] = (int8_t) BUBBLE_NONE;
        numBubbles--;
        delete i;
    }
    path.clear();
    for(long long int i = 0; i < BOARD_SIZE_X; i++)
        for(long long int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if(bubbles[i][j]->GetTexture() != nullptr && IsIsolated(i, j))
            {
                bubbles[i][j]->Clear();
                matrix[i][j] = (int8_t) BUBBLE_NONE;
                numBubbles--;
            }
        }

    long long int bubblesBroken = startBubbles - numBubbles;
    long long int score = 100;
    long long int bubbleScore = 50;
    for(long long int i = 3; i < bubblesBroken && i < 6; i++)
    {
        score += bubbleScore;
        bubbleScore += 50;
    }
    for(long long int i = 6; i < bubblesBroken && i < 9; i++)
    {
        score += bubbleScore;
        bubbleScore += 100;
    }
    for(long long int i = 9; i < bubblesBroken && i < 13; i++)
    {
        score += bubbleScore;
        bubbleScore += 150;
    }
    for(long long int i = 13; i < bubblesBroken && i < 16; i++)
    {
        score += bubbleScore;
        bubbleScore += 200;
    }
    for(long long int i = 16; i < bubblesBroken && i < 17; i++)
    {
        score += bubbleScore;
        bubbleScore += 300;
    }
    for(long long int i = 17; i < bubblesBroken; i++)
    {
        score += bubbleScore;
    }
    *pbubbles = numBubbles;
    *pscore = score;
}

bool Matchfinder::CheckForMatch(int new_i, int new_j)
{
    path.push_back(new Path(new_i, new_j, false));
    long long int num_visited = 0;
    while(path.size() > num_visited)
    {
        size_t size = path.size();
        for(size_t i = 0; i < size; i++)
        {
            if(path[i]->visited)
                continue;
            new_i = path[i]->x;
            new_j = path[i]->y;

            path[i]->visited = true;
            num_visited++;

            if (new_j+1 < BOARD_SIZE_Y)
                if(matrix[new_i][new_j] == matrix[new_i][new_j+1] && !PathContains(path, new_i, new_j + 1))
                    path.push_back(new Path(new_i, new_j+1, false));

            if (new_j-1 >= 0)
                if(matrix[new_i][new_j] == matrix[new_i][new_j-1] && !PathContains(path, new_i, new_j - 1))
                    path.push_back(new Path(new_i, new_j-1, false));

            if (new_i-1 >= 0)
                if(matrix[new_i][new_j] == matrix[new_i-1][new_j] && !PathContains(path, new_i - 1, new_j))
                    path.push_back(new Path(new_i-1, new_j, false));

            if(new_i+1 < BOARD_SIZE_X && new_j >= 0)
                if(matrix[new_i][new_j] == matrix[new_i+1][new_j] && !PathContains(path, new_i + 1, new_j))
                    path.push_back(new Path(new_i+1, new_j, false));

            if(new_i % 2 == 0)
            {
                if(new_i-1 >= 0 && new_j-1 >= 0)
                    if(matrix[new_i][new_j] == matrix[new_i-1][new_j-1] && !PathContains(path, new_i - 1, new_j - 1))
                        path.push_back(new Path(new_i-1, new_j-1, false));

                if(new_i+1 < BOARD_SIZE_X && new_j-1 >= 0)
                    if(matrix[new_i][new_j] == matrix[new_i+1][new_j-1] && !PathContains(path, new_i + 1, new_j - 1))
                        path.push_back(new Path(new_i+1, new_j-1, false));
            }
            if(new_i % 2 == 1)
            {
                if(new_i-1 >= 0 && new_j+1 >= 0)
                    if(matrix[new_i][new_j] == matrix[new_i-1][new_j+1] && !PathContains(path, new_i - 1, new_j + 1))
                        path.push_back(new Path(new_i-1, new_j+1, false));

                if(new_i+1 >= 0 && new_j+1 >= 0)
                    if(matrix[new_i][new_j] == matrix[new_i+1][new_j+1] && !PathContains(path, new_i + 1, new_j + 1))
                        path.push_back(new Path(new_i+1, new_j+1, false));
            }
        }
    }

    if(path.size() >= 3)
        return true;

    for(auto & i : path)
        delete i;
    path.clear();

    return false;
}

LevelManager* LevelManager::instance = nullptr;
LevelManager::LevelManager()
{
    FILE *fp = fopen("levels.txt", "r");
    if(fp == nullptr)
    {
        perror("levels.txt");
        exit(EXIT_FAILURE);
    }

    memset(numBubbles, 0, NUM_LEVELS_IMPLEMENTED*sizeof(numBubbles[0]));
    for(long long int l = 0; l < NUM_LEVELS_IMPLEMENTED; l++)
    {
        fscanf(fp,"\n");
        for(long long int i = 0; i < BOARD_SIZE_X; i++)
        {
            for(long long int j = 0; j < BOARD_SIZE_Y; j++)
            {
                if(j != BOARD_SIZE_Y-1)
                    fscanf(fp, "%hhd ", &level[l][i][j]);
                else
                    fscanf(fp, "%hhd\n", &level[l][i][j]);
                if(level[l][i][j] == 1)
                    numBubbles[l]++;

            }
        }
    }

    fclose(fp);
}

void LevelManager::SetLevel(int l, Bubble *bubbles[BOARD_SIZE_X][BOARD_SIZE_Y]) {
    SDL_FRect dstRect;
    dstRect.x = BUBBLE_OFFSET_X;
    dstRect.y = BUBBLE_OFFSET_Y;
    dstRect.w = BUBBLE_WIDTH;
    dstRect.h = BUBBLE_HEIGHT;
    BubbleColor bubbleColor[NUM_BUBBLES] = {BUBBLE_BLUE, BUBBLE_YELLOW, BUBBLE_GREEN, BUBBLE_RED, BUBBLE_TRANSPARENT};
    SDL_Event event;

    for (long long int i = 0; i < BOARD_SIZE_X; i++) {

//            SDL_GetMouseState(&mogh_x, &mogh_y);
//            if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
                if (i % 2 == 1)
                    dstRect.x += BUBBLE_WIDTH / 2;


            for (long long int j = 0; j < BOARD_SIZE_Y; j++) {
                uint8_t bubbleType = level[l-1][i][j];
                if (bubbleType == 1) {
                    bubbles[i][j] = new Bubble(bubbleColor[rand() % 4], dstRect, true);
                } else if (bubbleType == 2)
                    bubbles[i][j] = new Bubble(BUBBLE_TRANSPARENT, dstRect, true);
                else if (bubbleType == 0)
                    bubbles[i][j] = new Bubble(BUBBLE_NONE, dstRect, false);
                Matchfinder::getInstance()->SetMatrix(i, j, bubbles[i][j]->GetColor());
                dstRect.x += BUBBLE_WIDTH;
            }
            dstRect.x = BUBBLE_OFFSET_X;
            dstRect.y += BUBBLE_HEIGHT - 5;
        }
    }


LevelManager* LevelManager::getInstance()
{
    if(!instance)
        instance = new LevelManager;
    return instance;

}

LevelManager::~LevelManager()
{
    instance = nullptr;
}

void Game::InitStats()
{
    const char *path = "config.txt";
    FILE *fp = fopen(path, "r");
    if(fp == nullptr)
    {
        perror(path);
        exit(EXIT_FAILURE);
    }

    currentFrame = 0;
    frozenFrame = 0;
    strikesAfter5Consecutive = 0;
    consecutiveStrikes = 0;
    consecutiveStrikesRect.x = STRIKES_RECT_X;
    consecutiveStrikesRect.y = STRIKES_RECT_Y;
    consecutiveStrikesRect.w = STRIKES_RECT_W;
    consecutiveStrikesRect.h = 0;

    levelOffset = 0;
    t = 0;
    velocity = 0;
    acceleration = 0.005;

    running = true;
    paused = false;
    frozen = false;

    shouldShootBubble = false;
    shootingBubble = false;
    /*vlocity_va_timermoon_ro_az_file_migirim */
    fscanf(fp, "level: %d\n", &level);
    fscanf(fp, "score: %d\n", &score);
    fscanf(fp, "score multiplier: %fx\n", &scoreMultiplier);
    fscanf(fp, "timer: %d seconds\n", &timer);
    fscanf(fp, "bubble speed: %f\n", &bubbleSpeed);
    fclose(fp);

    bubbleSpeed *= 0.01;
}

Game::Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    /* chiz_haye_SDL */
    Uint32 flags = 0;
    if(fullscreen)
        flags |= SDL_WINDOW_FULLSCREEN;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
        running = false;
        return;
    }
//    SDL_Window *m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);


//    SDL_Renderer *renderer = SDL_CreateRenderer(m_window, -1, 0);
    GUIManager::getInstance()->SetWindow(m_window);
    GUIManager::getInstance()->SetRenderer(m_renderer);

    currentTime = time(nullptr);
    srand(currentTime);

    InitStats();
    InitMap();
    SDL_RenderPresent(m_renderer);
}

void Game::InitMap()
{
    if(level >= 2)
    {
        numBubblesLeft = LevelManager::getInstance()->GetNumBubbles(level);
        LevelManager::getInstance()->SetLevel(level, bubbles);
    }
    else
    {
        levelOffset = 2 + rand() % (NUM_LEVELS_IMPLEMENTED-1);
        numBubblesLeft = LevelManager::getInstance()->GetNumBubbles(levelOffset);
        LevelManager::getInstance()->SetLevel(levelOffset, bubbles);
    }

    SDL_FRect cannonBubbleDstRect;
    cannonBubbleDstRect.x = CANNON_BUBBLE_OFFSET_X;
    cannonBubbleDstRect.y = CANNON_BUBBLE_OFFSET_Y;
    cannonBubbleDstRect.w = CANNON_BUBBLE_WIDTH;
    cannonBubbleDstRect.h = CANNON_BUBBLE_HEIGHT;
//    cannonBubble = new Bubble(RandomBubble(), cannonBubbleDstRect, true);


    int x = RandomBubble();
    SDL_FRect spareBubbleDstRect;
    spareBubbleDstRect.x = SPARE_BUBBLE_OFFSET_X;
    spareBubbleDstRect.y = SPARE_BUFFLE_OFFSET_Y;
    spareBubbleDstRect.w = SPARE_BUBBLE_W;
    spareBubbleDstRect.h = SPARE_BUBBLE_H;
    spareBubble =new Bubble(RandomBubble(), spareBubbleDstRect, true);
    cannonBubble = new Bubble(RandomBubble(), spareBubbleDstRect, true);
//    spareBubble = new Bubble(canonbubble colo, spareBubbleDstRect, true);


    cannonPoint.x = cannonBubbleDstRect.x + cannonBubbleDstRect.w/2;
    cannonPoint.y = cannonBubbleDstRect.y + cannonBubbleDstRect.h/2;
    startPoint = cannonPoint;
    shotBubble = new Bubble(BUBBLE_NONE, cannonBubbleDstRect, false);
}
/////////////////////////////////// random ball  creaator////////////////////////
BubbleColor Game::RandomBubble()
{
    long long int freq[NUM_BUBBLES];
    memset(freq, 0, NUM_BUBBLES*sizeof(int));
    for(auto & bubble : bubbles)
        for(auto & j : bubble)
        {
            if(j->GetTexture() == nullptr)
                continue;
            freq[j->GetColor()]++;
        }
    long long int randomBubble;
    while(true)
    {
        randomBubble = ((rand() % (NUM_BUBBLES -1)));
        if(freq[randomBubble] > 0)
            break;
    }
    return (BubbleColor) randomBubble;
}
bool Game::InsideRect(float pointX, float pointY, SDL_FRect &rect)
{
    if (pointX >= rect.x && pointX <= (rect.x + rect.w))
        if (pointY >= rect.y && pointY <= (rect.y + rect.h))
            return true;
    return false;
}

Game::~Game()
{
    delete FontRenderer::getInstance();
    delete TextureManager::getInstance();
    delete GUIManager::getInstance();
    delete Matchfinder::getInstance();
    delete SoundManager::getInstance();

    for(auto & bubble : bubbles)
        for(auto & j : bubble)
            delete j;
    delete cannonBubble;
    delete spareBubble;
    delete shotBubble;
    SDL_Quit();
}

void Game::Play()
{
    const long long int FPS = 60;
    const long long int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    Uint32 frameTime;

    while (running)
    {

        frameStart = SDL_GetTicks();
        HandleEvents();
        if(!paused)
        {
            if(!frozen)
                currentFrame++;
            else
                frozenFrame++;
            if(timer==0)
            {
                Render();
            }
            else
            {
                Update();
                Render();
            }
            Update();
            Render();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
        else
            ;
    }

    SDL_RenderClear(m_renderer);
    printf("Game over, your score is %d\n", score);
}

void drawLineToMouseAndReflect(SDL_Renderer* m_renderer) {
    SDL_GetMouseState(&mogh_x, &mogh_y);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);

    SDL_RenderDrawLine(m_renderer, 505, 675, mogh_x, mogh_y);

    float slope = (float)(mogh_y - 675) / (mogh_x - 505);

    float yIntercept = 675 - slope * 505;

    int wallX = (mogh_x < 505) ? 130 : 880;

    int wallY = slope * wallX + yIntercept;

    SDL_RenderDrawLine(m_renderer, mogh_x, mogh_y, wallX, wallY);

    if (wallX == 130 || wallX == 880) {

        float reflectionSlope = -slope;

        float reflectionYIntercept = wallY - reflectionSlope * wallX;

        int reflectionX = (reflectionYIntercept < 0) ? -reflectionYIntercept / reflectionSlope : 1200;

        int endY = 765 - 2 * (675 - wallY);

        SDL_RenderDrawLine(m_renderer, wallX, wallY, 505, endY);
    }

    SDL_RenderPresent(m_renderer);
    }



void Game::Render()
{
    SDL_RenderClear(GUIManager::getInstance()->GetRenderer());
    DisplayBackground();
//    DisplayCannon();
    if(!normal)DisplayTimer();

    DisplayScore();
    DisplayLevel();

    DisplayConsecutiveStrikesRect();
    DisplayBubbles();
//    Canon(m_renderer,canon,canon_rect,m_window);
    DisplayCannonToBubbleVector();
//    SDL_RenderDrawLineF(GUIManager::getInstance()->GetRenderer(), startPoint.x, startPoint.y, endPoint.x, endPoint.y);
//    SDL_RenderDrawLineF(GUIManager::getInstance()->GetRenderer(), endPoint.x, mogh_y, startPoint.x, endPoint.y-(startPoint.y-endPoint.y));
//    SDL_RenderCopyEx(m_renderer, canon, NULL, canon_rect, angle, NULL, SDL_FLIP_NONE);
    handle_canon();
    drawLineToMouseAndReflect(m_renderer);
    SDL_RenderPresent(GUIManager::getInstance()->GetRenderer());

}

void shift_layers(std::vector<std::vector<int>>& vec) {

    std::vector<int> new_second_layer = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};

    for (int i = 16; i > 0; --i) {
        vec[i+1] = vec[i];
    }

    vec[1] = new_second_layer;
}

void Game::Normalize(SDL_FPoint &vec, int length)
{

    float norm = sqrt(vec.x*vec.x + vec.y*vec.y);
    vec.x = (vec.x * length  ) / norm ;
    vec.y =  ( vec.y * length) / norm ;
}

void Game::ShootBubbleInit()
{
    SDL_FRect cannonBubbleDestRect = cannonBubble->GetDestRect();
    cannonBubbleDestRect.w = BUBBLE_WIDTH;
    cannonBubbleDestRect.h = BUBBLE_HEIGHT;
    shotBubble->SetColor(cannonBubble->GetColor());
    shotBubble->SetDestRect(cannonBubbleDestRect);
    shotBubble->SetTexture(cannonBubble->GetTexture());
    shotBubble->SetVisible(true);
    shotBubbleDirectionVector.x = mousePoint.x - cannonPoint.x;
    shotBubbleDirectionVector.y = mousePoint.y - cannonPoint.y;
    Normalize(shotBubbleDirectionVector);
    cannonBubble->SetColor(spareBubble->GetColor());
    cannonBubble->SetTexture(spareBubble->GetTexture());
    BubbleColor bubbleColor = RandomBubble();
    spareBubble->SetColor(bubbleColor);
    spareBubble->SetTexture(TextureManager::getInstance()->GetBubble(bubbleColor));
    shootingBubble = true;
}

void Game::HandleCollision(float &x, float &y, Bubble *bubble)
{
    SDL_FRect bubbleDestRect = bubble->GetDestRect();
    SDL_FRect shotBubbleRect = shotBubble->GetDestRect();

    while(InsideRect(x, y, bubbleDestRect))
    {
        t -= bubbleSpeed;
        x = startPoint.x + shotBubbleDirectionVector.x * t;
        y = startPoint.y + shotBubbleDirectionVector.y * t;
    }

    shotBubbleRect.x =  x;
    shotBubbleRect.y = y ;
    shotBubble->SetDestRect(shotBubbleRect);

    for(long long int new_i = 0; new_i < BOARD_SIZE_X; new_i++)
        for(long long int new_j = 0; new_j < BOARD_SIZE_Y; new_j++)
        {
            bubbleDestRect = bubbles[new_i][new_j]->GetDestRect();
            if(bubbles[new_i][new_j]->GetTexture() != nullptr || !InsideRect(x, y, bubbleDestRect))
                continue;

            bubbles[new_i][new_j]->SetColor(shotBubble->GetColor());
            bubbles[new_i][new_j]->SetTexture(shotBubble->GetTexture());
            bubbles[new_i][new_j]->SetVisible(true);



            double angle = atan2(shotBubbleDirectionVector.y, shotBubbleDirectionVector.x);
            angle += M_PI;
            double angle_in_degrees = angle*180/M_PI;

            if(velocity > 0.5)
                velocity = 0.5;
            if(velocity > 0.1 && velocity < 0.3)
                velocity += velocity/2;

            t = 0;
            shootingBubble = false;
            shotBubble->SetVisible(false);

            Matchfinder::getInstance()->SetMatrix(new_i, new_j, bubbles[new_i][new_j]->GetColor());
            if(Matchfinder::getInstance()->CheckForMatch(new_i, new_j))
            {
                if(consecutiveStrikes == 5)
                {
                    if (strikesAfter5Consecutive % 4 == 0 || strikesAfter5Consecutive % 4 == 1) {
                        SoundManager::getInstance()->PlaySound(SOUND_COMBO_BONUS1);


                    }
                        if(strikesAfter5Consecutive % 4 == 2 || strikesAfter5Consecutive % 4 == 3)
                        SoundManager::getInstance()->PlaySound(SOUND_COMBO_BONUS2);


                    strikesAfter5Consecutive++;
                }
                else
                    SoundManager::getInstance()->PlaySound(SOUND_COMBO);
                int currentMoveScore = 0;
                        Matchfinder::getInstance()->ClearPath(bubbles, &currentMoveScore, &numBubblesLeft);
                            score += scoreMultiplier * currentMoveScore;
                if
                (!Matchfinder::getInstance()->BoardContains(spareBubble->GetColor()) &&
                   !Matchfinder::getInstance()->BoardIsEmpty()){
                            BubbleColor bubbleColor = RandomBubble() ;
                            spareBubble->SetColor(bubbleColor);spareBubble->SetTexture(TextureManager::getInstance()->GetBubble(bubbleColor));
                }
                if(!Matchfinder::getInstance()->BoardContains(cannonBubble->GetColor()) &&
                   !Matchfinder::getInstance()->BoardIsEmpty()){
                        BubbleColor  bubbleColor = RandomBubble() ;
                            cannonBubble->SetColor(bubbleColor);
                            cannonBubble->SetTexture(TextureManager::getInstance()->GetBubble(bubbleColor));
                }
                if(consecutiveStrikes < 5){
                    consecutiveStrikes++;
                        if(consecutiveStrikes == 5)
                            SoundManager::getInstance()->PlaySound(SOUND_FULLY_LOADED);
                                consecutiveStrikesRect.h -= STRIKES_RECT_H;
                    scoreMultiplier = 1.5;
                }
            }
            else
            {
               if(consecutiveStrikes == 5)
                    SoundManager::getInstance()->PlaySound(SOUND_RESET_BONUS);
                else
                    SoundManager::getInstance()->PlaySound(SOUND_FAILED_SHOT);
                if(consecutiveStrikes > 0)
                    {
                        scoreMultiplier = 1;
                        consecutiveStrikes = 0;
                        strikesAfter5Consecutive =  0;
                            consecutiveStrikesRect.h = 0;
                    }
            }
            return;
        }
    t = 0;
    shootingBubble = false;
    shotBubble->SetVisible(false);
}

void Game::ShootBubble()
{
    static bool playSound = false;
    static bool playedSound = false;
    float x = startPoint.x + shotBubbleDirectionVector.x * t;
    float y = startPoint.y + shotBubbleDirectionVector.y * t ;
    SDL_FRect shotBubbleRect = shotBubble->GetDestRect();
    shotBubbleRect.x = x - shotBubbleRect.w/2 ;
    shotBubbleRect.y = y - shotBubbleRect.h/2;
    shotBubble->SetDestRect(shotBubbleRect) ;

    if(x >= WALL_RIGHT_X)
    {
        playSound = true;
        if(playSound && !playedSound)
        {
                SoundManager::getInstance()->PlaySound(SOUND_HIT_WALL) ;
                playedSound = true;
        }
        double theta;
        theta = atan2(shotBubbleDirectionVector.y, shotBubbleDirectionVector.x);
        theta = M_PI - theta;
        startPoint.x = x;
        startPoint.y = y;
        endPoint.x = startPoint.x + 250 * cos(theta);
        endPoint.y = startPoint.y + 250 * sin(theta);
        shotBubbleDirectionVector.x = endPoint.x - startPoint.x;
        shotBubbleDirectionVector.y = endPoint.y - startPoint.y;
        Normalize(shotBubbleDirectionVector);
        t = 0;
    }
    else if(x <= WALL_LEFT_X)
    {
        playSound = true;
        if(playSound && !playedSound)
        {
                SoundManager::getInstance()->PlaySound(SOUND_HIT_WALL);
            playedSound = true;
        }

        long double theta;
        theta = atan2(shotBubbleDirectionVector.y, shotBubbleDirectionVector.x);
        theta = M_PI - theta;
        startPoint.x = x + 3;
        startPoint.y = y;
        endPoint.x = startPoint.x + 250 * cos(theta);
        endPoint.y = startPoint.y + 250 * sin(theta);
        shotBubbleDirectionVector.x = endPoint.x - startPoint.x;
        shotBubbleDirectionVector.y = endPoint.y - startPoint.y;
        Normalize(shotBubbleDirectionVector);
        t = 0;
    }
    else if(y <= WALL_TOP_Y)
    {
        playSound = true;
        if(playSound && !playedSound){
             SoundManager::getInstance()->PlaySound(SOUND_HIT_WALL);
            playedSound = true;
        }

        long double theta;
        theta = atan2(shotBubbleDirectionVector.y, shotBubbleDirectionVector.x);
        theta = 2*M_PI - theta;
        startPoint.x = x;
        startPoint.y = y;
        endPoint.x = startPoint.x + 250 * cos(theta);
        endPoint.y = startPoint.y + 250 * sin(theta);
        shotBubbleDirectionVector.x = endPoint.x - startPoint.x;
        shotBubbleDirectionVector.y = endPoint.y - startPoint.y;
        Normalize(shotBubbleDirectionVector);
        t = 0;
    }
    else if(y >= WALL_BOTTOM_Y){
        shotBubble->SetVisible(false);
        shootingBubble = false;
        t = 0;
        return;
    }
    else
    {
        if(playSound)
            playSound = false;
        if(playedSound)
            playedSound = false;
    }

    for(auto & bubble : bubbles)
        for(auto & j : bubble)
        {
            SDL_FRect bubbleDestRect = j->GetDestRect();
            if(!InsideRect(x, y, bubbleDestRect))
                continue;
            if(j->GetColor() == BUBBLE_NONE)
                continue;
            HandleCollision(x, y, j);
            return;
        }
    t += bubbleSpeed;
}
void Game::handle_canon(){

    SDL_Surface* canon_img = IMG_Load("cannon.png");

    SDL_Texture* canon = SDL_CreateTextureFromSurface(m_renderer, canon_img);

    double angle = 0;

    bool quit = false;

    SDL_Event event;

    if (!quit) {

        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_GetMouseState(&mogh_x, &mogh_y);

        angle = atan2(600 - mogh_y, (WINDOW_WIDTH-100 / 2) - mogh_x );

        draw_image_zaviedar(m_renderer, canon, angle);

        SDL_RenderPresent(m_renderer);
    }
}
void Game :: draw_image_zaviedar (SDL_Renderer* renderer, SDL_Texture* texture, double angle) {

    int x = (WINDOW_WIDTH - IMAGE_WIDTH) / 2 + 33;
    int y = 700 - IMAGE_HEIGHT-33;
    SDL_Event event;
    SDL_Rect rect = {x, y, 130, 130};
    if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
    {

    }
    SDL_RenderCopyEx(m_renderer, canon, NULL, &rect, ((angle * 180)-30) / M_PI, NULL, SDL_FLIP_NONE);
}

void Game::ChangeLevel(int marhale)
{
    frozen = true;
    if(level+marhale < 1)
    {
        frozen = false;
        return;
    }

    level+=1;

    currentTime += marhale;
    srand(currentTime);

    if(level <= 2)
        numBubblesLeft = LevelManager::getInstance()->GetNumBubbles(level);
    else
    {
        levelOffset = 0;
        levelOffset = 2 +level;

        numBubblesLeft = LevelManager::getInstance()->GetNumBubbles(levelOffset);

    }
}

void Game::Update()
{
    if(frozen && rotateLeft)
    {
        rotateLeft = false;
    }
    if(frozen && rotateRight)
    {
        rotateRight = false;
    }
    if(rotateLeft && !frozen)
    {
        RotateBubbles(ROTATE_LEFT);
    }
    if(rotateRight && !frozen)
    {
        RotateBubbles(ROTATE_RIGHT);
    }
    if(shouldShootBubble && !shootingBubble)
    {
        ShootBubbleInit();
        shouldShootBubble = false;
        shootingBubble = true;
        startPoint = cannonPoint;
        endPoint = mousePoint;
    }
    if(shootingBubble)
    {
        ShootBubble();
    }
    if(numBubblesLeft == 0)
    {
        SoundManager::getInstance()->PlaySound(SOUND_LEVEL_UP);
//
        ChangeLevel(1);
    }
    if(frozen)
    {
        if(frozenFrame == 30)
        {
            frozen = false;
            frozenFrame = 0;
            if(level <= 2)
                LevelManager::getInstance()->SetLevel(level, bubbles);
            else
                LevelManager::getInstance()->SetLevel(levelOffset, bubbles);
        }
    }
    if(currentFrame % 60 == 0 && !frozen)
    {
        timer--;
    }
    if(timer == 0)
    {
        if(normal)
        running = true;
        else
        running=false;


    }
}
void barikalla()
{
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);


    SDL_Window* w_window = SDL_CreateWindow("Barikalla !", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (w_window == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(w_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(w_window);
        SDL_Quit();
        return;
    }

    bool running_barik= true;
    while (running_barik)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
            {
                running_barik = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderText(m_renderer, "Barikalla !", 300, 250, 64, 100);

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(w_window);
    TTF_Quit();

}
void Game::HandleEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (numBubblesLeft==0){
            barikalla();

        }
        if ((event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED )&& (is_clicked( mogh_x ,mogh_y,915 ,80,220,230)))
        {
            running=false;
        }
            if ((event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED )&& (is_clicked( mogh_x ,mogh_y,930 ,60,190,70)))
        {

            setting = 1;

            draw(m_renderer,setting_window_png,setting_window_rect,0,-100,1300,1000);
            draw(m_renderer,unmute_dokme_png,unmute_dokme_rect,95, 560, 70, 150);
            draw(m_renderer,mute_dokme_png,mute_dokme_rect,95, 630, 70, 150);
            draw(m_renderer,full_music_dokme_png,full_music_dokme_rect,505, 210, 295, 240);
            draw(m_renderer, setting_dokme_png, setting_dokme_rect, 577, 30, 150, 240);
            draw(m_renderer, exit_dokme_png, exit_dokme_rect, 70, 100, 150, 240);
            SDL_RenderPresent(m_renderer);
        }

        while (setting)
        {
            setting_ma_actions(m_renderer);
            if (volume==0)
                Mix_VolumeMusic(0);
            else if (volume ==1)
                Mix_VolumeMusic(30);
            else if (volume ==2)
                Mix_VolumeMusic(128);
            SDL_RenderPresent(m_renderer);

        }
        switch (event.type)
        {
            case SDL_QUIT:
            {
                running = false;
                break;
            }
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_SPACE:
                    {
                        SDL_FRect rect = cannonBubble->GetDestRect();
                        cannonBubble->SetDestRect(spareBubble->GetDestRect());
                        spareBubble->SetDestRect(rect);
                        Bubble *tmp = cannonBubble;
                        cannonBubble = spareBubble;
                        spareBubble = tmp;
                        break;
                    }

                    case SDLK_p:
                    {
                        paused = !paused;
                        break;
                    }
                    case SDLK_r:
                    {
                        Entity::ToggleRectangleVisible();
                        break;
                    }
                    case SDLK_LEFT:
                    {
                        ChangeLevel(-1);
                        break;
                    }
                    case (SDLK_l):
                    {
                        ChangeLevel(1);
                        break;
                    }
                }
                break;
            }

            case SDL_MOUSEMOTION:
            {
                HandleMouseMotion(event);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                HandleMouseDown(event);
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                HandleMouseUp(event);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Game::HandleMouseMotion(SDL_Event &event)
{
    SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
}

void Game::RotateBubbles(RotateDirection direction) {
    long long int sign = 0;
    float dtheta;
    SDL_FPoint centerOfRotation;

    if (direction == ROTATE_LEFT)
        sign = -1;
    else if (direction == ROTATE_RIGHT)
        sign = 1;
    dtheta = sign * 0.10 * velocity;
    centerOfRotation.x = bubbles[LVL1_CENTER_X][LVL1_CENTER_Y]->GetDestRect().x;
    centerOfRotation.y = bubbles[LVL1_CENTER_X][LVL1_CENTER_Y]->GetDestRect().y;
    for (auto &bubble: bubbles)
        for (auto &j: bubble) {
            SDL_FPoint vectorCenterToBubble;
            vectorCenterToBubble.x = j->GetDestRect().x - centerOfRotation.x;
            vectorCenterToBubble.y = j->GetDestRect().y - centerOfRotation.y;

            float radius = sqrt(
                    vectorCenterToBubble.x * vectorCenterToBubble.x + vectorCenterToBubble.y * vectorCenterToBubble.y);
            float theta = atan2(vectorCenterToBubble.y, vectorCenterToBubble.x);

            SDL_FRect newRect;
            newRect.x = centerOfRotation.x + radius * cos(theta + dtheta);
            newRect.y = centerOfRotation.y + radius * sin(theta + dtheta);
            newRect.w = j->GetDestRect().w;
            newRect.h = j->GetDestRect().h;

            j->SetDestRect(newRect);
        }

    velocity -= acceleration;
    if (velocity <= 0) {
        if (rotateLeft)
            rotateLeft = false;
        if (rotateRight)
            rotateRight = false;
    }
}
void Game::HandleMouseDown(SDL_Event &event)
{
    SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
    if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
    {
        if(!shootingBubble)
        {
//            SoundManager::getInstance()->PlaySound(SOUND_SHOOT_BUBBLE);
            shouldShootBubble = true;
        }
    }
//    if (shouldShootBubble){
//        shiftBubbles()
//    }
}

void Game::HandleMouseUp(SDL_Event &event)
{
    SDL_atomic_t t;
    SDL_GetMouseState(&mousePoint.x, &mousePoint.y);
    if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_RELEASED)
    {
    }
}

void Game::DisplayBackground()
{
    SDL_RenderCopy(GUIManager::getInstance()->GetRenderer(), TextureManager::getInstance()->GetBackground(), nullptr, nullptr);
    draw(m_renderer,pause_dokme_png,pause_dokme_rect,930 ,60,190,70);
    draw(m_renderer,cheat_png,cheat_rect,900 ,250,320,350);
    draw(m_renderer,quit_dokme_png,quit_dokme_rect,915 ,80,220,230);


}

void Game::DisplayScore()
{
    char text[32];
    sprintf(text, "%d", score);
    FontRenderer::getInstance()->DisplayText(text, SCORE_OFFSET_X, SCORE_OFFSET_Y);
}
void Game::DisplayLevel()
{
    char text[16];
    sprintf(text, "%d", level);
    FontRenderer::getInstance()->DisplayText(text, LEVEL_OFFSET_X, LEVEL_OFFSET_Y);
}

void Game::DisplayConsecutiveStrikesRect()
{
    SDL_SetRenderDrawColor(GUIManager::getInstance()->GetRenderer(), 210, 78, 170, 255);
    SDL_RenderFillRect(GUIManager::getInstance()->GetRenderer(), &consecutiveStrikesRect);
}

void Game::DisplayTimer()
{
    char text[16];
    sprintf(text, "%02d:%02d", timer / 60, timer % 60);
    FontRenderer::getInstance()->DisplayText(text, TIMER_OFFSET_X, TIMER_OFFSET_Y);
}

void Game::DisplayBubbles()
{
    for(auto & bubble : bubbles)
        for(auto & j : bubble)
            j->Render();
    cannonBubble->Render();
//    spareBubble->Render();
    if(shotBubble->IsVisible())
        shotBubble->Render();
}

void Game::DisplayCannonToBubbleVector()
{
//    SDL_RenderDrawLine(GUIManager::getInstance()->GetRenderer(), cannonPoint.x, cannonPoint.y, mousePoint.x, mousePoint.y);
}

Entity::Entity()
= default;

Entity::~Entity()
= default;

bool Entity::rectangleVisible = false;
void Entity::Render()
{
    if(texture != nullptr && isVisible)
    {
        SDL_RenderCopyF(GUIManager::getInstance()->GetRenderer(), texture, nullptr, &dstRect);


    }
    if(rectangleVisible)
    {
            SDL_SetRenderDrawColor(GUIManager::getInstance()->GetRenderer(), 0x00, 0x00, 0x00, 255);
        SDL_RenderDrawRectF(GUIManager::getInstance()->GetRenderer(), &dstRect);


    }
}

Bubble::Bubble(BubbleColor bubbleColor, SDL_FRect dstRect, bool isVisible)
{
    this->bubbleColor = bubbleColor;
    this->texture = TextureManager::getInstance()->GetBubble(this->bubbleColor);
    this->dstRect= dstRect;
    this->isVisible= isVisible;

}

void Bubble::Clear()
{
    SetVisible(false);
    SetTexture(TextureManager::getInstance()->GetBubble(BUBBLE_NONE));
    SetColor(BUBBLE_NONE);

}

Bubble::~Bubble()
= default;
