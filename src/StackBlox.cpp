#include "StackBlox.h"
#include "Piece.h"
#include "Well.h"
#include "Version.h"
#include <assert.h>


StackBlox& StackBlox::getInstance(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
{
    static StackBlox instance(numTilesWidth, numTilesHeight, title, fullscreen);
    return instance;
}

StackBlox::StackBlox(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
    : game(numTilesWidth, numTilesHeight, title, fullscreen)
    , well(numTilesWidth, numTilesHeight)
    , showTitleScreen(true)
    , titleText("StackBlox", game.heightPercentToPixels(13), game.getBasePath() + "assets/OpenSans-Regular.ttf", SDL_Color{ 255, 255, 255, 255 }, game.getGameWidth(), game.getRenderer(), 0, game.heightPercentToPixels(9), true)
    , fpsText(std::string{std::to_string(game.getFPS()) + " fps"}.c_str(), game.heightPercentToPixels(2), game.getBasePath() + "assets/OpenSans-Regular.ttf", SDL_Color{ 255, 255, 255, 255 }, game.getGameWidth(), game.getRenderer(), 0, game.heightPercentToPixels(0))
    , scoreText(std::string{"score: " + std::to_string(getScore())}.c_str(), game.heightPercentToPixels(2), game.getBasePath() + "assets/OpenSans-Regular.ttf", SDL_Color{ 255, 255, 255, 255 }, game.getGameWidth(), game.getRenderer(), 0, game.heightPercentToPixels(2))
{
    isRunning = true;

    // LG G4 Android device doesn't show the title screen in the proper position without this
    game.renderPresent();
}

StackBlox::~StackBlox()
{
}

void StackBlox::handleEvents()
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

            dragStart = event.tfinger.x * game.getScreenWidth()/game.getTileSize();
            dragVertStart = event.tfinger.y * game.getScreenHeight()/game.getTileSize();
            pieceMoved = false;
        }

        if (event.type == SDL_FINGERMOTION)
        {
            dragDistance = event.tfinger.x*game.getScreenWidth()/game.getTileSize() - dragStart;
            dragVertDistance = event.tfinger.y*game.getScreenHeight()/game.getTileSize() - dragVertStart;

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
                dragVertStart = event.tfinger.y * game.getScreenHeight()/game.getTileSize();
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


void StackBlox::newPiece(const Piece& piece)
{
    well.newPiece(piece);
    dropTime = time + well.quickDrop(false);
    pieceMoved = false;
    dragDistance = 0;
    dragVertDistance = 0;
    //assert(moveOffset == 0); // FIX BEFORE MERGE!
    assert(moveOffsetTouch == 0);
}

bool StackBlox::noPiece()
{
    return well.hasNoPiece();
}

void StackBlox::update()
{
    if (!showTitle())
    {
        updateStackBlox();
    }

    fpsText.updateText(std::string{std::to_string(game.getFPS()) + " fps"}.c_str());
}

void StackBlox::updateStackBlox()
{
    time = std::chrono::steady_clock::now();

    if (time > dropTime)
    {
        well.movePieceDown(1);
        dropTime += well.getDropDelay();
        scoreText.updateText(std::string{"score: " + std::to_string(getScore())}.c_str());
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

void StackBlox::render()
{
    game.renderSetViewport();

    if (showTitle())
    {
        renderTitleScreen();
    }
    else
    {
        renderStackBlox();
    }
}


void StackBlox::renderTitleScreen()
{
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color red = { 255, 0, 0, 255 };

    game.setRenderDrawColor({ 0, 0, 0, 255 });
    game.renderClear();

    titleText.render();
    fpsText.render();

    game.text("Controls", 5, white, game.widthPercentToPixels(15), game.heightPercentToPixels(32));

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

    game.text(moveControls, 4, white, game.widthPercentToPixels(15), game.heightPercentToPixels(37));
    game.text("Move piece", 4, white, game.widthPercentToPixels(50), game.heightPercentToPixels(37));

    game.text(rotateControls, 4, white, game.widthPercentToPixels(15), game.heightPercentToPixels(42));
    game.text("Rotate piece", 4, white, game.widthPercentToPixels(50), game.heightPercentToPixels(42));

    game.text(dropControls, 4, white, game.widthPercentToPixels(15), game.heightPercentToPixels(47));
    game.text("Drop piece faster", 4, white, game.widthPercentToPixels(50), game.heightPercentToPixels(47));

    game.text(startControls, 6, red, 0, game.heightPercentToPixels(65), true);

    const std::string versionString = "Version: " + versionMajor + "." + versionMinor + "." + versionPatch;
    game.text(versionString.c_str(), 3, white, game.widthPercentToPixels(4), game.heightPercentToPixels(92));

    game.text("dnqpy.com", 3, white, game.widthPercentToPixels(4), game.heightPercentToPixels(95));

    game.renderPresent();
}

void StackBlox::renderStackBlox()
{
    game.setRenderDrawColor({ 0, 0, 0, 255 });
    game.renderClear();

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Rect outlineRect = { 0, 0, game.getGameWidth(), game.getGameHeight() };
    game.renderFillRect(outlineRect, white);

    SDL_Rect rect;
    rect.w = game.getTileSize();
    rect.h = game.getTileSize();

    SDL_Color tileColor;

    // Render pieces in well
    std::vector<std::vector<Color>> wellVals = well.getWellValues();
    for (unsigned int y = 0; y < wellVals.size(); y++)
    {
        for (unsigned int x = 0; x < wellVals[y].size(); x++)
        {
            if (wellVals.at(y).at(x) != Color{ 0, 0, 0, 0 })
            {
                tileColor = {
                    wellVals.at(y).at(x).r,
                    wellVals.at(y).at(x).g,
                    wellVals.at(y).at(x).b,
                    wellVals.at(y).at(x).a};
            }
            else
            {
                tileColor = { 0, 0, 0, 255 };
            }

            rect.x = x * game.getTileSize() + game.getOutlineOffsetWidth();
            rect.y = y * game.getTileSize() + game.getOutlineOffsetHeight();
            game.renderFillRect(rect, tileColor);
        }
    }

    Color color = well.getPieceColor();

    // Render active piece
    std::vector<Point> pieceCoords = well.getPieceTileCoordinates();
    for (auto& p : pieceCoords)
    {
        rect.x = p.x * game.getTileSize() + game.getOutlineOffsetWidth();
        rect.y = p.y * game.getTileSize() + game.getOutlineOffsetHeight();
        game.renderFillRect(rect, { color.r, color.g, color.b, color.a });
    }

    if (over())
    {
        game.text("GAME", 15, white, 0, game.heightPercentToPixels(15), true);
        game.text("OVER", 15, white, 0, game.heightPercentToPixels(25), true);
    }

    fpsText.render();
    scoreText.render();

    // Render debug text
    std::string scoreString = "score: " + std::to_string(getScore());
    game.text(scoreString.c_str(), 5, white, 0, game.heightPercentToPixels(0), false);
    std::string resString = std::to_string(game.getScreenWidth()) + " x " + std::to_string(game.getScreenHeight());
    game.text(resString.c_str(), 5, white, 0, game.heightPercentToPixels(5), false);
    std::string fpsString = std::to_string(game.getFPS()) + " fps";
    game.text(fpsString.c_str(), 5, white, 0, game.heightPercentToPixels(10), false);



    /*std::string dropString = "drop delay: " + std::to_string(well.getDropDelay().count());
    game.text(dropString.c_str(), 5, white, 0, game.heightPercentToPixels(5), false);*/

    /*std::string xString = "x: " + std::to_string(event.tfinger.x);
    game.text(xString.c_str(), 5, white, 0, game.heightPercentToPixels(0), false);

    std::string dragStartString = "dragStart: " + std::to_string(dragStart);
    game.text(dragStartString.c_str(), 5, white, 0, game.heightPercentToPixels(5), false);

    std::string dragDistanceString = "dragDistance: " + std::to_string(dragDistance);
    game.text(dragDistanceString.c_str(), 5, white, 0, game.heightPercentToPixels(10), false);

    std::string pieceMovedString = "pieceMoved: " + std::to_string(pieceMoved);
    game.text(pieceMovedString.c_str(), 5, white, 0, game.heightPercentToPixels(15), false);

    std::string dragVertStartString = "dragVertStart: " + std::to_string(dragVertStart);
    game.text(dragVertStartString.c_str(), 5, white, 0, game.heightPercentToPixels(20), false);

    std::string dragVertDistanceString = "dragVertDistance: " + std::to_string(dragVertDistance);
    game.text(dragVertDistanceString.c_str(), 5, white, 0, game.heightPercentToPixels(25), false);*/

    game.renderPresent();
}

const int StackBlox::getScore() const
{
    return well.getScore();
}

bool StackBlox::over()
{
    return well.isFull();
}

void StackBlox::reset()
{
    well.reset();
    dropTime = time + well.quickDrop(false);
    showTitleScreen = true;
}

void StackBlox::playTitleScreenMusic()
{
    game.playMusic("assets/GetDownWithTheBlox.ogg");
    isPlayingMusic = true;
}

void StackBlox::stopMusic()
{
    game.stopMusic();
    isPlayingMusic = false;
}

void StackBlox::start()
{
    time = std::chrono::steady_clock::now();
    dropTime = time + well.quickDrop(false);
    moveTime = time + well.getMoveDelay();
}
