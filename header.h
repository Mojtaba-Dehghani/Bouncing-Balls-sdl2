#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <cstring>
#include <SDL2/SDL.h>
#define WINDOW_WIDTH    1008
#define WINDOW_HEIGHT   753
#define SCORE_OFFSET_X  0
#define SCORE_OFFSET_Y  50
#define LEVEL_OFFSET_X  931
#define LEVEL_OFFSET_Y  631
#define BUBBLE_OFFSET_X 165
#define BUBBLE_OFFSET_Y -15
#define TIMER_OFFSET_X  900
#define TIMER_OFFSET_Y  135
#define BUBBLE_WIDTH    40
#define BUBBLE_HEIGHT   40
#define NUM_BUBBLES     5
#define NUM_LEVELS      50
#define BOARD_SIZE_X    18
#define BOARD_SIZE_Y    18
#define NUM_NODES       (BOARD_SIZE_X * BOARD_SIZE_Y)

#define CANNON_BUBBLE_OFFSET_X  480
#define CANNON_BUBBLE_OFFSET_Y  650
#define CANNON_BUBBLE_WIDTH     50
#define CANNON_BUBBLE_HEIGHT    50

#define SPARE_BUBBLE_OFFSET_X  30
#define SPARE_BUFFLE_OFFSET_Y 640
#define SPARE_BUBBLE_W         65
#define SPARE_BUBBLE_H         65

#define NUM_STRIKES     5
#define STRIKES_RECT_W  28
#define STRIKES_RECT_H  (125/NUM_STRIKES)
#define STRIKES_RECT_X  930
#define STRIKES_RECT_Y  405

#define WALL_LEFT_X   145
#define WALL_RIGHT_X  865
#define WALL_TOP_Y    0
#define WALL_BOTTOM_Y WINDOW_HEIGHT
// TODO: move these into structs when scaling to multiple levels
#define LVL1_START_X 4
#define LVL1_END_X   13
#define LVL1_START_Y 2
#define LVL1_END_Y   10

#define LVL1_CENTER_X 8
#define LVL1_CENTER_Y 8


class Bubble : public Entity
{
public:
    Bubble(BubbleColor bubbleColor, SDL_FRect dstRect, bool isVisible = false);
    ~Bubble();
    BubbleColor GetColor(void) { return bubbleColor; }
    void SetColor(BubbleColor bubbleColor) { this->bubbleColor = bubbleColor; }
    void Clear(void);
private:
    BubbleColor bubbleColor;
};

#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity
{
public:
    Entity();
    ~Entity();
    void Render();
    static void ToggleRectangleVisible()
    {
        rectangleVisible = !rectangleVisible;
    }
    void SetTexture(SDL_Texture *texture)
    {
        this->texture = texture;
    }
    SDL_Texture* GetTexture(void)
    {
        return texture;
    }
    SDL_FRect GetDestRect(void)
    {
        return dstRect;
    }
    bool IsVisible(void) 
    { 
        return isVisible; 
    }
    void SetVisible(bool visible) 
    { 
        isVisible = visible; 
    }
    void SetDestRect(SDL_FRect rect)
    {
        dstRect = rect;
    }
protected:
    SDL_Texture *texture;
    SDL_FRect srcRect, dstRect;
    bool isVisible;
    static bool rectangleVisible;
};


#ifndef _GAME_H_
#define _GAME_H_

X
using namespace std;

