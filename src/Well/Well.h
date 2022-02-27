#pragma once

#include "Piece.h"
#include <chrono>

class Well
{
public:
    Well(const int numTilesWidth, const int numTilesHeight);
    void addPieceToWell();
    bool collision();
    bool isFull() const;
    const std::chrono::milliseconds getDropDelay() const;
    const int getScore() const;
    std::chrono::milliseconds decreaseDropDelay();
    std::chrono::milliseconds quickDrop(bool force);
    std::vector<std::vector<Color>> getWellValues() const;
    void movePieceHorizontally(int x);
    void movePieceDown(int y);
    void newPiece(const Piece& newPiece);
    bool hasNoPiece() { return wellHasNoPiece; }
    void reset();
    void rotatePiece();
    void deleteCompleteLines();
    const Color getPieceColor() const;
    const std::vector<Point> getPieceTileCoordinates() const;
    const std::chrono::milliseconds getMoveDelay() const { return moveDelay; }
private:
    const int numTilesWidth;
    const int numTilesHeight;
    std::vector<std::vector<Color>> wellVals;
    Piece piece;
    bool wellIsFull;
    bool wellHasNoPiece;
    const std::chrono::milliseconds moveDelay = std::chrono::milliseconds(100);
    const std::chrono::milliseconds dropDelayDefault = std::chrono::milliseconds{ 1000 };
    const std::chrono::milliseconds dropDelayInterval = std::chrono::milliseconds{ 5 };
    const std::chrono::milliseconds dropDelayLimit = std::chrono::milliseconds{ 100 };
    const std::chrono::milliseconds dropDelayForce = std::chrono::milliseconds{ 50 };
    std::chrono::milliseconds dropDelayNormal = dropDelayDefault + dropDelayInterval;
    std::chrono::milliseconds dropDelay;
    int score;
    const int lineScore = 100;
    const int lineBonus = 25;
};
