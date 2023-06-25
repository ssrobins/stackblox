#pragma once

#include "Display.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <string>

class Text {
public:
    Text(const char* text, int heightPixels, std::string fontPath, SDL_Color fontColor, int gameWidth, SDL_Renderer* renderer, int x = 0, int y = 0, bool centered = false, bool createTextureNow = true);
    ~Text();
    void updateText(const char* newText);
    void createTexture();
    void render();

private:
    float getPixelsToPointsScaleFactor();
    TTF_Font* font;
    int fontSize;
    SDL_Color fontColor;
    const char* text;
    int x;
    int y;
    bool centered;
    SDL_Surface* surf;
    SDL_Texture* labelTexture;
    SDL_Rect renderQuad;
    SDL_Renderer* renderer;
    int gameWidth;
};

class Game {
public:
    Game(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);
    ~Game();
    const float getScreenScale(bool fullscreen);

    void renderSetViewport();
    void setRenderDrawColor(const SDL_Color& color);
    void renderClear();
    void renderPresent();
    void renderFillRect(const SDL_Rect& rect, const SDL_Color& color);
    void playMusic(const std::string& musicPath);
    void stopMusic();
    int getScreenWidth() const { return display.getScreenWidth(); }
    int getScreenHeight() const { return display.getScreenHeight(); }
    int getGameWidth() const { return display.getGameWidth(); }
    int getGameHeight() const { return display.getGameHeight(); }
    int getTileSize() const { return display.getTileSize(); }
    int getFPS() const { return fps; }
    static std::string getBasePath();
    SDL_Renderer* getRenderer() const { return renderer; }
    void calculateFPS();
    int getOutlineOffsetWidth() { return display.getOutlineOffsetWidth(); };
    int getOutlineOffsetHeight() { return display.getOutlineOffsetHeight(); };
    int widthPercentToPixels(int percent) const { return display.widthPercentToPixels(percent); }
    int heightPercentToPixels(int percent) const { return display.heightPercentToPixels(percent); }

private:
    const float screenScale;

    Display display;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect renderRect;
    Mix_Music* music;
    int fps = 0;
};
