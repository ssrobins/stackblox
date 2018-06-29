#include "ErrorHandler.h"
#include "Game.h"
#include "Piece.h"
#include "Well.h"
#include "Version.h"
#include "SDL_ttf.h"
#include <assert.h>


Game& Game::getInstance(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
{
    static Game instance(numTilesWidth, numTilesHeight, title, fullscreen);
    return instance;
}

Game::Game(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
    : fullscreen(fullscreen)
    , well(numTilesWidth, numTilesHeight)
    , showTitleScreen(true)
    , alreadyShowingTitle(false)
    , display(numTilesWidth, numTilesHeight, screenScale)
{
    int flags = 0;

    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    isRunning = false;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw Exception(SDL_GetError());
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0)
    {
        throw Exception(SDL_GetError());
    }
    display.setDisplaySize(displayMode.w, displayMode.h);

    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        display.getGameWidth(),
        display.getGameHeight(),
        flags);
    if (window == nullptr)
    {
        throw Exception(SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        throw Exception(SDL_GetError());
    }
    renderRect.x = (display.getScreenWidth()-display.getGameWidth())/2;
    renderRect.y = (display.getScreenHeight()-display.getGameHeight())/2;
    renderRect.w = display.getGameWidth();
    renderRect.h = display.getGameHeight();

    if (TTF_Init() != 0)
    {
        throw Exception(SDL_GetError());
    }

    isRunning = true;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            isRunning = false;
            return;
        }

        if (event.type == SDL_FINGERDOWN)
        {
            if (showTitleScreen)
            {
                showTitleScreen = false;
                start();
            }
            else
            {
                touchTime = std::chrono::steady_clock::now();
            }

            dragStart = event.tfinger.x * display.getScreenWidth()/display.getTileSize();
            dragVertStart = event.tfinger.y * display.getScreenHeight()/display.getTileSize();
            pieceMoved = false;
        }

        if (event.type == SDL_FINGERMOTION)
        {
            dragDistance = event.tfinger.x*display.getScreenWidth()/display.getTileSize() - dragStart;
            dragVertDistance = event.tfinger.y*display.getScreenHeight()/display.getTileSize() - dragVertStart;

            if (dragDistance <= -1)
            {
                moveOffsetTouch = -1;
                dragStart += moveOffsetTouch;
                well.quickDrop(false);
                pieceMoved = true;
            }
            else if (dragDistance >= 1)
            {
                moveOffsetTouch = 1;
                dragStart += moveOffsetTouch;
                well.quickDrop(false);
                pieceMoved = true;
            }

            if (dragVertDistance >= 1)
            {
                well.quickDrop(true);
                dropTime = time;
                dragVertStart = event.tfinger.y * display.getScreenHeight()/display.getTileSize();
            }
        }

        if (event.type == SDL_FINGERUP)
        {
            auto touchDuration =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - touchTime);

            if (touchDuration < std::chrono::milliseconds(250) &&
                !pieceMoved)
            {
                well.rotatePiece();
            }

            pieceMoved = false;

            dragStart = 0;
            dragDistance = 0;

            dragVertStart = 0;
            dragVertDistance = 0;

            well.quickDrop(false);
        }

        // If the key stays down, only one event is actually processed
        if (event.key.repeat == 0)
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_RETURN:
                    if (showTitleScreen)
                    {
                        showTitleScreen = false;
                        start();
                    }
                    break;
                case SDLK_ESCAPE:
                    if (showTitleScreen)
                    {
                        showTitleScreen = false;
                        isRunning = false;
                    }
                    break;
                case SDLK_RIGHT:
                    moveOffset += 1;
                    moveTime = time;
                    break;
                case SDLK_LEFT:
                    moveOffset -= 1;
                    moveTime = time;
                    break;
                case SDLK_DOWN:
                    well.quickDrop(true);
                    dropTime = time;
                    break;
                case SDLK_SPACE:
                    well.rotatePiece();
                    break;
                default: break;
                }
            }

            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    moveOffset -= 1;
                    moveTime = time;
                    break;
                case SDLK_LEFT:
                    moveOffset += 1;
                    moveTime = time;
                    break;
                case SDLK_DOWN:
                    dropTime = time + well.quickDrop(false);
                    break;
                default: break;
                }
            }
        }

        assert((moveOffset == 0) || (moveOffset == -1) || (moveOffset == 1));
        assert((moveOffsetTouch == 0) || (moveOffsetTouch == -1) || (moveOffsetTouch == 1));
    }
}