class Game
{
public:
    Game(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    ~Game();
    void Play(void);
private:
    void InitMap(void);
    void InitStats(void);
    void RotateBubbles(RotateDirection direction);
    void HandleEvents(void);
    void HandleMouseMotion(SDL_Event &event);
    void HandleMouseDown(SDL_Event &event);
    void HandleMouseUp(SDL_Event &event);
    void Render(void);
    void Update(void);
    void ShootBubbleInit(void);
    void ShootBubble(void);
    void ChangeLevel(int offset);
    BubbleColor RandomBubble(void);
    void DisplayCannonToBubbleVector(void);
    void DisplayScore(void);
    void DisplayTimer(void);
    void DisplayLevel(void);
    void DisplayBubbles(void);
    void DisplayConsecutiveStrikesRect(void);
    void DisplayBackground(void);
    bool InsideRect(int pointX, int pointY, SDL_Rect &rect);
    bool InsideRect(float pointX, float pointY, SDL_FRect &rect);
    void Normalize(SDL_FPoint &vec, int length = 600);
    void HandleCollision(float &x, float &y, Bubble *bubble);

// data section
private:
    // gamestate
    bool running;
    bool paused;
    bool frozen;
    time_t currentTime;
    int levelOffset;
    Uint32 level;
    Uint32 score;
    Uint64 currentFrame;
    Uint64 frozenFrame;
    Bubble *bubbles[BOARD_SIZE_X][BOARD_SIZE_Y];
    Bubble *cannonBubble, *spareBubble, *shotBubble;
    SDL_Rect consecutiveStrikesRect;
    SDL_Point cannonPoint, mousePoint;
    SDL_Point startPoint, endPoint;
    SDL_FPoint shotBubbleDirectionVector;
    int numBubblesLeft;
    int timer;
    float bubbleSpeed;
    int consecutiveStrikes;
    int strikesAfter5Consecutive;
    float scoreMultiplier;
    float t;
    bool rotateLeft, rotateRight;
    bool shouldShootBubble;
    bool shootingBubble;
    double velocity;
    double acceleration;
};



#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_


using namespace std;

#define NUM_LEVELS_IMPLEMENTED 7
class LevelManager
{
public:
    ~LevelManager();
    static LevelManager* getInstance();
    int GetNumBubbles(int level)
    {
        if(level > NUM_LEVELS_IMPLEMENTED)
        {
            fprintf(stderr, "Level %d has not been implemented yet - if you know a new board, mail me at wagner.daniel98@yahoo.com\n", level);
            exit(EXIT_FAILURE);
        }
        return numBubbles[level-1];
    }
    void SetLevel(int l, Bubble *bubbles[BOARD_SIZE_X][BOARD_SIZE_Y]);
private:
    LevelManager();
    static LevelManager *instance;
    int8_t level[NUM_LEVELS_IMPLEMENTED][BOARD_SIZE_X][BOARD_SIZE_Y];
    int numBubbles[NUM_LEVELS_IMPLEMENTED];
};


#ifndef _MATCHFINDER_H_
#define _MATCHFINDER_H_


using namespace std;


class Matchfinder
{
public:
    bool CheckForMatch(int new_i, int new_j);
    bool BoardContains(BubbleColor bubbleColor);
    bool BoardIsEmpty(void) { return numBubbles == 0; }
    static Matchfinder* getInstance();
    void ClearPath(Bubble *bubbles[BOARD_SIZE_X][BOARD_SIZE_Y], int *pscore, int *pbubbles);
    void SetMatrix(int i, int j, BubbleColor bubbleColor);
    int8_t GetMatrix(int i, int j);
    void ZeroMatrix(void);
    void PrintMatrix(void);
    ~Matchfinder();
private:
    Matchfinder();
    bool PathContains(vector<Path*> &p, int x, int y);
    bool IsIsolated(int x, int y);
    static Matchfinder *instance;
    int8_t graph[NUM_NODES][NUM_NODES];
    int8_t matrix[BOARD_SIZE_X][BOARD_SIZE_Y];
    int numBubbles;
    vector<Path*> path;
};





#ifndef _SINGLETONS_H_
#define _SINGLETONS_H_
class FontRenderer
{
public:
    ~FontRenderer();
    static FontRenderer* getInstance();
    void DisplayText(const char *msg, int x, int y);
private:
    FontRenderer();
    static FontRenderer *instance;
    TTF_Font *font;
};

class TextureManager
{
public:
    ~TextureManager();
    static TextureManager* getInstance();
    SDL_Texture* GetBackground(void) { return background; }
    SDL_Texture* GetBubble(BubbleColor bubbleColor) 
    { 
        if(bubbleColor == BUBBLE_NONE) 
            return NULL; 
        return bubbles[bubbleColor]; 
    }
private:
    TextureManager();
    SDL_Texture* CreateTextureFromImage(const char *path);
private:
    static TextureManager *instance;
    SDL_Texture *background;
    SDL_Texture *bubbles[NUM_BUBBLES];
};

class GUIManager
{
public:
    ~GUIManager();
    static GUIManager* getInstance();
    SDL_Renderer* GetRenderer(void)          { return renderer; }
    void SetRenderer(SDL_Renderer *renderer) { this->renderer = renderer; }
    void SetWindow(SDL_Window *window)       { this->window = window; }
private:
    GUIManager();
    static GUIManager *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
};



#ifndef _SOUNDMANAGER_H_
#define _SOUNDMANAGER_H_

#define NUM_SOUNDS 9
enum SoundType
{
    SOUND_SHOOT_BUBBLE,
    SOUND_FAILED_SHOT,
    SOUND_COMBO,
    SOUND_COMBO_BONUS1,
    SOUND_COMBO_BONUS2,
    SOUND_FULLY_LOADED,
    SOUND_HIT_WALL,
    SOUND_LEVEL_UP,
    SOUND_RESET_BONUS
};
class SoundManager
{
private:
    SoundManager();
    void Load(const char *filename, SoundType soundType);
public:
    ~SoundManager();
    static SoundManager* getInstance();
    void PlaySound(SoundType soundType);
public:
    static SoundManager *instance;
private:
    SDL_AudioSpec wavSpec[NUM_SOUNDS];
    SDL_AudioDeviceID deviceId[NUM_SOUNDS];
    Uint32 wavLength[NUM_SOUNDS];
    Uint8 *wavBuffer[NUM_SOUNDS];
};
#endif