#include "StackBlox.h"
#include "Piece.h"
#include "Well.h"
#include "Version.h"
#include <assert.h>


ControlText::ControlText(const bool hasTouchscreen)
{
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
}

TitleScreen::TitleScreen(const Game& game, const bool hasTouchscreen)
    : fontPath(Game::getBasePath() + "assets/OpenSans-Regular.ttf")
    , controlText(hasTouchscreen)
    , titleText("StackBlox", game.heightPercentToPixels(13), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(0), game.heightPercentToPixels(9), true)
    , controlHeadingText("Controls", game.heightPercentToPixels(5), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(15), game.heightPercentToPixels(32))
    , moveControlText(controlText.moveControls, game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(15), game.heightPercentToPixels(37))
    , moveControlDescripText("Move piece", game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(50), game.heightPercentToPixels(37))
    , rotateControlText(controlText.rotateControls, game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(15), game.heightPercentToPixels(42))
    , rotateControlDescripText("Rotate piece", game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(50), game.heightPercentToPixels(42))
    , dropControlText(controlText.dropControls, game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(15), game.heightPercentToPixels(47))
    , dropControlDescripText("Drop piece faster", game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(50), game.heightPercentToPixels(47))
    , startControlText(controlText.startControls, game.heightPercentToPixels(6), fontPath, red, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(0), game.heightPercentToPixels(65), true)
    , versionText(("Version: " + versionMajor + "." + versionMinor + "." + versionPatch).c_str(), game.heightPercentToPixels(3), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(4), game.heightPercentToPixels(92))
    , websiteText("dnqpy.com", game.heightPercentToPixels(3), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(4), game.heightPercentToPixels(95))
{
}

void TitleScreen::render()
{
    titleText.render();
    controlHeadingText.render();
    moveControlText.render();
    moveControlDescripText.render();
    rotateControlText.render();
    rotateControlDescripText.render();
    dropControlText.render();
    dropControlDescripText.render();
    startControlText.render();
    versionText.render();
    websiteText.render();
}

StackBlox& StackBlox::getInstance(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
{
    static StackBlox instance(numTilesWidth, numTilesHeight, title, fullscreen);
    return instance;
}

StackBlox::StackBlox(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
    : game(numTilesWidth, numTilesHeight, title, fullscreen)
    , well(numTilesWidth, numTilesHeight)
    , showTitleScreen(true)
    , titleScreen(game, hasTouchscreen)
    , fontPath(Game::getBasePath() + "assets/OpenSans-Regular.ttf")
    , scoreText(std::string{std::to_string(getScore())}.c_str(), game.heightPercentToPixels(4), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(2), game.heightPercentToPixels(0))
    , gameText("GAME", game.heightPercentToPixels(15), fontPath, white, game.getGameWidth(), game.getRenderer(), 0, game.heightPercentToPixels(15), true)
    , overText("OVER", game.heightPercentToPixels(15), fontPath, white, game.getGameWidth(), game.getRenderer(), 0, game.heightPercentToPixels(25), true)
    , fpsText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(25), game.heightPercentToPixels(1), false, false)
    , screenResText(std::string{"res: " + std::to_string(game.getScreenWidth()) + " x " + std::to_string(game.getScreenHeight())}.c_str(), game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(35), game.heightPercentToPixels(1))
    , dropDelayText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(56), game.heightPercentToPixels(1), false, false)
    , dragStartText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(25), game.heightPercentToPixels(3), false, false)
    , dragDistanceText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(50), game.heightPercentToPixels(3), false, false)
    , pieceMovedText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(73), game.heightPercentToPixels(3), false, false)
    , dragVertStartText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(25), game.heightPercentToPixels(5), false, false)
    , dragVertDistanceText("", game.heightPercentToPixels(2), fontPath, white, game.getGameWidth(), game.getRenderer(), game.widthPercentToPixels(54), game.heightPercentToPixels(5), false, false)
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
    assert(moveOffset == 0);
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
}

void StackBlox::updateStackBlox()
{
    time = std::chrono::steady_clock::now();

    if (time > dropTime)
    {
        well.movePieceDown(1);
        dropTime += well.getDropDelay();
        if (noPiece())
        {
            scoreText.updateText(std::string{std::to_string(getScore())}.c_str());
            well.decreaseDropDelay();
        }
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

    if (showDebugText)
        fpsText.updateText(std::string{std::to_string(game.getFPS()) + " fps"}.c_str());

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
    game.setRenderDrawColor({ 0, 0, 0, 255 });
    game.renderClear();

    if (showDebugText)
        fpsText.render();

    titleScreen.render();

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

    scoreText.render();

    if (over())
    {
        gameText.render();
        overText.render();
    }

    if (showDebugText)
    {
        fpsText.render();
        screenResText.render();
        dropDelayText.updateText(std::string{"dropDelay: " + std::to_string(well.getDropDelay().count())}.c_str());
        dropDelayText.render();

        if (hasTouchscreen)
        {
            dragStartText.updateText(std::string{"dragStart: " + std::to_string(dragStart)}.c_str());
            dragStartText.render();
            dragDistanceText.updateText(std::string{"dragDist: " + std::to_string(dragDistance)}.c_str());
            dragDistanceText.render();
            pieceMovedText.updateText(std::string{"pieceMoved: " + std::to_string(pieceMoved)}.c_str());
            pieceMovedText.render();
            dragVertStartText.updateText(std::string{"dragVertStart: " + std::to_string(dragVertStart)}.c_str());
            dragVertStartText.render();
            dragVertDistanceText.updateText(std::string{"dragVertDist: " + std::to_string(dragVertDistance)}.c_str());
            dragVertDistanceText.render();
        }
    }

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
    scoreText.updateText(std::string{std::to_string(getScore())}.c_str());

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