void Game::newPiece(const Piece& piece)
{
    well.newPiece(piece);
    dropTime = time + well.quickDrop(false);
    pieceMoved = false;
    dragStart = event.tfinger.x * display.getScreenWidth()/display.getTileSize();
    dragDistance = 0;
    dragVertStart = event.tfinger.y * display.getScreenHeight()/display.getTileSize();
    dragVertDistance = 0;
}

bool Game::noPiece()
{
    return well.hasNoPiece();
}

void Game::update()
{
    time = std::chrono::steady_clock::now();

    if (time > dropTime)
    {
        well.movePieceDown(1);
        dropTime += well.getDropDelay();
    }

    if (moveOffsetTouch != 0)
    {
        well.movePieceHorizontally(moveOffsetTouch);
        moveOffsetTouch = 0;
    }

    if (time > moveTime)
    {
        well.movePieceHorizontally(moveOffset);

        moveTime += well.getMoveDelay();
    }
}

void Game::render()
{
    if (fullscreen)
    {
        if (SDL_RenderSetViewport(renderer, &renderRect) != 0)
        {
            throw Exception(SDL_GetError());
        }
    }

    if (showTitle())
    {
        if (!alreadyShowingTitle)
        {
            renderTitleScreen();
            alreadyShowingTitle = true;
        }
    }
    else
    {
        renderStackBlox();
    }
}


void Game::renderTitleScreen()
{
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color red = { 255, 0, 0, 255 };

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    text("StackBlox", 13, white, 0, heightPercentToPixels(9), true);

    text("Controls", 5, white, widthPercentToPixels(15), heightPercentToPixels(32));

    const char * moveControls;
    const char * rotateControls;
    const char * dropControls;
    const char * startControls;

    if (hasTouchscreen)
    {
        moveControls = "Drag Across";
        rotateControls = "Touch";
        dropControls = "Drag Down";
        startControls = "Touch to start";
    }
    else
    {
        moveControls = "Left / Right";
        rotateControls = "Spacebar";
        dropControls = "Down";
        startControls = "Press Enter to start";
    }

    text(moveControls, 4, white, widthPercentToPixels(15), heightPercentToPixels(37));
    text("Move piece", 4, white, widthPercentToPixels(50), heightPercentToPixels(37));

    text(rotateControls, 4, white, widthPercentToPixels(15), heightPercentToPixels(42));
    text("Rotate piece", 4, white, widthPercentToPixels(50), heightPercentToPixels(42));

    text(dropControls, 4, white, widthPercentToPixels(15), heightPercentToPixels(47));
    text("Drop piece faster", 4, white, widthPercentToPixels(50), heightPercentToPixels(47));

    text(startControls, 6, red, 0, heightPercentToPixels(65), true);

    const std::string versionString = "Version: " + versionMajor + "." + versionMinor + "." + versionPatch;
    text(versionString.c_str(), 3, white, widthPercentToPixels(4), heightPercentToPixels(92));

    text("dnqpy.com", 3, white, widthPercentToPixels(4), heightPercentToPixels(95));

    SDL_RenderPresent(renderer);
}

