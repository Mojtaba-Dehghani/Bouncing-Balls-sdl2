#define _fUNCTIONS_H_

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
using namespace std;

void menu( SDL_Renderer* m_renderer,bool d_or_night);
bool is_clicked(int x1,int y1,int x,int y,int w,int h);
void draw(SDL_Renderer* m_renderer, SDL_Texture* m_img, SDL_Rect img_rect, int x, int y, int w, int h);
void setting_ma(SDL_Renderer* m_renderer,bool mode);
void setting_ma_actions(SDL_Renderer* m_renderer);
void draw_image_zaviedar(SDL_Renderer* m_renderer, SDL_Texture* texture, double angle);
void draw_rect_zaviedar(SDL_Renderer* m_renderer, int x, int y, int w, int h, SDL_Color color) ;
void game(SDL_Renderer* m_renderer,bool d_or_night);
void canon_pain();
void shift_layers_3d(std::vector<std::vector<std::vector<int>>>& vec);
void shift_layers_3d_ar(int arr[7][18][18]);
void menu_run_actions(SDL_Renderer* m_renderer );
void menu_run(SDL_Renderer* m_renderer ,bool mode);
void shiftBubbles(std::vector<std::vector<int>>& board, bool shouldShootBubble);
void draw_image_zaviedar(SDL_Renderer* renderer, SDL_Texture* texture, double angle);
void handle_canon();
void drawLineToMouseAndReflect(SDL_Renderer* m_renderer);
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, int w, int h);
void user_input();
void barikalla();
void showLeaderboard(SDL_Renderer* renderer, const std::string& filename, TTF_Font* font, SDL_Color color);

