#include "Display.h"

Display::Display(int numTilesWidth, int numTilesHeight, float screenScale)
    : numTilesWidth(numTilesWidth)
    , numTilesHeight(numTilesHeight)
    , screenScale(screenScale)
{
}

void Display::setDisplaySize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    widthToHeightTileRatio = static_cast<float>(numTilesWidth) / static_cast<float>(numTilesHeight);

    if (static_cast<float>(screenWidth) / static_cast<float>(screenHeight) > widthToHeightTileRatio)
    {
        tileSize = static_cast<int>((screenHeight * screenScale) / numTilesHeight);
    }
    else
    {
        tileSize = static_cast<int>((screenWidth * screenScale) / numTilesWidth);
    }

    gameWidth = tileSize * numTilesWidth;
    gameHeight = tileSize * numTilesHeight;
}