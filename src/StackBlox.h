#pragma once

#include "Game.h"
#include "Well.h"

// POC
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class ControlText {
public:
    ControlText(const bool hasTouchscreen);
    const char* moveControls;
    const char* rotateControls;
    const char* dropControls;
    const char* startControls;
    const char* continueControls;
};

class TitleScreen {
public:
    TitleScreen(const Game& game, const bool hasTouchscreen);
    ~TitleScreen() {};
    void render();

private:
    std::string fontPath;
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color red = { 255, 0, 0, 255 };
    ControlText controlText;
    Text titleText;
    Text controlHeadingText;
    Text moveControlText;
    Text moveControlDescripText;
    Text rotateControlText;
    Text rotateControlDescripText;
    Text dropControlText;
    Text dropControlDescripText;
    Text startControlText;
    Text versionText;
    Text websiteText;
};

class StackBlox {
public:
    static StackBlox& getInstance(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);
    ~StackBlox();
    StackBlox(StackBlox const&) = delete;
    void operator=(StackBlox const&) = delete;

    void handleEvents();
    void update();
    void updateStackBlox();
    bool running() { return isRunning; }
    bool showTitle() { return showTitleScreen; }
    bool playingMusic() { return isPlayingMusic; }
    bool noPiece();
    void newPiece(const Piece& piece);
    const int getScore() const;
    bool over();

    void reset();
    void render();
    void renderStackBlox();
    void renderTitleScreen();
    void renderAdventureBlox();
    void updateAdventureBlox();
    void playTitleScreenMusic();
    void stopMusic();
    void start();

private:
    StackBlox(const int numTilesWidth, const int numTilesHeight, const char* title, bool fullscreen);

    const bool hasTouchscreen =
#if __ANDROID__ || TARGET_OS_IPHONE
        true;
#else
        false;
#endif

    std::string fontPath;
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color red = { 255, 0, 0, 255 };

    Game game;
    TitleScreen titleScreen;

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

    bool showDebugText = false;
    ControlText controlText;
    Text scoreText;
    Text gameText;
    Text overText;
    Text finalScoreText;
    Text continueControlText;
    Text fpsText;
    Text screenResText;
    Text dropDelayText;
    Text dragStartText;
    Text dragDistanceText;
    Text pieceMovedText;
    Text dragVertStartText;
    Text dragVertDistanceText;
    
    // POC move to final location later
    SDL_Texture* playerTex;
    SDL_Rect playerRect;
    int cnt = 0;
};

// POC
class TextureManager {
public:
    static SDL_Texture* loadTexture(const char* filename, SDL_Renderer* ren);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_Renderer* ren);

};


class GameObject {

public:
    GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;
};

class Map
{
public:
    Map(SDL_Renderer* ren);
    ~Map();
    void LoadMap(int arr[10][10]);
    void DrawMap();
private:
    SDL_Rect src, dest;
    SDL_Texture* wall;
    SDL_Texture* floor;
    
    SDL_Renderer* renderer;
    
    int map[10][10];
    
};


// ECS.h
class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;


class Component
{
public:
    Entity* entity;
    
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
    
    virtual ~Component() {}
};


class Entity
{
private:
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;
    
    ComponentArray componentArray;
    ComponentBitSet componentBitSet;

public:
    void update()
    {
        for (auto& c: components) c->update();
        for (auto& c : components) c-> draw();
    }
    void draw() {}
    bool isActive() const { return active; }
    void destroy() { active = false; }

    template <typename T> bool hasComponent() const
    {
        return componentBitSet[getComponentTypeID<T>];
    }

    template <typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));
        
        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;
        
        c->init();
        return *c;
    }
    
    template<typename T> T& getComponent() const
    {
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;

public:
    void update()
    {
        for (auto& e : entities) e->update();
    }
    void draw()
    {
        for (auto& e : entities) e->draw();
    }

    void refresh()
    {
        entities.erase(std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity->isActive();
        }),
            std::end(entities));
    }
    
    Entity& addEntity()
    {
        Entity* e = new Entity();
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};


// Components.h
class PositionComponent : public Component
{
private:
    int xpos;
    int ypos;
public:
    int x() { return xpos; }
    int y() { return ypos; }
    
    void init() override
    {
        xpos = 0;
        ypos = 0;
    }

    void update() override
    {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y)
    {
        xpos = x;
        ypos = y;
    }
};

