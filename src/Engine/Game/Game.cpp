#include "Game.h"
#include "Exceptions.h"
#include "SDL_image.h"
#include <chrono>

Text::Text(const char* text, int heightPixels, std::string fontPath, SDL_Color fontColor, int gameWidth, SDL_Renderer* renderer, int x, int y, bool centered, bool createTextureNow)
    : fontColor(fontColor)
    , centered(centered)
    , text(text)
    , x(x)
    , y(y)
    , renderer(renderer)
    , gameWidth(gameWidth)
{
    if (TTF_Init() != 0) {
        throw Exception(SDL_GetError());
    }

    fontSize = 100;
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (font == nullptr) {
        throw Exception(SDL_GetError());
    }

    float scale = getPixelsToPointsScaleFactor();
    fontSize = static_cast<int>(heightPixels * scale);

    if (createTextureNow)
        createTexture();
}

void Text::createTexture()
{
    TTF_SetFontSize(font, fontSize);

    surf = TTF_RenderText_Blended(font, text, fontColor);
    int textureWidth = surf->w;
    int textureHeight = surf->h;

    SDL_DestroyTexture(labelTexture);
    labelTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    if (centered) {
        x = (gameWidth - textureWidth) / 2 - 3;
    }

    renderQuad = { x, y, textureWidth, textureHeight };
}

void Text::render()
{
    SDL_RenderCopyEx(renderer, labelTexture, nullptr, &renderQuad, 0.0, nullptr, SDL_FLIP_NONE);
}

void Text::updateText(const char* newText)
{
    text = newText;
    createTexture();
}

Text::~Text()
{
    SDL_DestroyTexture(labelTexture);
    TTF_CloseFont(font);
}

Game::Game(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen)
    : screenScale(getScreenScale(fullscreen))
    , display(numTilesWidth, numTilesHeight)
{
    int flags = SDL_WINDOW_ALLOW_HIGHDPI;

    if (fullscreen) {
        flags = flags | SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw Exception(SDL_GetError());
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        throw Exception(SDL_GetError());
    }
    display.setDisplaySize(displayMode.w, displayMode.h, screenScale, false);

    window = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        display.getGameWidth(),
        display.getGameHeight(),
        flags);
    if (window == nullptr) {
        throw Exception(SDL_GetError());
    }

    std::string iconPath = getBasePath() + "assets/Icon1024x1024.png";
    SDL_Surface* icon = IMG_Load(iconPath.c_str());
    if (icon == nullptr) {
        throw Exception(SDL_GetError());
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        throw Exception(SDL_GetError());
    }

    int pixelWidth;
    int pixelHeight;
    SDL_GetRendererOutputSize(renderer, &pixelWidth, &pixelHeight);
    display.setDisplaySize(pixelWidth, pixelHeight, 1.0f, true);
    renderRect.x = (display.getScreenWidth() - display.getGameWidth()) / 2;
    renderRect.y = (display.getScreenHeight() - display.getGameHeight()) / 2;
    renderRect.w = display.getGameWidth();
    renderRect.h = display.getGameHeight();
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

const float Game::getScreenScale(bool fullscreen)
{
    if (fullscreen) {
        return 1.0f;
    } else {
        return 0.8f;
    }
}

float Text::getPixelsToPointsScaleFactor()
{
    if (font == nullptr) {
        throw Exception(SDL_GetError());
    }
    int height = TTF_FontHeight(font);
    if (height <= 0) {
        throw Exception("Font height is " + std::to_string(height));
    }

    return static_cast<float>(fontSize) / static_cast<float>(height);
}

void Game::renderSetViewport()
{
    if (SDL_RenderSetViewport(renderer, &renderRect) != 0) {
        throw Exception(SDL_GetError());
    }
}

void Game::setRenderDrawColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Game::renderClear()
{
    SDL_RenderClear(renderer);
}

void Game::renderPresent()
{
    SDL_RenderPresent(renderer);
    calculateFPS();
}

std::string Game::getBasePath()
{
    std::string basePath =
#if __ANDROID__
        "";
#else
        SDL_GetBasePath();
#endif

    return basePath;
}

void Game::calculateFPS()
{
    static std::chrono::time_point<std::chrono::high_resolution_clock> oldTime = std::chrono::high_resolution_clock::now();
    static int numFrames;
    numFrames++;

    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds { 1 }) {
        oldTime = std::chrono::high_resolution_clock::now();
        fps = numFrames;
        numFrames = 0;
    }
}

void Game::renderFillRect(const SDL_Rect& rect, const SDL_Color& color)
{
    setRenderDrawColor(color);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Game::playMusic(const std::string& musicPath)
{
    std::string fullMusicPath = getBasePath() + musicPath;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw Exception(Mix_GetError());
    }
    music = Mix_LoadMUS(fullMusicPath.c_str());
    if (music == nullptr) {
        throw Exception(Mix_GetError());
    }
    Mix_PlayMusic(music, -1);
}

void Game::stopMusic()
{
    Mix_FadeOutMusic(100);
    Mix_FreeMusic(music);
    music = nullptr;
}