void Game::renderStackBlox()
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    rect.w = display.getTileSize();
    rect.h = display.getTileSize();

    // Render pieces in well
    std::vector<std::vector<Color>> wellVals = well.getWellValues();
    for (unsigned int y = 0; y < wellVals.size(); y++)
    {
        for (unsigned int x = 0; x < wellVals[y].size(); x++)
        {
            if (wellVals.at(y).at(x) != Color{ 0, 0, 0, 0 })
            {
                SDL_SetRenderDrawColor(renderer,
                    wellVals.at(y).at(x).r,
                    wellVals.at(y).at(x).g,
                    wellVals.at(y).at(x).b,
                    wellVals.at(y).at(x).a);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer,
                    0,
                    0,
                    0,
                    255);
            }

            rect.x = x * display.getTileSize();
            rect.y = y * display.getTileSize();
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    Color color = well.getPieceColor();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Render active piece
    std::vector<Point> pieceCoords = well.getPieceTileCoordinates();
    for (auto& p : pieceCoords)
    {
        rect.x = p.x * display.getTileSize();
        rect.y = p.y * display.getTileSize();
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_Color white = { 255, 255, 255, 255 };

    if (over())
    {
        text("GAME", 15, white, 0, heightPercentToPixels(15), true);
        text("OVER", 15, white, 0, heightPercentToPixels(25), true);
    }

    // Render debug text
    /*std::string xString = "x: " + std::to_string(event.tfinger.x);
    text(xString.c_str(), 5, white, 0, heightPercentToPixels(0), false);

    std::string dragStartString = "dragStart: " + std::to_string(dragStart);
    text(dragStartString.c_str(), 5, white, 0, heightPercentToPixels(5), false);

    std::string dragDistanceString = "dragDistance: " + std::to_string(dragDistance);
    text(dragDistanceString.c_str(), 5, white, 0, heightPercentToPixels(10), false);

    std::string pieceMovedString = "pieceMoved: " + std::to_string(pieceMoved);
    text(pieceMovedString.c_str(), 5, white, 0, heightPercentToPixels(15), false);

    std::string dragVertStartString = "dragVertStart: " + std::to_string(dragVertStart);
    text(dragVertStartString.c_str(), 5, white, 0, heightPercentToPixels(20), false);

    std::string dragVertDistanceString = "dragVertDistance: " + std::to_string(dragVertDistance);
    text(dragVertDistanceString.c_str(), 5, white, 0, heightPercentToPixels(25), false);*/

    SDL_RenderPresent(renderer);
}

bool Game::over()
{
    return well.isFull();
}

void Game::reset()
{
    well.reset();
    dropTime = time + well.quickDrop(false);
    showTitleScreen = true;
    alreadyShowingTitle = false;
}

int Game::heightPercentToPixels(int percent)
{
    return display.getGameHeight() * percent / 100;
}

int Game::widthPercentToPixels(int percent)
{
    return display.getGameWidth() * percent / 100;
}

float Game::getPixelsToPointsScaleFactor(std::string& fontPath)
{
    int fontSize = 100;
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr)
    {
        throw Exception(SDL_GetError());
    }

    int height = TTF_FontHeight(font);
    if (height <= 0)
    {
        throw Exception("Font " + fontPath + " height is " + std::to_string(height));
    }
    
    TTF_CloseFont(font);
    
    return static_cast<float>(fontSize)/static_cast<float>(height);
}

void Game::text(const char * text, int fontSizeHeightPercent, SDL_Color& fontColor, int x, int y, bool centered)
{
    std::string fontPath = basePath + "assets/OpenSans-Regular.ttf";
    
    float scale = getPixelsToPointsScaleFactor(fontPath);
    int heightPixels = heightPercentToPixels(fontSizeHeightPercent);
    int fontSize = static_cast<int>(heightPixels * scale);

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr)
    {
        throw Exception(SDL_GetError());
    }

    SDL_Surface* surf = TTF_RenderText_Blended(font, text, fontColor);

    TTF_CloseFont(font);
    SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, surf);

    int textureWidth = surf->w;
    int textureHeight = surf->h;
    SDL_FreeSurface(surf);

    if (centered)
    {
        x = (display.getGameWidth() - textureWidth) / 2 - 3;
    }

    SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };

    SDL_RenderCopyEx(renderer, labelTexture, nullptr, &renderQuad, 0.0, nullptr, SDL_FLIP_NONE);
    SDL_DestroyTexture(labelTexture);
}

void Game::start()
{
    time = std::chrono::steady_clock::now();
    dropTime = time + well.quickDrop(false);
    moveTime = time + well.getMoveDelay();
}
