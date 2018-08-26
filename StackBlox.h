#pragma once

#include "Display.h"
#include "Well.h"
#include "SDL.h"
#include <string>

class StackBlox
{
public:
    static StackBlox& getInstance(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);
    ~StackBlox();
    StackBlox(StackBlox const&) = delete;
    void operator=(StackBlox const&) = delete;

    void handleEvents();
    void update();
    bool running() { return isRunning; }
    bool showTitle() { return showTitleScreen; }
    bool noPiece();
    void newPiece(const Piece& piece);
    bool over();

    void reset();
    void render();
    void renderStackBlox();
    void renderTitleScreen();
    void start();

private:
    StackBlox(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);

    void text(const char * text, int fontSizeHeightPercent, SDL_Color& fontColor, int x = 0, int y = 0, bool centered = false);

    const float screenScale = 
    #if __ANDROID__ || TARGET_OS_IPHONE
        1.0f;
    #else
        0.8f;
    #endif

    const bool hasTouchscreen =
    #if __ANDROID__ || TARGET_OS_IPHONE
        true;
    #else
        false;
    #endif

    Display display;
    bool fullscreen;

    float getPixelsToPointsScaleFactor(std::string& fontPath);

    SDL_Window *window;
    SDL_Renderer* renderer;
    SDL_Rect renderRect;
    SDL_Event event;
    bool isRunning;
    std::chrono::steady_clock::time_point time;
    std::chrono::steady_clock::time_point dropTime;
    std::chrono::steady_clock::time_point moveTime;
    int moveOffset = 0;
    int moveOffsetTouch = 0;

    bool pieceMoved = false;
    std::chrono::steady_clock::time_point touchTime;
    float dragStart = 0;
    float dragVertStart = 0;
    float dragDistance = 0;
    float dragVertDistance = 0;

    Well well;

    bool showTitleScreen;
    bool alreadyShowingTitle;

    std::string basePath = 
    #if __ANDROID__
        "";
    #else
        SDL_GetBasePath();
    #endif
};
