#pragma once

#include <vector>

class Display
{
public:
    Display(int numTilesWidth, int numTilesHeight, float screenScale);
    void setDisplaySize(int width, int height);
    int getScreenWidth() { return screenWidth; };
    int getScreenHeight() { return screenHeight; };
    int getTileSize() { return tileSize; };
    int getGameWidth() { return gameWidth; };
    int getGameHeight() { return gameHeight; };
private:
    const int numTilesWidth;
    const int numTilesHeight;
    const float screenScale;
    float widthToHeightTileRatio;
    int screenWidth;
    int screenHeight;
    int gameWidth;
    int gameHeight;
    int tileSize;
};
