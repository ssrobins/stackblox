#include "ErrorHandler.h"
#include "StackBlox.h"
#include "SDL_mixer.h"

int main(int argc, char *argv[])
{
    const int numTilesWidth = 12;
    const int numTilesHeight = 20;

    ErrorHandler errorHandler("error.log");
    int errorCode = EXIT_SUCCESS;

    bool fullscreen = 
    #if __ANDROID__ || TARGET_OS_IPHONE
        true;
    #else
        false;
    #endif

    try
    {
        auto& stackblox = StackBlox::getInstance(
            numTilesWidth,
            numTilesHeight,
            "StackBlox",
            fullscreen);

        PieceCollection pieceCollection = {
            Piece(pieceI, xOffsetCenter(pieceI, numTilesWidth), yOffsetTop(pieceI), pieceIcolor),
            Piece(pieceJ, xOffsetCenter(pieceJ, numTilesWidth), yOffsetTop(pieceJ), pieceJcolor),
            Piece(pieceL, xOffsetCenter(pieceL, numTilesWidth), yOffsetTop(pieceL), pieceLcolor),
            Piece(pieceO, xOffsetCenter(pieceO, numTilesWidth), yOffsetTop(pieceO), pieceOcolor),
            Piece(pieceS, xOffsetCenter(pieceS, numTilesWidth), yOffsetTop(pieceS), pieceScolor),
            Piece(pieceT, xOffsetCenter(pieceT, numTilesWidth), yOffsetTop(pieceT), pieceTcolor),
            Piece(pieceZ, xOffsetCenter(pieceZ, numTilesWidth), yOffsetTop(pieceZ), pieceZcolor)
        };

        const int FPS = 60;

        // 1000 milliseconds per second divided by 60 frames per second = milliseconds per frame
        const int frameDelay = 1000 / FPS;

        Uint32 frameStart;
        int frameTime;

        bool playingMusic = false;
        Mix_Music *music = nullptr;

        while (stackblox.running())
        {
            frameStart = SDL_GetTicks();
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }

            stackblox.handleEvents();

            if (!stackblox.showTitle())
            {
                if (stackblox.noPiece())
                {
                    stackblox.newPiece(pieceCollection.getRandomPiece());
                }

                stackblox.update();
            }

            if (!stackblox.running())
            {
                break;
            }

            if(!playingMusic)
            {
                if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                }
                music = Mix_LoadMUS("assets/GetDownWithTheBlox.ogg");
                if(music == nullptr)
                {
                    printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
                }
                Mix_PlayMusic(music, -1);

                playingMusic = true;
            }

            stackblox.render();

            if (stackblox.over())
            {
                SDL_Delay(3000); // in milliseconds
                stackblox.reset();
            }
        }
    }
    catch (Exception& error)
    {
        errorHandler.showError(error);
        errorCode = EXIT_FAILURE;
    }

    return errorCode;
}
