#include "Well.h"
#include "Piece.h"

Score::Score()
    : score(0)
{
}

void Score::updateScore(unsigned int deleteLineCount, unsigned int dropDelayDiff)
{
    score += deleteLineCount * (lineScore + (deleteLineCount - 1) * lineBonus) + dropDelayDiff + 1;
}

Well::Well(const int numTilesWidth, const int numTilesHeight)
    : numTilesWidth(numTilesWidth)
    , numTilesHeight(numTilesHeight)
    , wellVals(numTilesHeight, std::vector<Color>(numTilesWidth))
    , wellIsFull(false)
    , wellHasNoPiece(true)
{
    quickDrop(false);
}

void Well::addPieceToWell()
{
    std::vector<Point> pieceCoords = getPieceTileCoordinates();
    Color pieceColor = getPieceColor();

    for (auto& p : pieceCoords) {
        if (p.y >= 0 && p.x >= 0) {
            wellVals.at(p.y).at(p.x) = pieceColor;
        }
    }

    wellHasNoPiece = true;
}

bool Well::collision()
{
    bool result = false;

    std::vector<Point> pieceCoords = getPieceTileCoordinates();
    for (auto& p : pieceCoords) {
        // Collision detection between active piece and well boundaries
        if (p.x < 0 || p.x >= numTilesWidth || p.y >= numTilesHeight) {
            result = true;
            break;
        }

        // Collision detection between active piece and well pieces
        for (unsigned int y = 0; y < wellVals.size(); y++) {
            for (unsigned int x = 0; x < wellVals[y].size(); x++) {
                if (wellVals.at(y).at(x) != Color { 0, 0, 0, 0 }) {
                    if (p.x == x && p.y == y) {
                        result = true;
                        break;
                    }
                }
            }
        }
    }

    return result;
}

bool Well::isFull() const
{
    return wellIsFull;
}

const std::chrono::milliseconds Well::getDropDelay() const
{
    return dropDelay;
}

const int Well::getScore() const
{
    return score.getScore();
}

std::chrono::milliseconds Well::decreaseDropDelay()
{
    if (dropDelayNormal > dropDelayLimit) {
        dropDelayNormal -= dropDelayInterval;
    }
    return dropDelayNormal;
}

std::chrono::milliseconds Well::quickDrop(bool force)
{
    if (force) {
        dropDelay = dropDelayForce;
    } else {
        dropDelay = dropDelayNormal;
    }
    return dropDelay;
}

std::vector<std::vector<Color>> Well::getWellValues() const
{
    return wellVals;
}

void Well::movePieceHorizontally(int x)
{
    if (x != 0) {
        Piece pieceOriginal = piece;

        piece.move(x, 0);

        if (collision()) {
            piece = pieceOriginal;
        }
    }
}

void Well::movePieceDown(int y)
{
    Piece pieceOriginal = piece;

    piece.move(0, y);

    if (collision()) {
        if (pieceOriginal.atTop()) {
            wellIsFull = true;
        }

        piece = pieceOriginal;
        addPieceToWell();
        deleteCompleteLines();
    }
}

void Well::newPiece(const Piece& newPiece)
{
    piece = newPiece;
    wellHasNoPiece = false;
}

void Well::reset()
{
    for (unsigned int y = 0; y < wellVals.size(); y++) {
        for (unsigned int x = 0; x < wellVals[y].size(); x++) {
            wellVals.at(y).at(x) = Color { 0, 0, 0, 0 };
        }
    }

    wellIsFull = false;
    dropDelayNormal = dropDelayDefault;
    score.reupdateScore();
}

void Well::rotatePiece()
{
    Piece pieceOriginal = piece;

    piece.rotate();

    if (collision()) {
        piece = pieceOriginal;
    }
}

void Well::deleteCompleteLines()
{
    std::vector<std::vector<Color>> wellValsModified = wellVals;
    int deleteLineCount = 0;

    for (unsigned int y = 0; y < wellVals.size(); y++) {
        bool lineComplete = true;
        for (unsigned int x = 0; x < wellVals[y].size(); x++) {
            if (wellVals.at(y).at(x) == Color { 0, 0, 0, 0 }) {
                lineComplete = false;
            }
        }

        if (lineComplete) {
            wellValsModified.erase(wellValsModified.begin() + y);
            wellValsModified.insert(wellValsModified.begin(), std::vector<Color>(numTilesWidth, { 0, 0, 0, 0 }));
            deleteLineCount++;
        }
    }
    score.updateScore(deleteLineCount, static_cast<unsigned int>(dropDelayDefault.count()) - static_cast<unsigned int>(dropDelayNormal.count()));

    wellVals = wellValsModified;
}

const Color Well::getPieceColor() const
{
    return piece.getColor();
}

const std::vector<Point> Well::getPieceTileCoordinates() const
{
    return piece.getTileCoordinates();
}
