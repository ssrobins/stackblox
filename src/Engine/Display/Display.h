#pragma once

class Display {
public:
    Display(const int numTilesWidth, const int numTilesHeight);
    void setDisplaySize(const int width, const int height, const float screenScale, const bool outline);
    int heightPercentToPixels(const int percent) const;
    int widthPercentToPixels(const int percent) const;
    int getScreenWidth() const { return screenWidth; };
    int getScreenHeight() const { return screenHeight; };
    int getTileSize() const { return tileSize; };
    int getGameWidth() const { return gameWidth; };
    int getGameHeight() const { return gameHeight; };
    int getOutlineOffsetWidth() const { return outlineOffsetWidth; };
    int getOutlineOffsetHeight() const { return outlineOffsetHeight; };

private:
    const int numTilesWidth;
    const int numTilesHeight;
    int screenWidth;
    int screenHeight;
    int gameWidth;
    int gameHeight;
    int outlineOffsetWidth;
    int outlineOffsetHeight;
    int tileSize;
};
