#include "Display.h"

Display::Display(const int numTilesWidth, const int numTilesHeight)
    : numTilesWidth(numTilesWidth)
    , numTilesHeight(numTilesHeight)
{
}

void Display::setDisplaySize(const int width, const int height, const float screenScale, const bool outline)
{
    screenWidth = width;
    screenHeight = height;

    if (static_cast<float>(screenWidth) / static_cast<float>(screenHeight) > static_cast<float>(numTilesWidth) / static_cast<float>(numTilesHeight)) {
        tileSize = static_cast<int>((screenHeight * screenScale) / numTilesHeight);
    } else {
        tileSize = static_cast<int>((screenWidth * screenScale) / numTilesWidth);
    }

    gameWidth = tileSize * numTilesWidth;
    gameHeight = tileSize * numTilesHeight;
    outlineOffsetWidth = 0;
    outlineOffsetHeight = 0;

    if (outline) {
        int gameMinDim = 0;
        if (gameWidth < gameHeight) {
            gameMinDim = gameWidth;
        } else {
            gameMinDim = gameHeight;
        }

        int outlineLimit = gameMinDim / 150;
        if (outlineLimit == 0) {
            outlineLimit = 1;
        }

        int extraSpaceWidth = screenWidth - gameWidth;
        if (extraSpaceWidth >= outlineLimit * 2) {
            outlineOffsetWidth = outlineLimit;
            gameWidth = gameWidth + outlineOffsetWidth * 2;
        }

        int extraSpaceHeight = screenHeight - gameHeight;
        if (extraSpaceHeight >= outlineLimit * 2) {
            outlineOffsetHeight = outlineLimit;
            gameHeight = gameHeight + outlineOffsetHeight * 2;
        }
    }
}

int Display::heightPercentToPixels(const int percent) const
{
    return gameHeight * percent / 100;
}

int Display::widthPercentToPixels(const int percent) const
{
    return gameWidth * percent / 100;
}
