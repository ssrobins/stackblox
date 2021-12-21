#pragma once

#include "Game.h"
#include "Well.h"

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
    bool playingMusic() { return isPlayingMusic; }
    bool noPiece();
    void newPiece(const Piece& piece);
    bool over();

    void reset();
    void render();
    void renderStackBlox();
    void renderTitleScreen();
    void playMusic();
    void start();

private:
    StackBlox(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);

    const bool hasTouchscreen =
    #if __ANDROID__ || TARGET_OS_IPHONE
        true;
    #else
        false;
    #endif

    Game game;

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

    bool isPlayingMusic;
    bool showTitleScreen;
};
